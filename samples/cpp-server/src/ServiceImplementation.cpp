#include <ServiceImplementation.h>

using namespace yarp::sig;


ServiceImplementation::ServiceImplementation(const std::string& port_name)
{
    if (!rpc_server_.open(port_name))
        throw(std::runtime_error(log_prefix_ + " Error: cannot open RPC port."));

    this->yarp().attachAsServer(rpc_server_);
}


std::vector<yarp::sig::Matrix> ServiceImplementation::get_poses()
{
    // Test pose
    Matrix pose_0(4, 4);
    pose_0(0, 3) = 1.0;
    pose_0(1, 3) = 2.0;
    pose_0(2, 3) = 3.0;

    std::vector<Matrix> poses;
    poses.push_back(pose_0);

    return poses;
}


yarp::sig::Vector ServiceImplementation::get_position()
{
    Vector position(3);
    position(0) = 1.0;
    position(1) = 2.0;
    position(2) = 3.0;

    return position;
}


double ServiceImplementation::get_distance()
{
    return 1.0;
}
