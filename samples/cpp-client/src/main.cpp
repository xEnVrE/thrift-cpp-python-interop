#include <yarp/os/Network.h>
#include <yarp/os/RpcClient.h>

#include <chrono>
#include <cstdlib>
#include <iostream>
#include <string>
#include <thread>

#include <ThriftCppPythonInterop/Service.h>

using namespace yarp::os;
using namespace std::literals::chrono_literals;


int main(int argc, char** argv)
{
    const std::string log_prefix = "[tcpi-cpp-client]";

    Network network;
    if (!network.checkNetwork())
    {
        std::cerr << log_prefix << " Error: cannot find YARP network." << std::endl;
        return EXIT_FAILURE;
    }

    Service service;

    RpcClient rpc_client;
    if (!rpc_client.open("/tcpi/cpp-client/rpc:o"))
    {
        std::cerr << log_prefix << " Error: cannot open RPC port." << std::endl;
        return EXIT_FAILURE;
    }

    service.yarp().attachAsClient(rpc_client);
    service.yarp().setStreamingMode(false);

    while (true)
    {
        auto poses = service.get_poses();
        auto position = service.get_position();
        auto distance = service.get_distance();

        std::cout << "Received " << poses.size() << " poses." << std::endl;
        std::size_t i = 0;
        for (const auto& pose : poses)
        {
            std::cout << "Pose #" << i++ << std::endl;
            std::cout << pose.toString() << std::endl;
        }
        std::cout << "Position " << position.toString() << std::endl;
        std::cout << "Distance " << distance << std::endl;

        std::this_thread::sleep_for(1s);
    }

    return EXIT_SUCCESS;
}
