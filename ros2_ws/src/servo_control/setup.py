from setuptools import setup, find_packages
from glob import glob
import os

package_name = 'servo_control'

setup(
    name=package_name,
    version='0.0.0',
    packages=find_packages(include=[package_name, f"{package_name}.*"]),
    data_files=[
        (os.path.join('share', package_name), ['package.xml']),
        (os.path.join('share', package_name, 'launch'), glob('launch/*.py')),
        (os.path.join('share', 'ament_index', 'resource_index', 'packages'), [f'resource/{package_name}']),
    ],
    install_requires=[
        'setuptools',
        'adafruit-circuitpython-pca9685',
        'adafruit-blinka',
    ],
    zip_safe=True,
    maintainer='Your Name',
    maintainer_email='your_email@example.com',
    description='Servo control package for hexapod robot',
    license='MIT',
    entry_points={
        'console_scripts': [
            'servo_control_node = servo_control.servo_control_node:main',
            'calibrate_servos = servo_control.utilities.calibrate_servos:main',
        ],
    },
)
