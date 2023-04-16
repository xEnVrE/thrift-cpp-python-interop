struct YarpMatrix
{
}
(
    yarp.name="yarp::sig::Matrix"
    yarp.includefile="yarp/sig/Matrix.h"
)

struct YarpVector
{
}
(
    yarp.name="yarp::sig::Vector"
    yarp.includefile="yarp/sig/Vector.h"
)

service Service
{
    list<YarpMatrix> get_poses();
    YarpVector get_position();
    double get_distance();
}