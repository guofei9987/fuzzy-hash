from setuptools import setup
from setuptools import find_packages

from distutils.extension import Extension
import os

this_directory = os.path.abspath(os.path.dirname(__file__))


# 读取 README
def read_file(filename):
    with open(os.path.join(this_directory, filename), encoding='utf-8') as f:
        long_description = f.read()
    return long_description


setup(
    name='fuzzy-hash',
    version='0.0.3',
    python_requires='>=3.5',
    packages=find_packages(),
    ext_modules=[
        Extension(
            name="fuzzy_hash.lib.core",
            sources=[
                'fuzzy_hash/lib/fuzzy.c',
                'fuzzy_hash/lib/edit_dist.c',
            ])
    ],
    description='Fuzzy Hash in python',
    # long_description=read_file('README.md'),
)
