/*
 *  Withrobot, Inc.
 *
 *  Raspberry PI example 
 *   - 2015.04.29 ('c')void
 */

#include <stdio.h>
#include <stdlib.h>

#include <vector>
#include <map>


#include "attitude.h"
extern attitude_t cube_attitude;
extern "C" int triangle_main();

#include "myahrs_plus.hpp"
using namespace WithRobot;

static const int   BAUDRATE = 115200;
static const char* DIVIDER = "1";  // 100 Hz


void handle_error(const char* error_msg)
{
    fprintf(stderr, "ERROR: %s\n", error_msg);
    exit(1);
}

void wait_for_user_input()
{
    printf("\npress enter key to quit.\n");
    char c = getchar();
    exit(1);
}

class UserAhrs : public iMyAhrsPlus
{
    Platform::Mutex lock;
    SensorData sensor_data;

public:
    int sample_count;

    UserAhrs(std::string port="", unsigned int baudrate=115200)
    : iMyAhrsPlus(port, baudrate), sample_count(0) {}
    ~UserAhrs() {}

    bool initialize() {
        bool ok = false;
        do {
            if(start() == false) break;
            if(cmd_binary_data_format("QUATERNION, IMU") == false) break;
            if(cmd_divider(DIVIDER) == false) break;
            if(cmd_mode("BC") == false) break;
            ok = true;
        } while(0);

        return ok;
    }

    inline void get_data(SensorData& data) {
        LockGuard _l(lock);
        data = sensor_data;
    }

    inline SensorData get_data() {
        LockGuard _l(lock);
        return sensor_data;
    }

    void print_attitude(int sensor_id) {
        std::string line(50, '-');
        printf("%s\n", line.c_str());

        Quaternion& q = sensor_data.quaternion;
        EulerAngle& e = sensor_data.euler_angle;
        ImuData<float>& imu = sensor_data.imu;

        printf("%04d) sensor_id %d, Quaternion(xyzw)=%.4f,%.4f,%.4f,%.4f, Angle(rpy)=%.1f, %.1f, %.1f, Accel(xyz)=%.4f,%.4f,%.4f, Gyro(xyz)=%.4f,%.4f,%.4f, Magnet(xyz)=%.2f,%.2f,%.2f\n",
                sample_count,
                sensor_id,
                q.x, q.y, q.z, q.w,
                e.roll, e.pitch, e.yaw,
                imu.ax, imu.ay, imu.az,
                imu.gx, imu.gy, imu.gz,
                imu.mx, imu.my, imu.mz);
    }

protected:
    /*
     * 	override event handler
     */
    void OnSensorData(int sensor_id, SensorData data) {
        sample_count++;
        {
            LockGuard _l(lock);
            sensor_data = data;
            sensor_data.euler_angle = sensor_data.quaternion.to_euler_angle();
            
            cube_attitude.roll  = sensor_data.euler_angle.roll;
            cube_attitude.pitch = sensor_data.euler_angle.pitch;
            cube_attitude.yaw   = sensor_data.euler_angle.yaw;
        }

        /*
         * 	do something for arrived data.
         */
        print_attitude(sensor_id);
    }

    void OnAttributeChange(int sensor_id, std::string attribute_name, std::string value) {
        printf("OnAttributeChange(id %d, %s, %s)\n", sensor_id, attribute_name.c_str(), value.c_str());
    }
};

 

/******************************************************************************************************************************
 *
 *
 *
 ******************************************************************************************************************************/

void usage(const char* prog)
{
    printf("\nusage : %s serial device  \n\t ex) $ %s /dev/ttyACM1\n\n", prog, prog);
}

void read_serial_devices_from_command_line(std::vector<std::string>& args, std::vector<std::string>& serial_device_list)
{
    for(size_t i=1; i<args.size(); i++) {
        serial_device_list.push_back(args[i]);
    }
}

int main(int argc, char* argv[]) 
{
    std::vector<std::string> args;
    for(int i=0; i<argc; i++) {
        args.push_back(std::string(argv[i]));
    }
    
    if(argc < 2) {
        printf("ERROR. need more arguments\n");
        usage(args[0].c_str());
        exit(1);
    }

    std::vector<std::string> serial_device_list;
    for(size_t i=1; i<args.size(); i++) {
        serial_device_list.push_back(args[i]);
    }

    for(size_t i=0; i<serial_device_list.size(); i++) {
        printf(" - serial device(%d) : %s\n", i, serial_device_list[i].c_str());
    }
        
    UserAhrs sensor(serial_device_list[0].c_str(), BAUDRATE);

    if(sensor.initialize() == false) {
        handle_error("initialize() returns false");
    }
    
    
#if 0
    wait_for_user_input();
#else 
	triangle_main();
#endif 

}
 

