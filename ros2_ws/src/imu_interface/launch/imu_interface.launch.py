from setuptools import setup

package_name = 'hexapod_imu_interface'

setup(
    name=package_name,
    version='0.1.0',
    packages=[package_name],
    install_requires=['setuptools', 'smbus2'],
    zip_safe=True,
    maintainer='user',
    maintainer_email='user@example.com',
    description='IMU interface package for hexapod robot',
    license='Apache 2.0',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
            'imu_interface_node = imu_interface.imu_interface_node:main',
        ],
    },
)
