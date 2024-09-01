#include <X11/Xatom.h>
#include <X11/Xlib.h>

#include <sys/select.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <fstream>
#include <iostream>
#include <sstream>

#include <string>
#include <vector>

#include <fcntl.h>
#include <pwd.h>
#include <string.h>
#include <unistd.h>

#include <ctime>

#include "../header_files/file_configure.h"

class Application{
    private:
        std::string _app_name;
        pid_t _pid;
        Window _window;
        
        std::string _read_file(
            const std::string fullpath // Path of the file
        ){
            std::ifstream file_read;
            file_read.open(fullpath.c_str());
            std::string content((std::istreambuf_iterator<char>(file_read)), std::istreambuf_iterator<char>());
            
            file_read.close();
            return content;
        }

        std::string _get_process_state(
            const pid_t pid // PID of the application
        ){ // Gets the state of the application

            std::string fullpath = "/proc/" + std::to_string(pid) + "/status";
            std::string status = _read_file(fullpath);
            std::istringstream iss(status);
            std::string line;

            while (std::getline(iss, line)) {
                if (line.find("State:") == 0) {
                    return line.substr(line.find(':') + 1);
                }
            }
            return "Unknown";
        }

        std::string _get_command_line(
            const pid_t pid // PID of the application
        ) { // Gets the command line of the application
            std::string cmdline = _read_file("/proc/" + std::to_string(pid) + "/cmdline");
            cmdline = cmdline.substr(cmdline.find('\0') + 1);
            
            return cmdline;
        }

        std::string _get_process_owner(
            const pid_t pid // PID of the application
        ) { // Gets the owner of the application
            struct stat info;
            struct passwd *pw = getpwuid(info.st_uid);
            
            return pw ? pw->pw_name : "Unknown";
        }

        long _get_system_uptime() { // Get system uptime
            std::string uptime_str = _read_file("/proc/uptime");
            std::istringstream iss(uptime_str);
            
            long uptime;
            iss >> uptime;
            
            return uptime;
        }

        long _get_process_start_time(
            const pid_t pid // PID of the application
        ) { // Gets the start time of the application
            std::string stat = _read_file("/proc/" + std::to_string(pid) + "/stat");
            std::istringstream iss(stat);
            std::vector<std::string> stats;
            std::string token;
            
            while (iss >> token) {
                stats.push_back(token);
            }
            
            long start_time = std::stol(stats[21]);
            return start_time / sysconf(_SC_CLK_TCK);
        }

        long _get_process_uptime(
            const pid_t pid // PID of the application
        ) { // Gets the uptime of the application
            long system_uptime = Application::_get_system_uptime();
            long process_start_time = Application::_get_process_start_time(pid);
            
            return system_uptime - process_start_time;
        }

        std::string _get_memory_usage(
            const pid_t pid // PID of the application
        ) { // Gets the memory usage of the application
            std::string status = _read_file("/proc/" + std::to_string(pid) + "/status");
            std::istringstream iss(status);
            std::string line;
            
            while (std::getline(iss, line)) {
                if (line.find("VmSize:") == 0) {
                    return line.substr(line.find(':') + 1);
                }
            }
            return "Unknown";
        }

        std::string _get_cpu_usage(
            const pid_t pid // PID of the application
        ) { // Gets the CPU usage of the application
            std::string stat = _read_file("/proc/" + std::to_string(pid) + "/stat");
            std::istringstream iss(stat);
            std::vector<std::string> stats;
            std::string token;
            
            while (iss >> token) {
                stats.push_back(token);
            }
            
            long utime = std::stol(stats[13]);
            long stime = std::stol(stats[14]);
            long cutime = std::stol(stats[15]);
            long cstime = std::stol(stats[16]);
            long total_time = utime + stime + cutime + cstime;
            long process_uptime = Application::_get_process_uptime(pid);
            double cpu_usage = 100.0 * (total_time / sysconf(_SC_CLK_TCK)) / process_uptime;
            
            return std::to_string(cpu_usage) + "%";
        }

        bool _is_process_running(
            const pid_t pid // PID of the application
        ) { // Checks if the application is running
            return kill(pid, 0) == 0;
        }

        Display* _open_display() {
            Display* display = XOpenDisplay(nullptr);
            return display;
        }

        Window _get_window_by_pid(
            Display* display, // Display of the application 
            const pid_t pid // PID of the application
        ) { // Gets the window handle of the application
            Window root = DefaultRootWindow(display);
            Window parent;
            Window* children;
            unsigned int nchildren;

            if (XQueryTree(display, root, &root, &parent, &children, &nchildren)) {
                for (unsigned int i = 0; i < nchildren; ++i) {
                    Window w = children[i];
                    Atom atom = XInternAtom(display, "_NET_WM_PID", True);
            
                    if (atom != None) {
                        Atom actual_type;
                        int actual_format;
                        unsigned long nitems, bytes_after;
                        unsigned char* prop;
            
                        if (XGetWindowProperty(display, w, atom, 0, 1, False, XA_CARDINAL,
                                               &actual_type, &actual_format, &nitems, &bytes_after,
                                               &prop) == Success) {
            
                            if (prop) {
                                if (pid == *(pid_t*)prop) {
                                    XFree(prop);
                                    XFree(children);
                                    return w;
                                }
                                XFree(prop);
                            }
                        }
                    }
                }
                
                if (children) {
                    XFree(children);
                }
            }
            return 0;
        }

        bool _execute_command(
            const std::string& command // Command to execute
        ) { // Executes a command
            pid_t pid = fork();

            if (pid == -1) {
                // Fork failed
                return false;
            } else if (pid == 0) {
                // In the child process
                std::vector<char*> args;
                std::istringstream iss(command);
                std::string token;

                while (iss >> token) {
                    char* arg = new char[token.size() + 1];
                    std::copy(token.begin(), token.end(), arg);
                    arg[token.size()] = '\0';
                    args.push_back(arg);
                }

                args.push_back(nullptr);
                execvp(args[0], args.data());

                // If execvp returns, it must have failed
                for (auto arg : args) {
                    delete[] arg;
                }
                _exit(EXIT_FAILURE);
            } else {
                // In the parent process
                int status;
                if (waitpid(pid, &status, 0) == -1) {
                    // Waitpid failed
                    return false;
                }
                return WIFEXITED(status) && WEXITSTATUS(status) == 0;
            }
        }

    public:
        Application(){}
        ~Application(){}

        void start_app(
            const std::string app_name, // Name of the application
            const std::vector<std::string> arguments // Arguments of the application
        ){ // Starts the application
            pid_t pid = fork();

            std::vector<char*> arg;
            arg.push_back(const_cast<char*>(app_name.c_str()));

            for (const auto& argument : arguments) {
                arg.push_back(const_cast<char*>(argument.c_str()));
            }
            arg.push_back(nullptr);

            execvp(arg[0], arg.data());
            Application::_pid = pid;
        }

        void stop_app(
            const pid_t pid=0, // PID of the application
            const bool force=false // Force stop the application
        ){ // Stops the application
            kill(pid==0 ? Application::_pid : pid, force ? SIGKILL : SIGTERM);
            waitpid(pid, nullptr, 0);
        }

        void get_status(
            pid_t pid=0, // PID of the application
            const std::string filename="status_file.txt", // Name of the status file
            const std::string file_path="log_files/" // Path of the status file
        ) { // Gets the status of the application
            std::ofstream write_file;
            std::string fullpath = file_path + filename;
            std::string status;

            if (pid==0) {
                pid = Application::_pid;
            }
            
            if (!Application::_is_process_running(pid)) {
                status = "Process not running";
                return;
            }

            status += "Process ID (PID): " + std::to_string(pid) + "\n";
            status += "State: " + Application::_get_process_state(pid) + "\n";
            status += "CPU Usage: " + Application::_get_cpu_usage(pid) + "\n";
            status += "Memory Usage: " + Application::_get_memory_usage(pid) + "\n";
            status += "Uptime: " + std::to_string(Application::_get_process_uptime(pid)) + " seconds\n";
            status += "Command Line: " + Application::_get_command_line(pid) + "\n";
            status += "Owner: " + Application::_get_process_owner(pid) + "\n";
            
            write_file.open(fullpath.c_str());
            write_file << status << std::endl;
            write_file.close();
        }

        void get_window_handle(
            pid_t pid=0 // PID of the application
        ) { // Gets the window handle of the application
            Display* display = _open_display();
            Window window = _get_window_by_pid(display, pid==0 ? Application::_pid : pid);
            
            XCloseDisplay(display);
            Application::_window = window;
        }

        void window_foreground(
            Window window=0 // Window handle of the application
        ) { // Brings the application window to the foreground
            Display* display = _open_display();
            window==0 ? window = Application::_window : window;
            
            XRaiseWindow(display, window);
            XSetInputFocus(display, window, RevertToPointerRoot, CurrentTime);
            XCloseDisplay(display);
        }

        void minimize_window(
            Window window=0 // Window handle of the application
        ) { // Minimizes the application window
            Display* display = _open_display();
            window==0 ? window = Application::_window : window;
            
            XIconifyWindow(display, window, DefaultScreen(display));
            XCloseDisplay(display);
        }

        void maximize_window(
            Window window=0 // Window handle of the application
        ) { // Maximizes the application window
            Display* display = _open_display();
            window==0 ? window = Application::_window : window;

            Atom wm_state = XInternAtom(display, "_NET_WM_STATE", False);
            Atom wm_max_horz = XInternAtom(display, "_NET_WM_STATE_MAXIMIZED_HORZ", False);
            Atom wm_max_vert = XInternAtom(display, "_NET_WM_STATE_MAXIMIZED_VERT", False);
            
            XEvent xev;
            memset(&xev, 0, sizeof(xev));
            
            xev.type = ClientMessage;
            xev.xclient.window = window;
            xev.xclient.message_type = wm_state;
            xev.xclient.format = 32;
            xev.xclient.data.l[0] = 1;
            xev.xclient.data.l[1] = wm_max_horz;
            xev.xclient.data.l[2] = wm_max_vert;
            
            XSendEvent(display, DefaultRootWindow(display), False,
                       SubstructureNotifyMask | SubstructureRedirectMask, &xev);
            XCloseDisplay(display);
        }

        void restore_window(
            Window window=0 // Window handle of the application
        ) { // Restores the application window
            Display* display = _open_display();
            window==0 ? window = Application::_window : window;
            
            Atom wm_state = XInternAtom(display, "_NET_WM_STATE", False);
            Atom wm_max_horz = XInternAtom(display, "_NET_WM_STATE_MAXIMIZED_HORZ", False);
            Atom wm_max_vert = XInternAtom(display, "_NET_WM_STATE_MAXIMIZED_VERT", False);
            
            XEvent xev;
            memset(&xev, 0, sizeof(xev));
            
            xev.type = ClientMessage;
            xev.xclient.window = window;
            xev.xclient.message_type = wm_state;
            xev.xclient.format = 32;
            xev.xclient.data.l[0] = 0; // _NET_WM_STATE_REMOVE
            xev.xclient.data.l[1] = wm_max_horz;
            xev.xclient.data.l[2] = wm_max_vert;
            
            XSendEvent(display, DefaultRootWindow(display), False,
                       SubstructureNotifyMask | SubstructureRedirectMask, &xev);
            XCloseDisplay(display);
        }

        void resize_or_move_window(
            const int x,
            const int y,
            const int width,
            const int height,
            Window window=0 // Window handle of the application
        ) { // Resizes or moves the application window
            Display* display = _open_display();
            window==0 ? window = Application::_window : window;
            
            XMoveResizeWindow(display, window, x, y, width, height);
            XCloseDisplay(display);
        }

        bool is_window_in_focus(
            Window window=0 // Window handle of the application
        ) { // Checks if the application window is in focus
            Display* display = _open_display();
            window==0 ? window = Application::_window : window;

            Window focused;
            int revert_to;
            
            XGetInputFocus(display, &focused, &revert_to);
            XCloseDisplay(display);
            
            return focused == window;
        }

        bool check_for_updates() { // Checks if any application requires updation
            std::string command = "sudo apt-get update";
            return _execute_command(command);
        }
    
        bool install_updates() { // Installs updates for applications
            std::string command = "sudo apt-get upgrade -y";
            return _execute_command(command);
        }
    
        bool install_application(
            const std::string package_name // Name of the application
        ) { // Install the specified application
            std::string command = "sudo apt-get install -y " + package_name;
            return _execute_command(command);
        }
    
        bool uninstall_application(
            const std::string package_name // Name of the application
        ) { // Uninstall the specified application
            std::string command = "sudo apt-get remove -y " + package_name;
            return _execute_command(command);
        }
};