#ifndef PYMATRIX
#define PYMATRIX

#include <Python.h>
#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;
namespace py = pybind11;

class pyMatrix {
public:
    size_t ndim;
    size_t size;
    vector<size_t> shape;
    vector<size_t> strides;
    double *m_data;

    // Function declarations:
    pyMatrix(){}
    pyMatrix(vector<size_t> shape_);
    pyMatrix(py::array_t<double, py::array::c_style | py::array::forcecast> data);

    void set_data(py::array_t<double, py::array::c_style | py::array::forcecast> data);
    py::array_t<double> to_numpy() const;

    // Inline functions (annoying to take out of header because templated....?)
    template <typename... indices>
    void set_data(double value, indices... ind){
        //Set element at index "ind" to be equal to "value"
        int flattened_ind = 0;
        std::vector<size_t> index_list = { static_cast<size_t>(ind)... };  // Pack indices into vector
        for (size_t i = 0; i < ndim; i++) {
            assert(index_list[i] < shape[i]);
            try {if(index_list[i] > shape[i]){throw runtime_error("Invalid index for .set_data");}}
            catch (const exception &e) {cout << "Error: " << e.what() << endl; std::exit(1);} 

            flattened_ind += index_list[i]*strides[i];
        }

        m_data[flattened_ind] = value;
    }

    template <typename... indices>
    double read(indices... ind){ 
        //Return a data entry from matrix given index
        int flattened_ind = 0;
        std::vector<size_t> index_list = { static_cast<size_t>(ind)... };  // Pack indices into vector
        for (size_t i = 0; i < ndim; i++) {
            assert(index_list[i] < shape[i]);
            try {if(index_list[i] > shape[i]){throw runtime_error("Invalid index for .read");}}
            catch (const exception &e) {cout << "Error: " << e.what() << endl; std::exit(1);} 

            flattened_ind += index_list[i]*strides[i];
        }
        return m_data[flattened_ind];
    }

};

#endif
