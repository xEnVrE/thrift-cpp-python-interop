#include <yarp/os/Network.h>

#include <chrono>
#include <cstdlib>
#include <iostream>
#include <string>
#include <thread>

#include <ServiceImplementation.h>

using namespace yarp::os;
using namespace std::literals::chrono_literals;


int main(int argc, char** argv)
{
    const std::string log_prefix = "[tcpi-cpp-server]";

    Network network;
    if (!network.checkNetwork())
    {
        std::cerr << log_prefix << " Error: cannot find YARP network." << std::endl;
        return EXIT_FAILURE;
    }

    /**
     * Rpc server with callbacks.
     */
    ServiceImplementation impl("/tcpi/cpp-server/rpc:i");

    /**
     * Simulate main thread here.
     */
    while (true)
        std::this_thread::sleep_for(1s);

    return EXIT_SUCCESS;
}
