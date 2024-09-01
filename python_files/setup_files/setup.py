from setuptools import setup, Extension
import pybind11

ext_modules = [
    Extension(
        'angel_configure',
        sources=['cpp_files/binding_files/bindings.cpp', 'cpp_files/program_files/file_configure.cpp', 'cpp_files/program_files/folder_configure.cpp', 'cpp_files/program_files/news_configure.cpp'],
        include_dirs=[pybind11.get_include()],
        libraries=['curl', 'tinyxml2'],
        language='c++'
    ),
]

setup(
    name='angel_configure',
    version='0.1',
    ext_modules=ext_modules,
)
