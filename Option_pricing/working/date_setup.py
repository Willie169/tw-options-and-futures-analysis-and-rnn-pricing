from setuptools import setup, Extension
import pybind11

include_dirs = [pybind11.get_include()]

date_module = Extension(
    'date',
    sources=['date.cpp'],
    include_dirs=include_dirs,
    language='c++'
)

setup(
    name='date',
    ext_modules=[date_module],
    zip_safe=False,
)
