from setuptools import setup

package_name = 'hexapod_kinematics_py'

setup(
    name=package_name,
    version='0.0.0',
    packages=[package_name],
    data_files=[
        ('share/ament_index/resource_index/packages',
         ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='Your Name',
    maintainer_email='your_email@example.com',
    description='Hexapod Kinematics Python Package',
    license='MIT',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
            'ik_node = hexapod_kinematics_py.ik_node:main',
            'kinematics = hexapod_kinematics_py.kinematics:main'
        ],
    },
)
