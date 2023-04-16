# thrift-cpp-python-interop
Examples of C++-Python interoperability using Thrift services based on SWIG.

## Requirements
- [YARP](https://yarp.it/latest/) compiled with Python bindings
- [SWIG](https://www.swig.org/)

## Thrift service definition used in this repository

The test case considered in this repository is related to the following [Thrift service](https://github.com/xEnVrE/thrift-cpp-python-interop/blob/master/cpp_library/src/thrift/service.thrift) definition:

https://github.com/xEnVrE/thrift-cpp-python-interop/blob/737b10e39b225853b42d0c9009c973f9631cf9a3/cpp_library/src/thrift/service.thrift#L1-L22

where the service `Service` offers three methods:
- `get_poses` returns a list of `yarp::sig::Matrix` 4x4 matrices representing poses
- `get_position` returns a `yarp::sig::Vector` vector representing a 3D position
- `get_distance` return a double representing a distance

## Builds the C++ library that exports the `Service` class

```console
git clone https://github.com/xEnVrE/thrift-cpp-python-interop
cd thrift-cpp-python-interop/cpp-library
mkdir build && cd build
cmake -DCMAKE_INSTALL_PREFIX=<your_install_prefix> ../
make install
```

## Builds the Python library that exports the `Service` class

**Note:** it is required to build and install the C++ library first.

**Warning:** It is suggested to build and install the library within a virtual environment.

```console
(env) git clone https://github.com/xEnVrE/thrift-cpp-python-interop
(env) cd thrift-cpp-python-interop/python-library
(env) mkdir build && cd build
(env) cmake ../
(env) make install
```
## Use the service in a C++ CMake-based project

https://github.com/xEnVrE/thrift-cpp-python-interop/blob/d765eb1868e2c9875dcf7bdf6742bc1193cd0abc/samples/cpp-client/CMakeLists.txt#L17
https://github.com/xEnVrE/thrift-cpp-python-interop/blob/d765eb1868e2c9875dcf7bdf6742bc1193cd0abc/samples/cpp-client/CMakeLists.txt#L26

> Note: the names of the target can be changed in the following:

> https://github.com/xEnVrE/thrift-cpp-python-interop/blob/d765eb1868e2c9875dcf7bdf6742bc1193cd0abc/cpp_library/CMakeLists.txt#L3
https://github.com/xEnVrE/thrift-cpp-python-interop/blob/d765eb1868e2c9875dcf7bdf6742bc1193cd0abc/cpp_library/src/CMakeLists.txt#L1

### Write a client/server node in C++

- Client: [C++ Client CMake project](https://github.com/xEnVrE/thrift-cpp-python-interop/tree/master/samples/cpp-client)
> In order to build and run the client:
> ```console
> git clone https://github.com/xEnVrE/thrift-cpp-python-interop
> cd thrift-cpp-python-interop/samples/cpp-client
> mkdir build && cd build
> make
> ./tcpi-cpp-client
> ```
> The client opens an RPC port `/tcpi/cpp-client/rpc:o`.

- Server: [C++ Server CMake project](https://github.com/xEnVrE/thrift-cpp-python-interop/tree/master/samples/cpp-server)
> In order to build and run the server:
> ```console
> git clone https://github.com/xEnVrE/thrift-cpp-python-interop
> cd thrift-cpp-python-interop/samples/cpp-server
> mkdir build && cd build
> make
> ./tcpi-cpp-server
> ```
> The server opens an RPC port `/tcpi/cpp-server/rpc:i`.

## Use the service in a Python project

### Write a client/server node in Python

- Client: [Python Client project](https://github.com/xEnVrE/thrift-cpp-python-interop/tree/master/samples/python-client)
> In order to build and run the client:
> ```console
> git clone https://github.com/xEnVrE/thrift-cpp-python-interop
> cd thrift-cpp-python-interop/samples/python-client
> python client.py
> ```
> The client opens an RPC port `/tcpi/python-client/rpc:o`.

- Server: [Python Server project](https://github.com/xEnVrE/thrift-cpp-python-interop/tree/master/samples/python-server)
> In order to build and run the server:
> ```console
> git clone https://github.com/xEnVrE/thrift-cpp-python-interop
> cd thrift-cpp-python-interop/samples/python-server
> python server.py
> ```
> The server opens an RPC port `/tcpi/python-server/rpc:i`.

## Connection between C++ and Python nodes

It is as easy as connecting the corresponding `YARP` ports using `yarp connect`.
