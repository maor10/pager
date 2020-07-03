import glob
import os

from setuptools import setup, find_packages, Extension


BASE_C_SOURCES_DIRECTORY = os.path.join(os.path.dirname(os.path.abspath(__file__)), "cpager")
PATHS = glob.glob(BASE_C_SOURCES_DIRECTORY + '/**/*.c', recursive=True)

module = Extension("cpager", sources=PATHS)
setup(name='pager',
      version='1.0',
      packages=find_packages(),
      ext_modules=[module])
