from setuptools import find_packages
from setuptools import setup

setup(
    name='hexapod_msgs',
    version='0.1.0',
    packages=find_packages(
        include=('hexapod_msgs', 'hexapod_msgs.*')),
)
