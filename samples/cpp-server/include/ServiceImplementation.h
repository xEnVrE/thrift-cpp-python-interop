#include <yarp/os/RpcServer.h>
#include <yarp/sig/Matrix.h>
#include <yarp/sig/Vector.h>


#include <ThriftCppPythonInterop/Service.h>


class ServiceImplementation : public Service
{
public:
    ServiceImplementation(const std::string& port_name);

    ~ServiceImplementation() = default;

    /**
     * Implement Service public interface
     */
    std::vector<yarp::sig::Matrix> get_poses();

    yarp::sig::Vector get_position();

    double get_distance();

private:

    yarp::os::RpcServer rpc_server_;

    const std::string log_prefix_ = "[tcpi-cpp-server::ServiceImplementation]";
};
