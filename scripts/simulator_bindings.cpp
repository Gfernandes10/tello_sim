#include <pybind11/pybind11.h>
#include <pybind11/chrono.h>
#include <pybind11/stl.h>
#include "Simulator.h"
#include "../NoLinearModel_ert_rtw/NoLinearModel.h"

namespace py = pybind11;

PYBIND11_MODULE(simulator, m) {
    py::class_<NoLinearModel::ExtY>(m, "ExtY")
        .def_readonly("dx_mps", &NoLinearModel::ExtY::dx_mps)
        .def_readonly("x_m", &NoLinearModel::ExtY::x_m)
        .def_readonly("pitch_rad", &NoLinearModel::ExtY::pitch_rad)
        .def_readonly("dpitch_radps", &NoLinearModel::ExtY::dpitch_radps)
        .def_readonly("dy_mps", &NoLinearModel::ExtY::dy_mps)
        .def_readonly("y_m", &NoLinearModel::ExtY::y_m)
        .def_readonly("roll_rad", &NoLinearModel::ExtY::roll_rad)
        .def_readonly("roll_radps", &NoLinearModel::ExtY::roll_radps)
        .def_readonly("yaw_rad", &NoLinearModel::ExtY::yaw_rad)
        .def_readonly("dyaw_radps", &NoLinearModel::ExtY::dyaw_radps)
        .def_readonly("dz_mps", &NoLinearModel::ExtY::dz_mps)
        .def_readonly("z_m", &NoLinearModel::ExtY::z_m);

    py::class_<NoLinearModel::InstP>(m, "InstP")
        .def(py::init<>())
        .def_readwrite("Cx", &NoLinearModel::InstP::Cx)
        .def_readwrite("Cy", &NoLinearModel::InstP::Cy)
        .def_readwrite("pitch_K", &NoLinearModel::InstP::pitch_K)
        .def_readwrite("pitch_max", &NoLinearModel::InstP::pitch_max)
        .def_readwrite("pitch_omega", &NoLinearModel::InstP::pitch_omega)
        .def_readwrite("pitch_zeta", &NoLinearModel::InstP::pitch_zeta)
        .def_readwrite("roll_K", &NoLinearModel::InstP::roll_K)
        .def_readwrite("roll_max", &NoLinearModel::InstP::roll_max)
        .def_readwrite("roll_omega", &NoLinearModel::InstP::roll_omega)
        .def_readwrite("roll_zeta", &NoLinearModel::InstP::roll_zeta)
        .def_readwrite("yawp_K", &NoLinearModel::InstP::yawp_K)
        .def_readwrite("yawp_max", &NoLinearModel::InstP::yawp_max)
        .def_readwrite("yawp_tal", &NoLinearModel::InstP::yawp_tal)
        .def_readwrite("zp_K", &NoLinearModel::InstP::zp_K)
        .def_readwrite("zp_max", &NoLinearModel::InstP::zp_max)
        .def_readwrite("zp_tal", &NoLinearModel::InstP::zp_tal);

    py::class_<Simulator>(m, "Simulator")
        .def(py::init<>())  // Construtor
        .def("initialize", &Simulator::initialize)
        .def("run", &Simulator::run)
        .def("run_real_time", &Simulator::run_real_time)
        .def("run_non_real_time", &Simulator::run_non_real_time)
        .def("run_input_vector_based", &Simulator::run_input_vector_based, 
             py::arg("upitch"), py::arg("uroll") = std::vector<double>(), 
             py::arg("uzp") = std::vector<double>(), py::arg("uyaw") = std::vector<double>())
        .def_readwrite("is_real_time", &Simulator::is_real_time)
        .def_readwrite("base_rate", &Simulator::base_rate)
        .def_readwrite("simulation_time", &Simulator::simulation_time)
        .def("get_rtY_vector", [](Simulator &sim) {
            return std::vector<NoLinearModel::ExtY>(sim.rtY_vector.begin(), sim.rtY_vector.end());
        })
        .def("get_params", &Simulator::get_params)
        .def("set_params", &Simulator::set_params);
}