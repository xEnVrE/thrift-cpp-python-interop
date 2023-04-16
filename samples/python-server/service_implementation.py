import tcpi
import yarp

class ServiceImplementation(tcpi.Service):

    def __init__(self, port_name):

        log_prefix = '[tcpi-python-server::ServiceImplementation]'

        super(ServiceImplementation, self).__init__()

        self.rpc_server_ = yarp.RpcServer()
        if not self.rpc_server_.open(port_name):
            print(log_prefix + " Error: cannot open RPC port.")
            exit(1)

        super(ServiceImplementation, self).yarp().attachAsServer(self.rpc_server_)


    def get_poses(self):

        pose_0 = yarp.Matrix(4, 4)
        pose_0[0, 3] = 1.0;
        pose_0[1, 3] = 2.0;
        pose_0[2, 3] = 3.0;

        poses = []
        poses.append(pose_0)

        return poses


    def get_position(self):

        position = yarp.Vector(3)
        position[0] = 1.0
        position[1] = 2.0
        position[2] = 3.0

        return position


    def get_distance(self):

        return 1.0
