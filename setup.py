from setuptools import setup
from setuptools import find_packages

from distutils.extension import Extension

setup(
    name='fuzzy-hash',
    version='0.0.1',
    python_requires='>=3.5',
    packages=find_packages(),
    ext_modules=[
        Extension(
            "fuzzy_hash.lib.core",
            [
                'fuzzy_hash/lib/fuzzy.c',
                'fuzzy_hash/lib/edit_dist.c',
            ])
    ],
)
