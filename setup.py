from setuptools import setup, Extension
from pybind11.setup_helpers import Pybind11Extension, build_ext

ext_modules = [
    Pybind11Extension(
        "simulator",
        [
            "scripts/simulator_bindings.cpp",
            "scripts/Simulator.cpp",
            "NoLinearModel_ert_rtw/NoLinearModel.cpp",  # Adicione este arquivo
            # Inclua outros arquivos necessários do diretório NoLinearModel_ert_rtw/
        ],
        include_dirs=[".", "NoLinearModel_ert_rtw"],  # Adicione o diretório de headers
        language="c++",
    ),
]

setup(
    name="simulator",
    ext_modules=ext_modules,
    cmdclass={"build_ext": build_ext},
)