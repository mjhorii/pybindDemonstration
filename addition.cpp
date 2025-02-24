#include <pybind11/pybind11.h>

namespace py = pybind11;

int add(int i, int j) {
    return i + j;
}

class sum{
	public:
    int i;
    int j;

	sum(int i_, int j_) {i = i_; j = j_;}

    int run() {return i + j;}
};

PYBIND11_MODULE(module_name, m) {
    //Add class "sum":
	pybind11::class_<sum>(m, "python_class_call_name")
		.def(pybind11::init<int, int>()) // Binding constructor: put the types of the inputs to the constructor
		.def("python_method_call_name", &sum::run); // Binding method
    
    //Add function "add":
    m.def("python_function_name", &add, // Necessary binding info
    "Function that adds two numbers", py::arg("i"), py::arg("j")); // Optional documentation and argument names

    m.doc() = "Module description";
}

//Equivalently, can use binding code with slightly different formatting:

// PYBIND11_MODULE(module_name, m) {
//     //Add class "sum":
// 	pybind11::class_<sum> pybind_class_name(m, "python_class_call_name");
// 	pybind_class_name.def(pybind11::init<int, int>()); // Binding constructor: put the types of the inputs to the constructor
// 	pybind_class_name.def("python_method_call_name", &sum::run); // Binding method

//     //Add function "add":
//     m.def("add", &add, // Necessary binding info
//     "A function that adds two numbers", py::arg("i"), py::arg("j")); // Optional documentation and argument names

// 	m.doc() = "Module description";
// }