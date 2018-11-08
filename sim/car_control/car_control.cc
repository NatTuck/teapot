
#include <iostream>

#include <gazebo/gazebo.hh>
#include <gazebo/physics/physics.hh>

using std::string;
using std::vector;
using namespace gazebo;
using physics::ModelPtr;
using physics::JointControllerPtr;

class CarControlPlugin : public ModelPlugin
{
public:
    physics::ModelPtr model;
    vector<string> drive_joints;
    vector<string> steer_joints;

    transport::NodePtr node;
    transport::SubscriberPtr sub;

    CarControlPlugin() {}

    void
    SetSpeed(double speed)
    {
        auto jc = model->GetJointController();
        for (auto name: this->drive_joints) {
            jc->SetVelocityTarget(name, speed);
        }
    }

    void
    SetTurn(double turn)
    {
        auto jc = model->GetJointController();
        for (auto name: this->steer_joints) {
            jc->SetPositionTarget(name, turn);
        }
    }

    void
    SetPosPID(string name)
    {
        auto pid = common::PID(0.15, 0, 0);
        auto jc = model->GetJointController();
        jc->SetPositionPID(name, pid);
    }

    void
    SetVelPID(string name)
    {
        auto pid = common::PID(0.25, 0, 0);
        auto jc = model->GetJointController();
        jc->SetVelocityPID(name, pid);

    }

    virtual void
    Load(physics::ModelPtr model, sdf::ElementPtr sdf)
    {
        this->model = model;

        if (model->GetJointCount() == 0) {
            std::cerr << "bad model loaded" << std::endl;
        }

        auto model_name = this->model->GetName();
        auto world_name = this->model->GetWorld()->Name();

        std::cerr << "hello from ControlPlugin" << std::endl;
        std::cerr << "world: " << world_name << std::endl;
        std::cerr << "model: " << model_name << std::endl;

        for (auto joint : model->GetJoints()) {
            auto name = joint->GetName();
            auto sname = joint->GetScopedName();

            if (name == std::string("teapot::wheel_rl_drive") ||
                name == std::string("teapot::wheel_rr_drive")) {
                this->drive_joints.push_back(sname);
                this->SetVelPID(sname);
            }

            if (name == std::string("teapot::wheel_fl_steer") ||
                name == std::string("teapot::wheel_fr_steer"))
            {
                this->steer_joints.push_back(sname);
                this->SetPosPID(sname);
            }

            std::cerr << "joint: " << joint->GetName() << std::endl;
        }

        this->SetSpeed(0.0);
        this->SetTurn(0.0);

        this->node = transport::NodePtr(new transport::Node());
        this->node->Init(world_name);

        std::string topic_name = "~/" + model_name + "/vel_cmd";
        this->sub = this->node->Subscribe(
            topic_name, &CarControlPlugin::OnVelCmd, this);
    }

    void
    OnVelCmd(ConstVector3dPtr &msg)
    {
        std::cerr << "Got vel cmd: " << msg->x() << std::endl;
        this->SetSpeed(msg->x());
    }
};

GZ_REGISTER_MODEL_PLUGIN(CarControlPlugin)

