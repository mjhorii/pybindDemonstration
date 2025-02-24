#include <Python.h>
#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;
namespace py = pybind11;

#include "pyMatrix.h"

py::array_t<double> test_fn(py::array_t<double, py::array::c_style | py::array::forcecast> input){
    pyMatrix a(input);
    pyMatrix b(a.shape);
    for (size_t i = 0; i < a.shape[0]; i++){
        for (size_t j = 0; j < a.shape[1]; j++){
            for (size_t k = 0; k < a.shape[2]; k++){
                b.set_data(a.read(i,j,k)*10,i,j,k);}}}
    return b.to_numpy();
}


PYBIND11_MODULE(example, m) {
    pybind11::class_<pyMatrix>(m, "pyMatrix")
        .def(pybind11::init<py::buffer>())  // Binding constructor: put the types of the inputs to the constructor
        .def("to_numpy", &pyMatrix::to_numpy);

    m.def("test_fn", &test_fn);
}


int main ()
{
    return 0;
}