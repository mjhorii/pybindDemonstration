# Demonstration of pybind11

## To create and activate virtualenv environment:
If virtualenv isn't already installed:
```
pip install virtualenv
```

Once installed,
```
virtualenv pybindDemoEnv
source pybindDemoEnv/bin/activate
pip install -r requirements.txt
ipython kernel install --user --name=pybindDemoEnv
```

To check if environment is active,
```
which python
```

To deactive the environment
```
deactivate
```

## Install new python packages when environment is active with format:
```
pip install scipy
```

## To compile C++ code (python virtualenv MUST be active when compiling):
```
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make
```

## pyMatrix 
- Can be constructed with
    - pyMatrix(py::array_t<double>): A numpy array (stores data in array format on C++ side) OR
    - pyMatrix(vector<size_t>): A shape vector of (dim1_length, dim2_length….) which just allocates memory to store data in array
- Edit matrix by setting data with
    - .set_data(py::array_t<double>): A numpy array from python OR
    - .set_data(double value, indices... ind): Matrix element value and index (e.g. .set_data(5,0,1)) for 2-dim matrix or .set_data(5,0,4,1) for 3-dim matrix)
- Read data with
    - .read(indices... ind): Index
- Convert to numpy array with
    - .to_numpy()

