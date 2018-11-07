
#include <iostream>

#include <gazebo/gazebo.hh>
#include <gazebo/physics/physics.hh>

namespace gazebo {
    class ControlPlugin : public ModelPlugin
    {
    public:
        ControlPlugin() {}
        virtual void Load(physics::ModelPtr model, sdf::ElementPtr sdf)
        {
            std::cerr << "hello from ControlPlugin" << std::endl;
            std::cerr << "model: " << model->GetName() << std::endl;
            for (auto joint : model->GetJoints()) {
                std::cerr << "joint: " << joint->GetName() << std::endl;
            }
        }
    };

    GZ_REGISTER_MODEL_PLUGIN(ControlPlugin)
}

