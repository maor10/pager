import os

from setuptools import setup, find_packages, Extension


module = Extension("cpager", sources=["cpager/cpager.c"])

setup(name='pager',
      version='1.0',
      packages=find_packages(),
      ext_modules=[module])
