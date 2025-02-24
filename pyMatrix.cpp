#include <Python.h>
#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;
namespace py = pybind11;

#include "pyMatrix.h"


pyMatrix::pyMatrix(vector<size_t> shape_){
    //Initialize as empty matrix with shape vector containing number of elements of each dimension
    shape = shape_;

    ndim = shape.size();
    shape.resize(ndim, 0);
    strides.resize(ndim, 0);

    size = 1;
    for (int i = ndim-1; i >= 0; i--) {
        strides[i] = (i == ndim-1) ? 1 : shape[i+1]*strides[i+1];
        size = size*shape[i];
    }

    m_data = new double[size];
}

pyMatrix::pyMatrix(py::array_t<double, py::array::c_style | py::array::forcecast> data){
    set_data(data);
}

void pyMatrix::set_data(py::array_t<double, py::array::c_style | py::array::forcecast> data){
    //Set data with numpy matrix
    auto buf = data.request();
    double *ptr = static_cast<double *>(buf.ptr); //ONLY WORKS FOR NUMPY ARRAY WITH DATA TYPE DOUBLE
    size = buf.size;
    ndim = buf.ndim;
    shape.resize(ndim, 0);
    strides.resize(ndim, 0);

    for (int i = ndim-1; i >= 0; i--) {
        shape[i] = buf.shape[i];
        strides[i] = (i == ndim-1) ? 1 : shape[i+1]*strides[i+1];
    }

    m_data = new double[size];
    for (size_t i = 0; i < size; i++) {
        m_data[i] = ptr[i];
    }
}

py::array_t<double> pyMatrix::to_numpy() const {

    vector<size_t> strides_bytes(ndim);
    for (size_t i =0; i<ndim; i++){
        strides_bytes[i] = strides[i]*sizeof(double);
    }

    return py::array_t<double>(
        shape,            // Shape
        strides_bytes,    // Strides
        m_data            // Data pointer
    );
}