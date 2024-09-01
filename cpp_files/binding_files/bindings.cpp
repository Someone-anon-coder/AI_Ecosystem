#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "../header_files/file_configure.h"
#include "../header_files/folder_configure.h"
#include "../header_files/news_configure.h"

namespace py = pybind11;

PYBIND11_MODULE(angel_configure, m) {
    py::class_<File>(m, "File")
        .def(py::init<>())
        .def("create_file", &File::create_file)
        .def("write_file", &File::write_file)
        .def("read_file", &File::read_file)
        .def("delete_file", &File::delete_file)
        .def("rename_file", &File::rename_file)
        .def("move_file", &File::move_file)
        .def("copy_file", &File::copy_file)
        .def("check_file", &File::check_file)
        .def("hide_file", &File::hide_file)
        .def("unhide_file", &File::unhide_file);

    py::class_<Folder>(m, "Folder")
        .def(py::init<>())
        .def("create_folder", &Folder::create_folder)
        .def("list_folder", &Folder::list_folder)
        .def("delete_folder", &Folder::delete_folder)
        .def("rename_folder", &Folder::rename_folder)
        .def("move_folder", &Folder::move_folder)
        .def("copy_folder", &Folder::copy_folder)
        .def("check_folder", &Folder::check_folder)
        .def("hide_folder", &Folder::hide_folder)
        .def("unhide_folder", &Folder::unhide_folder);
    
    py::class_<GoogleNews>(m, "GoogleNews")
        .def(py::init<>())
        .def("get_language", &GoogleNews::get_language)
        .def("get_country", &GoogleNews::get_country)
        .def("get_period", &GoogleNews::get_period)
        .def("get_start_date", &GoogleNews::get_start_date)
        .def("get_end_date", &GoogleNews::get_end_date)
        .def("get_max_results", &GoogleNews::get_max_results)
        .def("get_exclude_websites", &GoogleNews::get_exclude_websites)
        .def("get_news", &GoogleNews::get_news)
        .def("get_latest_topics", &GoogleNews::get_latest_topics)
        .def("get_news_by_topic", &GoogleNews::get_news_by_topic)
        .def("get_news_by_country", &GoogleNews::get_news_by_country)
        .def("get_news_by_site", &GoogleNews::get_news_by_site)
        .def("set_language", &GoogleNews::set_language)
        .def("set_country", &GoogleNews::set_country)
        .def("set_period", &GoogleNews::set_period)
        .def("set_start_date", &GoogleNews::set_start_date)
        .def("set_end_date", &GoogleNews::set_end_date)
        .def("set_max_results", &GoogleNews::set_max_results)
        .def("set_excluded_websites", &GoogleNews::set_excluded_websites);
}
