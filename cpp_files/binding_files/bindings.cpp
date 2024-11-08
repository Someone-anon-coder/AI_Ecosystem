#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "../header_files/file_configure.h"
#include "../header_files/folder_configure.h"
#include "../header_files/news_configure.h"
#include "../header_files/search_configure.h"

namespace py = pybind11;

PYBIND11_MODULE(angel_configure, m) {
    py::class_<File>(m, "File")
        .def(py::init<>())
        .def("__class_info__", &File::__class_info__)
        .def("_create_file", &File::_create_file, py::arg("filename"), py::arg("file_path") = "")
        .def("_write_file", &File::_write_file, py::arg("filename"), py::arg("content"), py::arg("file_path") = "")
        .def("_read_file", &File::_read_file, py::arg("filename"), py::arg("file_path") = "")
        .def("_delete_file", &File::_delete_file, py::arg("filename"), py::arg("file_path") = "")
        .def("_rename_file", &File::_rename_file, py::arg("filename"), py::arg("new_filename"), py::arg("file_path") = "")
        .def("_move_file", &File::_move_file, py::arg("filename"), py::arg("new_path"), py::arg("file_path") = "")
        .def("_copy_file", &File::_copy_file, py::arg("filename"), py::arg("new_path"), py::arg("file_path") = "")
        .def("_check_file", &File::_check_file, py::arg("filename"), py::arg("file_path") = "")
        .def("_hide_file", &File::_hide_file, py::arg("filename"), py::arg("file_path") = "")
        .def("_unhide_file", &File::_unhide_file, py::arg("filename"), py::arg("file_path") = "");

    py::class_<Folder>(m, "Folder")
        .def(py::init<>())
        .def("__class_info__", &Folder::__class_info__)
        .def("_create_folder", &Folder::_create_folder, py::arg("folder_name"), py::arg("folder_path") = "")
        .def("_list_folder", &Folder::_list_folder, py::arg("folder_name"), py::arg("list_filename") = "folder_list_file.txt", py::arg("list_file_path") = "log_files/", py::arg("folder_path") = "")
        .def("_delete_folder", &Folder::_delete_folder, py::arg("folder_name"), py::arg("folder_path") = "")
        .def("_rename_folder", &Folder::_rename_folder, py::arg("folder_name"), py::arg("new_folder_name"), py::arg("folder_path") = "")
        .def("_move_folder", &Folder::_move_folder, py::arg("folder_name"), py::arg("new_path"), py::arg("folder_path") = "")
        .def("_copy_folder", &Folder::_copy_folder, py::arg("folder_name"), py::arg("new_path"), py::arg("folder_path") = "")
        .def("_check_folder", &Folder::_check_folder, py::arg("folder_name"), py::arg("folder_path") = "")
        .def("_hide_folder", &Folder::_hide_folder, py::arg("folder_name"), py::arg("folder_path") = "")
        .def("_unhide_folder", &Folder::_unhide_folder, py::arg("folder_name"), py::arg("folder_path") = "");
    
    py::class_<GoogleNews>(m, "GoogleNews")
        .def(py::init<const std::string, const std::string, const std::string, const std::string, const std::string, const int, std::vector<std::string>>(), py::arg("language") = "en", py::arg("country") = "US", py::arg("period") = "anytime", py::arg("start_date") = "", py::arg("end_date") = "", py::arg("max_results") = 0, py::arg("exclude_websites") = std::vector<std::string>{})
        .def("__class_info__", &GoogleNews::__class_info__)
        .def("_get_language", &GoogleNews::_get_language)
        .def("_get_country", &GoogleNews::_get_country)
        .def("_get_period", &GoogleNews::_get_period)
        .def("_get_start_date", &GoogleNews::_get_start_date)
        .def("_get_end_date", &GoogleNews::_get_end_date)
        .def("_get_max_results", &GoogleNews::_get_max_results)
        .def("_get_exclude_websites", &GoogleNews::_get_exclude_websites)
        .def("_get_news", &GoogleNews::_get_news, py::arg("keyword"), py::arg("filename") = "text_files/news_articles.txt")
        .def("_get_latest_topics", &GoogleNews::_get_latest_topics, py::arg("filename") = "text_files/news_articles.txt")
        .def("_get_news_by_topic", &GoogleNews::_get_news_by_topic, py::arg("topic"), py::arg("filename") = "text_files/news_articles.txt")
        .def("_get_news_by_country", &GoogleNews::_get_news_by_country, py::arg("keyword"), py::arg("country"), py::arg("filename") = "text_files/news_articles.txt")
        .def("_get_news_by_site", &GoogleNews::_get_news_by_site, py::arg("site"), py::arg("filename") = "text_files/news_articles.txt")
        .def("_set_language", &GoogleNews::_set_language)
        .def("_set_country", &GoogleNews::_set_country)
        .def("_set_period", &GoogleNews::_set_period)
        .def("_set_start_date", &GoogleNews::_set_start_date)
        .def("_set_end_date", &GoogleNews::_set_end_date)
        .def("_set_max_results", &GoogleNews::_set_max_results)
        .def("_set_excluded_websites", &GoogleNews::_set_excluded_websites);
    
    py::class_<GoogleSearch>(m, "GoogleSearch")
        .def(py::init<const std::string, const int, const int, const int, const int, const int, const std::string, const std::string, const std::string, const std::string, const std::string, const std::string, const std::string, const std::string, const std::string, const std::string, const std::string, const std::string, const std::string, const std::string, const std::string, const std::string, const std::string, const std::string, const std::string, const std::string, const std::string, const std::string, const std::string, const std::string, const std::string>(), py::arg("search_terms") = "", py::arg("num_results") = 0, py::arg("start_index") = -1, py::arg("filter") = 0, py::arg("c2coff") = 0, py::arg("date_restrict") = 0, py::arg("extra_query") = "", py::arg("exact_terms") = "", py::arg("exclude_terms") = "", py::arg("site_search") = "", py::arg("site_search_filter") = "", py::arg("link_site") = "", py::arg("or_terms") = "", py::arg("date_restrict_type") = "", py::arg("low_range") = "", py::arg("high_range") = "", py::arg("search_type") = "", py::arg("filetype") = "", py::arg("rights") = "", py::arg("img_size") = "", py::arg("img_type") = "", py::arg("img_color_type") = "", py::arg("img_dominant_color") = "", py::arg("language") = "", py::arg("interface_language") = "", py::arg("user_country") = "", py::arg("result_country") = "", py::arg("safe") = "", py::arg("sort") = "", py::arg("json_file") = "json_files/search_result.json", py::arg("env_file") = "secret_files/.env")
        .def("__class_info__", &GoogleSearch::__class_info__)
        .def("_get_num_results", &GoogleSearch::_get_num_results)
        .def("_get_start_index", &GoogleSearch::_get_start_index)
        .def("_get_filter", &GoogleSearch::_get_filter)
        .def("_get_c2coff", &GoogleSearch::_get_c2coff)
        .def("_get_date_restrict", &GoogleSearch::_get_date_restrict)
        .def("_get_query", &GoogleSearch::_get_query)
        .def("_get_search_url", &GoogleSearch::_get_search_url)
        .def("_get_extra_query", &GoogleSearch::_get_extra_query)
        .def("_get_exact_terms", &GoogleSearch::_get_exact_terms)
        .def("_get_exclude_terms", &GoogleSearch::_get_exclude_terms)
        .def("_get_site_search", &GoogleSearch::_get_site_search)
        .def("_get_site_search_filter", &GoogleSearch::_get_site_search_filter)
        .def("_get_link_site", &GoogleSearch::_get_link_site)
        .def("_get_or_terms", &GoogleSearch::_get_or_terms)
        .def("_get_date_restrict_type", &GoogleSearch::_get_date_restrict_type)
        .def("_get_low_range", &GoogleSearch::_get_low_range)
        .def("_get_high_range", &GoogleSearch::_get_high_range)
        .def("_get_search_type", &GoogleSearch::_get_search_type)
        .def("_get_filetype", &GoogleSearch::_get_filetype)
        .def("_get_rights", &GoogleSearch::_get_rights)
        .def("_get_img_size", &GoogleSearch::_get_img_size)
        .def("_get_img_type", &GoogleSearch::_get_img_type)
        .def("_get_img_color_type", &GoogleSearch::_get_img_color_type)
        .def("_get_img_dominant_color", &GoogleSearch::_get_img_dominant_color)
        .def("_get_language", &GoogleSearch::_get_language)
        .def("_get_interface_language", &GoogleSearch::_get_interface_language)
        .def("_get_user_country", &GoogleSearch::_get_user_country)
        .def("_get_result_country", &GoogleSearch::_get_result_country)
        .def("_get_safe", &GoogleSearch::_get_safe)
        .def("_get_sort", &GoogleSearch::_get_sort)
        .def("_get_json_file", &GoogleSearch::_get_json_file)
        .def("_get_env_file", &GoogleSearch::_get_env_file)
        .def("_set_num_results", &GoogleSearch::_set_num_results)
        .def("_set_start_index", &GoogleSearch::_set_start_index)
        .def("_set_filter", &GoogleSearch::_set_filter)
        .def("_set_c2coff", &GoogleSearch::_set_c2coff)
        .def("_set_date_restrict", &GoogleSearch::_set_date_restrict)
        .def("_set_extra_query", &GoogleSearch::_set_extra_query)
        .def("_set_exact_terms", &GoogleSearch::_set_exact_terms)
        .def("_set_exclude_terms", &GoogleSearch::_set_exclude_terms)
        .def("_set_site_search", &GoogleSearch::_set_site_search)
        .def("_set_site_search_filter", &GoogleSearch::_set_site_search_filter)
        .def("_set_link_site", &GoogleSearch::_set_link_site)
        .def("_set_or_terms", &GoogleSearch::_set_or_terms)
        .def("_set_date_restrict_type", &GoogleSearch::_set_date_restrict_type)
        .def("_set_low_range", &GoogleSearch::_set_low_range)
        .def("_set_high_range", &GoogleSearch::_set_high_range)
        .def("_set_search_type", &GoogleSearch::_set_search_type)
        .def("_set_filetype", &GoogleSearch::_set_filetype)
        .def("_set_rights", &GoogleSearch::_set_rights)
        .def("_set_img_size", &GoogleSearch::_set_img_size)
        .def("_set_img_type", &GoogleSearch::_set_img_type)
        .def("_set_img_color_type", &GoogleSearch::_set_img_color_type)
        .def("_set_img_dominant_color", &GoogleSearch::_set_img_dominant_color)
        .def("_set_language", &GoogleSearch::_set_language)
        .def("_set_interface_language", &GoogleSearch::_set_interface_language)
        .def("_set_user_country", &GoogleSearch::_set_user_country)
        .def("_set_result_country", &GoogleSearch::_set_result_country)
        .def("_set_safe", &GoogleSearch::_set_safe)
        .def("_set_sort", &GoogleSearch::_set_sort)
        .def("_set_response_file", &GoogleSearch::_set_response_file)
        .def("_set_env_file", &GoogleSearch::_set_env_file)
        .def("_search_google", &GoogleSearch::_search_google, py::arg("query"), py::arg("filename") = "json_files/search_result.json")
        .def("_get_result", &GoogleSearch::_get_result, py::arg("result_index") = 0, py::arg("title") = "True", py::arg("snippet") = "True", py::arg("link") = "False", py::arg("image") = "False", py::arg("json_filename") = "json_files/search_result.json", py::arg("text_filename") = "text_files/search_results.txt");
}
