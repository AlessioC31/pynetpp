from glob import glob
from setuptools import setup
from pybind11.setup_helpers import ParallelCompile, Pybind11Extension

ext_modules = [
    Pybind11Extension(
        "pynetpp_bindings",
        sorted(glob("extras/bindings/*.cc")) + sorted(glob("model/*.cc")),  # Sort source files for reproducibility
        include_dirs=["/opt/omnetpp-6.0/include", "/opt/omnetpp-6.0/src", "/opt/inet/src", "/opt/flora/src","./include"],
        libraries=["oppenvir", "oppsim", "INET", "flora"],
        library_dirs=["/opt/omnetpp-6.0/lib", "/opt/inet/src", "/opt/flora/src"],
        extra_link_args=["-Wl,--no-as-needed"] # TODO: to fix
    ),
]

with ParallelCompile(default=0):
    setup(name="pynetpp", packages=["pynetpp"], ext_modules=ext_modules)