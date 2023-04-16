import numpy
import tcpi
import time
import yarp


def yarp_matrix_to_numpy(yarp_matrix):

    matrix = numpy.zeros(shape = (yarp_matrix.rows(), yarp_matrix.cols()))
    for i in range(matrix.shape[0]):
        for j in range(matrix.shape[1]):
            matrix[i, j] = yarp_matrix[i, j]

    return matrix


def yarp_vector_to_numpy(yarp_vector):

    vector = numpy.zeros(shape = (yarp_vector.size(),))
    for i in range(vector.shape[0]):
        vector[i] = yarp_vector[i]

    return vector


def main():
    log_prefix = '[tcpi-python-client]';

    yarp.Network.init()

    service = tcpi.Service()

    rpc_client = yarp.RpcClient()
    if not rpc_client.open('/tcpi/python-client/rpc:o'):
        print(log_prefix + " Error: cannot open RPC port.")
        exit(1)

    service.yarp().attachAsClient(rpc_client)
    service.yarp().setStreamingMode(False)

    while True:
        poses = service.get_poses()
        position = service.get_position();
        distance = service.get_distance();

        print("Poses: ")
        for pose in poses:
            print(yarp_matrix_to_numpy(pose))
        print("Position: " + str(yarp_vector_to_numpy(position)))
        print("Distance: " + str(distance))

        time.sleep(1)

    exit(0)

if __name__ == '__main__':
    main()
