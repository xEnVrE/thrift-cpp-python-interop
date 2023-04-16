%module(directors="1", package="tcpi") tcpi

/**
 * It is important to enable Director classes in SWIG to override methods
 * of the automaticallly generated class "Service"
 */
%feature("director") Service;

%include "yarp_import.i"
%include <std_vector.i>

%{
#include <ThriftCppPythonInterop/Service.h>
#if PY_VERSION_HEX >= 0x03020000
    # define SWIGPY_SLICE_ARG(obj) ((PyObject*) (obj))
#else
    # define SWIGPY_SLICE_ARG(obj) ((PySliceObject*) (obj))
#endif
%}

%template(ListYarpMatrix) std::vector<yarp::sig::Matrix>;

%include <ThriftCppPythonInterop/Service.h>
