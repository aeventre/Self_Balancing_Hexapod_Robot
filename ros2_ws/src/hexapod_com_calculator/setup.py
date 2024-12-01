from setuptools import setup
from pybind11.setup_helpers import Pybind11Extension, build_ext

ext_modules = [
    Pybind11Extension(
        "com_calculator",
        ["src/com_calculator.cpp", "src/bindings.cpp"],
    ),
]

setup(
    name="hexapod_com_calculator",
    version="0.1.0",
    author="Alec Ventresca",
    ext_modules=ext_modules,
    cmdclass={"build_ext": build_ext},
    packages=["hexapod_com_calculator"],
    zip_safe=False,
)
