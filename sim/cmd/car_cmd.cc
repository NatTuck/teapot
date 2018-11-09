
#include <string>
#include <vector>

#include <gazebo/gazebo_config.h>
#include <gazebo/transport/transport.hh>
#include <gazebo/msgs/msgs.hh>
#include <gazebo/gazebo_client.hh>

using std::string;
using std::vector;

using namespace gazebo;
using ignition::math::Vector3d;

int
main(int argc, char* argv[])
{
    client::setup(argc, argv);
    transport::NodePtr node(new transport::Node());
    node->Init();

    string topic = "~/teapot0/vel_cmd";
    transport::PublisherPtr pub = node->Advertise<msgs::Vector3d>(topic);

    pub->WaitForConnection();

    msgs::Vector3d msg;
    msgs::Set(&msg, Vector3d(std::atof(argv[1]), 0, 0));

    pub->Publish(msg);

    client::shutdown();
    return 0;
}
