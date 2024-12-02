from setuptools import setup

package_name = 'hexapod_com_calculator'

setup(
    name=package_name,
    version='0.1.0',
    packages=[package_name],
    install_requires=[
        'setuptools',
        'rclpy',
        'geometry_msgs',
        'std_msgs',
        'hexapod_msgs'
    ],
    zip_safe=True,
    maintainer='Your Name',
    maintainer_email='aeventre@buffalo.edu',
    description='Node to compute the center of mass (CoM) for the hexapod robot.',
    license='Apache-2.0',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
            'com_calculator = hexapod_com_calculator.com_calculator:main'
        ],
    },
)
