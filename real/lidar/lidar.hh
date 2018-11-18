#ifndef LIDAR_H
#define LIDAR_H

#include <stdint.h>

#include <string>
#include <vector>

#include <thread>
#include <mutex>
#include <atomic>

#include <rplidar.h>
using rp::standalone::rplidar::RPlidarDriver;
//using rp::standalone::rplidar::rplidar_response_measurement_node_hq_t;
//using rp::standalone::rplidar::rplidar_response_device_info_t;

struct LidarRay {
    float dst;
    float ang;
};

class Lidar {
public:
    Lidar(std::string path = "/dev/ttyUSB0", uint32_t baud = 115200);
    ~Lidar();

    // main thread API
    void start();
    void stop();
    std::vector<LidarRay> get_scan();

    // in worker thread
    void worker_main();
    std::vector<LidarRay> do_scan();

public:
    std::string dev_path;
    uint32_t dev_baud;
    RPlidarDriver* drv;
    rplidar_response_device_info_t dev_info;
    rplidar_response_measurement_node_hq_t nodes[8192];
    size_t count = 8192;

    std::thread worker;
    std::mutex lock;
    std::vector<LidarRay> data;
    std::atomic<bool> done;
};




#endif
