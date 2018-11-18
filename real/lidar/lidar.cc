
#include <exception>
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>

#include <math.h>

#include "lidar.hh"

using namespace rp::standalone::rplidar;

using std::string;
using std::vector;

using std::thread;
using std::mutex;
using std::lock_guard;

static bool
assert_ok(uint32_t rv)
{
    if (IS_FAIL(rv) && rv != RESULT_OPERATION_TIMEOUT) {
        throw std::runtime_error("laser op failed");
    }
}

Lidar::Lidar(string path, uint32_t baud)
    : dev_path(path), dev_baud(baud), done(false)
{
    uint32_t retv;

    this->drv = RPlidarDriver::CreateDriver(DRIVER_TYPE_SERIALPORT);

    retv = this->drv->connect(this->dev_path.c_str(), this->dev_baud);
    assert_ok(retv);

    retv = this->drv->getDeviceInfo(this->dev_info);
    assert_ok(retv);

    rplidar_response_device_health_t health;
    retv = this->drv->getHealth(health);
    assert_ok(retv);
    if (health.status != RPLIDAR_STATUS_OK) {
        throw std::runtime_error("lidar health");
    }
}

Lidar::~Lidar()
{
    this->stop();
}

void
Lidar::start()
{
    this->worker = thread([=](){ this->worker_main(); });
}

void
Lidar::stop()
{
    this->done.store(true);
    this->worker.join();
}

vector<LidarRay>
Lidar::get_scan()
{
    lock_guard<mutex> _guard(this->lock);
    vector<LidarRay> ys;
    for (LidarRay& xx : this->data) {
        ys.push_back(xx);
    }
    return ys;
}

void
Lidar::worker_main()
{
    RplidarScanMode scanMode;
    this->drv->startMotor();
    this->drv->startScan(false, true, 0, &scanMode);

    while (!this->done.load()) {
        auto xs = this->do_scan();
        {
            lock_guard<mutex> _guard(this->lock);
            this->data = xs;
        }
    }

    this->drv->stop();
    this->drv->stopMotor();
    RPlidarDriver::DisposeDriver(this->drv);
}

vector<LidarRay>
Lidar::do_scan()
{
    uint32_t retv;

    retv = this->drv->grabScanDataHq(this->nodes, this->count);
    assert_ok(retv);

    this->drv->ascendScanData(this->nodes, this->count);

    vector<LidarRay> ys;
    for (int ii = 0; ii < count; ++ii) {
        LidarRay yy;
        yy.dst = (nodes[ii].dist_mm_q2 / 1000.0f) / (1<<2);
        yy.ang = (nodes[ii].angle_z_q14 * (M_PI/2)) / (1 << 14);
        ys.push_back(yy);
    }
    return ys;
}

