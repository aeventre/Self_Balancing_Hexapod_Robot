from setuptools import setup
from setuptools import find_packages

package_name = 'hexapod_com_calculator'

setup(
    name=package_name,
    version='0.1.0',
    packages=find_packages(),
    install_requires=['setuptools', 'numpy', 'scipy'],  # Add any dependencies here
    zip_safe=True,
    maintainer='Your Name',
    maintainer_email='your.email@example.com',
    description='A package for calculating the center of mass of a hexapod robot.',
    license='Apache-2.0',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
            'com_calculator = hexapod_com_calculator.com_node:main',
        ],
    },
    data_files=[
        ('share/ament_index/resource_index/packages',
         ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
    ],
)
