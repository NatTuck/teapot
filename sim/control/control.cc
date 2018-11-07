
#include <iostream>

#include <gazebo/gazebo.hh>
#include <gazebo/physics/physics.hh>

using std::string;

namespace gazebo {
    class ControlPlugin : public ModelPlugin
    {
    public:
        physics::ModelPtr model;

        ControlPlugin() {}

        void
        SetSpeed(string name, double speed)
        {
            auto pid = common::PID(0.1, 0, 0);
            auto jc = model->GetJointController();
            jc->SetVelocityPID(name, pid);
            jc->SetVelocityTarget(name, speed);
        }

        void
        SetTurn(string name, double turn)
        {
            auto pid = common::PID(0.1, 0, 0);
            auto jc = model->GetJointController();
            jc->SetPositionPID(name, pid);
            jc->SetPositionTarget(name, turn);
        }

        virtual void
        Load(physics::ModelPtr model, sdf::ElementPtr sdf)
            {
                this->model = model;

                if (model->GetJointCount() == 0) {
                    std::cerr << "bad model loaded" << std::endl;
                }

                std::cerr << "hello from ControlPlugin" << std::endl;
                std::cerr << "model: " << model->GetName() << std::endl;
                for (auto joint : model->GetJoints()) {
                    auto name = joint->GetName();
                    auto sname = joint->GetScopedName();

                    if (name ==
                        std::string("cart_front_steer::wheel_rear_left_spin")) {
                        this->SetSpeed(sname, 1.0);
                    }

                    if (name ==
                        std::string("cart_front_steer::wheel_front_left_steer_spin")) {
                        this->SetTurn(sname, .0);
                    }

                    std::cerr << "joint: " << joint->GetName() << std::endl;
                }
            }
    };

    GZ_REGISTER_MODEL_PLUGIN(ControlPlugin)
}

