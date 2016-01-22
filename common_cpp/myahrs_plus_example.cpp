//*****************************************************************************
//
// Copyright (c) 2014 Withrobot, Inc.  All rights reserved.
//
// Software License Agreement
//
// Withrobot, Inc.(Withrobot) is supplying this software for use solely and
// exclusively on Withrobot's products.
//
// The software is owned by Withrobot and/or its suppliers, and is protected
// under applicable copyright laws.  All rights are reserved.
// Any use in violation of the foregoing restrictions may subject the user
// to criminal sanctions under applicable laws, as well as to civil liability
// for the breach of the terms and conditions of this license.
//
// THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
// OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
// MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
// WITHROBOT SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL,
// OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
//
//*****************************************************************************

/*
 *  User Application Example
 *   - 2014.07.13 ('c')void
 *   - 2014.07.28 ('c')void
 *      - ver 1.0
 *   - 2015.04.30 ('c')void
 *      - add example 7
 *   - 2016.01.22 ('c')gnohead
 *   	- add example 8
 */

#include <stdio.h>
#include <stdlib.h>

#include <vector>
#include <map>

#include "myahrs_plus.hpp"
using namespace WithRobot;

static const int BAUDRATE = 115200;

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

/******************************************************************************************************************************
 *
 *  EXAMPLE 1
 *
 ******************************************************************************************************************************/

void ex1_synchronous_read_ascii(const char* serial_device, int baudrate)
{
    printf("\n### %s() ###\n", __FUNCTION__);

    MyAhrsPlus sensor;
    SensorData sensor_data;
    uint32_t sample_count = 0;

    /*
     * 	start communication with the myAHRS+.
     */
    if(sensor.start(serial_device, baudrate) == false) {
        handle_error("start() returns false");
    }

    /*
     *  set ascii output format
     *   - select euler angle
     */
    if(sensor.cmd_ascii_data_format("RPY") == false) {
        handle_error("cmd_ascii_data_format() returns false");
    }

    /*
     *  set divider
     *   - output rate(Hz) = max_rate/divider
     */
    if(sensor.cmd_divider(DIVIDER) ==false) {
        handle_error("cmd_divider() returns false");
    }

    /*
     *  set transfer mode
     *   - AC : ASCII Message & Continuous mode
     */
    if(sensor.cmd_mode("AC") ==false) {
        handle_error("cmd_mode() returns false");
    }

    while(sample_count < 300) {
        if(sensor.wait_data() == true) { // waiting for new data
        	// read counter
            sample_count = sensor.get_sample_count();

            // copy sensor data
            sensor.get_data(sensor_data);

            // print euler angle
            EulerAngle& e = sensor_data.euler_angle;
            printf("%04d) EulerAngle (roll = %.2f, pitch = %.2f, yaw = %.2f)\n", sample_count, e.roll, e.pitch, e.yaw);
        }
    }

    /*
     * 	stop communication
     */
    sensor.stop();

    printf("END OF TEST(%s)\n\n", __FUNCTION__);
}

/******************************************************************************************************************************
 *
 *  EXAMPLE 2
 *
 ******************************************************************************************************************************/
void ex2_synchronous_read_binary(const char* serial_device, int baudrate)
{
    printf("\n### %s() ###\n", __FUNCTION__);

    MyAhrsPlus sensor;
    SensorData sensor_data;
    uint32_t sample_count = 0;

    /*
     * 	start communication with the myAHRS+.
     */
    if(sensor.start(serial_device, baudrate) == false) {
        handle_error("start() returns false");
    }

    /*
     *  set binary output format
     *   - select Quaternion and IMU data
     */
    if(sensor.cmd_binary_data_format("QUATERNION, IMU") == false) {
        handle_error("cmd_binary_data_format() returns false");
    }

    /*
     *  set divider
     *   - output rate(Hz) = max_rate/divider
     */
    if(sensor.cmd_divider(DIVIDER) ==false) {
        handle_error("cmd_divider() returns false");
    }

    /*
     *  set transfer mode
     *   - BC : Binary Message & Continuous mode
     */
    if(sensor.cmd_mode("BC") ==false) {
        handle_error("cmd_mode() returns false");
    }

    while(sample_count < 300) {
        if(sensor.wait_data() == true) { // waiting for new data
        	/*
        	 * copy sensor data
        	 */
            sample_count = sensor.get_sample_count();
            sensor.get_data(sensor_data);

            /*
             * print quaternion & imu data
             */
            Quaternion& q = sensor_data.quaternion;
            ImuData<float>& imu = sensor_data.imu;
            printf("%04d) Quaternion(xyzw)=%.4f,%.4f,%.4f,%.4f, Accel(xyz)=%.4f,%.4f,%.4f, Gyro(xyz)=%.4f,%.4f,%.4f, Magnet(xyz)=%.2f,%.2f,%.2f\n",
                    sample_count,
                    q.x, q.y, q.z, q.w,
                    imu.ax, imu.ay, imu.az,
                    imu.gx, imu.gy, imu.gz,
                    imu.mx, imu.my, imu.mz);

            /*
             * convert quaternion to direction cosine matrix
             */
            DirectionCosineMatrix dcm;
            dcm.set(q);
            printf("%04d) Direction cosine matrix %s\n", sample_count, dcm.to_string().c_str());

            /*
             * convert quaternion to euler angle
             */
            EulerAngle euler_angle_from_quaternion = q.to_euler_angle();
            printf("%04d) euler angle from quaternion %s\n", sample_count, euler_angle_from_quaternion.to_string().c_str());

            EulerAngle euler_angle_from_dcm = dcm.to_euler_angle();
            printf("%04d) euler angle from dcm %s\n", sample_count, euler_angle_from_dcm.to_string().c_str());
        }
    }

    /*
     * 	stop communication
     */
    sensor.stop();

    printf("END OF TEST(%s)\n\n", __FUNCTION__);
}


/******************************************************************************************************************************
 *
 *  EXAMPLE 3
 *
 ******************************************************************************************************************************/
void ex3_callback_attribute(void* context, int sensor_id, const char* attribute_name, const char* value)
{
    printf(" ## sensor_id %d, Attribute has been changed(%s, %s)\n", sensor_id, attribute_name, value);
}

void ex3_callback_data(void* context, int sensor_id, SensorData* sensor_data)
{
    int* counter = (int*)context;
    (*counter)++;

    Quaternion& q = sensor_data->quaternion;
    ImuData<float>& imu = sensor_data->imu;

    printf("%04d) sensor_id %d, Quaternion(xyzw)=%.4f,%.4f,%.4f,%.4f, Accel(xyz)=%.4f,%.4f,%.4f, Gyro(xyz)=%.4f,%.4f,%.4f, Magnet(xyz)=%.2f,%.2f,%.2f\n",
            *counter,
            sensor_id,
            q.x, q.y, q.z, q.w,
            imu.ax, imu.ay, imu.az,
            imu.gx, imu.gy, imu.gz,
            imu.mx, imu.my, imu.mz);
}

void ex3_asynchronous_read_binary(const char* serial_device, int baudrate)
{
    printf("\n### %s() ###\n", __FUNCTION__);

    MyAhrsPlus sensor;

    int sample_counter = 0;

    /*
     * 	register a callback function to attribute changed event.
     */
    sensor.register_attribute_callback(ex3_callback_attribute, 0);

    /*
     * 	register a callback function to new data arrived event.
     */
    sensor.register_data_callback(ex3_callback_data, &sample_counter);

    /*
     * 	start communication with the myAHRS+.
     */
    if(sensor.start(serial_device, baudrate) == false) {
        handle_error("start() returns false");
    }

    /*
     *  set binary output format
     *   - select Quaternion and IMU data
     */
    if(sensor.cmd_binary_data_format("QUATERNION, IMU") == false) {
        handle_error("cmd_binary_data_format() returns false");
    }

    /*
     *  set divider
     *   - output rate(Hz) = max_rate/divider
     */
    if(sensor.cmd_divider(DIVIDER) ==false) {
        handle_error("cmd_divider() returns false");
    }

    /*
     *  set transfer mode
     *   - BC : BINARY Message & Continuous mode
     */
    if(sensor.cmd_mode("BC") ==false) {
        handle_error("cmd_mode() returns false");
    }

    while(sample_counter < 100) {
        Platform::msleep(100);
    }

    /*
     * 	stop communication
     */
    sensor.stop();

    printf("END OF TEST(%s)\n\n", __FUNCTION__);
}

/******************************************************************************************************************************
 *
 *  EXAMPLE 4
 *
 ******************************************************************************************************************************/
void ex4_read_all_properties(const char* serial_device, int baudrate)
{
    printf("\n### %s() ###\n", __FUNCTION__);

    std::string line(120, '#');

    MyAhrsPlus sensor;

    /*
     * 	start communication with the myAHRS+.
     */
    if(sensor.start(serial_device, baudrate) == false) {
        handle_error("start() returns false");
    }

    Platform::msleep(100);

    /*
     *  show all attributes
     */
    std::vector<std::string> attribute_list = sensor.get_attribute_list();
    printf("%s\n", line.c_str());
    for(size_t i=0; i<attribute_list.size(); i++) {
        std::string value;
        if(sensor.get_attribute(attribute_list[i].c_str(), value) == true) {
            printf("#  %s : %s\n", attribute_list[i].c_str(), value.c_str());
        }
    }
    printf("%s\n", line.c_str());

    /*
     * 	stop communication
     */
    sensor.stop();

    printf("END OF TEST(%s)\n\n", __FUNCTION__);
}


/******************************************************************************************************************************
 *
 *  EXAMPLE 5
 *
 *  You can make own class inherited from iMyAhrsPlus class.
 *
 ******************************************************************************************************************************/

class UserDefinedAhrs : public iMyAhrsPlus
{
    Platform::Mutex lock;
    SensorData sensor_data;

public:
    int sample_count;

    UserDefinedAhrs(std::string port="", unsigned int baudrate=115200)
    : iMyAhrsPlus(port, baudrate), sample_count(0) {}
    ~UserDefinedAhrs() {}

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

    void do_something(int sensor_id) {
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
        }

        /*
         * 	do something for arrived data.
         */
        do_something(sensor_id);
    }

    void OnAttributeChange(int sensor_id, std::string attribute_name, std::string value) {
        printf("OnAttributeChange(id %d, %s, %s)\n", sensor_id, attribute_name.c_str(), value.c_str());
    }
};


void ex5_user_defined_class(const char* serial_device, int baudrate)
{
    printf("\n### %s() ###\n", __FUNCTION__);

    UserDefinedAhrs sensor(serial_device, baudrate);

    if(sensor.initialize() == false) {
        handle_error("initialize() returns false");
    }

    while(sensor.sample_count < 300) {
        Platform::msleep(100);
    }

    printf("END OF TEST(%s)\n\n", __FUNCTION__);
}


/******************************************************************************************************************************
 *
 *  EXAMPLE 6
 *
 *  This example shows you how to make an object that handle multiple sensors.
 *
 ******************************************************************************************************************************/

class MyAhrsArray
{
    class AhrsElement : public iMyAhrsPlus
    {
        MyAhrsArray* owner;
        Platform::Mutex lock;
        SensorData sensor_data;

    public:
        int sample_count;

        AhrsElement(MyAhrsArray* _owner, std::string port, unsigned int baudrate)
        : iMyAhrsPlus(port, baudrate), owner(_owner), sample_count(0){}
        ~AhrsElement() {}

        bool initialize() {
            bool ok = false;
            do {
                if(start() == false) break;
                if(cmd_binary_data_format("QUATERNION, IMU") == false) break;
                if(cmd_ascii_data_format("QUATIMU") == false) break;
                if(cmd_divider(DIVIDER) == false) break;
                if(cmd_mode("BC") == false) break;
                ok = true;
            } while(0);
            return ok;
        }

        SensorData get_data() {
            LockGuard _l(lock);
            return sensor_data;
        }

    protected:
        void OnSensorData(int sensor_id, SensorData d) {
            {
                LockGuard _l(lock);
                sample_count++;
                sensor_data = d;
                sensor_data.euler_angle = sensor_data.quaternion.to_euler_angle();
            }
            owner->OnSensorData(this, sensor_id, sensor_data);
        }

        void OnAttributeChange(int sensor_id, std::string attribute_name, std::string value) {
            owner->OnAttributeChange(this, sensor_id, attribute_name, value);
        }
    };

    std::vector<AhrsElement*> sensor_array;
    std::map<int, AhrsElement*> sensor_map;
    bool activated;
    bool debug;

public:
    MyAhrsArray(std::vector<std::string> port_list, int baudrate, bool dbg) : activated(false), debug(dbg) {
        for(size_t i=0; i<port_list.size(); i++) {
            sensor_array.push_back(new AhrsElement(this, port_list[i], baudrate));
        }
    }

    ~MyAhrsArray() {
        stop();
        for(size_t i=0; i<sensor_array.size(); i++) {
            delete sensor_array[i];
        }
    }

    bool initialize() {
        if(activated) {
            return true;
        }

        activated = false;
        char str_id[16];
        for(size_t i=0; i<sensor_array.size(); i++) {
            if(sensor_array[i]->initialize() == true) {
                // assign new id to distinguish data event
                sprintf(str_id, "%d", i);
                sensor_array[i]->cmd_id(str_id);
                sensor_map[i] = sensor_array[i];
                Platform::msleep(10);
            }
            else {
                stop();
                return false;
            }
        }

        for(size_t i=0; i<sensor_array.size(); i++) {
            sensor_array[i]->sample_count = 0;
        }

        activated = true;
        return true;
    }

    void stop() {
        for(size_t i=0; i<sensor_array.size(); i++) {
            sensor_array[i]->stop();
        }
        sensor_map.clear();
        activated = false;
    }

    bool get_data(int sensor_id, SensorData& data) {
        std::map<int, AhrsElement*>::iterator it = sensor_map.find(sensor_id);
        if(it == sensor_map.end()) {
            return false;
        }
        else {
            data = it->second->get_data();
            return true;
        }
    }

    void show_all(int seq)  {
        for(size_t i=0; i<sensor_array.size(); i++) {
            printf("### DATA(seq %d, sensor_id=%d, sample count=%d): Q(%s)\n", seq, sensor_array[i]->get_sensor_id(), sensor_array[i]->sample_count, sensor_array[i]->get_data().quaternion.to_string().c_str());
        }
        printf("\n");
    }

protected:
    void OnSensorData(AhrsElement* sensor, int sensor_id, SensorData& data) {
        if(activated == false) {
            return;
        }

        if(debug) {
            printf("OnSensorData(sensor_id=%d, sample count=%d): Q(%s)\n", sensor_id, sensor->sample_count, data.quaternion.to_string().c_str());
        }
    }

    void OnAttributeChange(AhrsElement* sensor, int sensor_id, std::string& attribute_name, std::string& value) {
        if(activated == false) {
            return;
        }

        printf("OnAttributeChange(sensor_id=%d, %s, %s)\n", sensor_id, attribute_name.c_str(), value.c_str());
    }
};


void ex6_multiple_sensors(std::vector<std::string>& serial_device_list, int baudrate)
{
    printf("\n### %s() ###\n", __FUNCTION__);

    static const bool debug = false;
    MyAhrsArray sensor_array(serial_device_list, baudrate, debug);

    if(sensor_array.initialize() == false) {
        handle_error("activate() returns false");
    }

    int sequence = 0;
    for(int i=0; i<5000; i++) {
        Platform::msleep(20);
        sensor_array.show_all(sequence++);
    }

    sensor_array.stop();

    printf("END OF TEST(%s)\n\n", __FUNCTION__);
}


/******************************************************************************************************************************
 *
 *  EXAMPLE 7
 *
 *  Coordinate Transformation
 *
 ******************************************************************************************************************************/

class MyAhrsHasOwnCoordinate : public iMyAhrsPlus
{
    Platform::Mutex lock;
    SensorData sensor_data_original;
    SensorData sensor_data_transformed;

    /*
     *  coordinate transformation quaternion
     *    sensor -> user
     */
    Quaternion q_s_to_u;
    Quaternion q_s_to_u_conj;

public:
    int sample_count;

    MyAhrsHasOwnCoordinate(std::string port="", unsigned int baudrate=115200)
    : iMyAhrsPlus(port, baudrate), sample_count(0) {
        /*
         *  coordinate transform matrix
         *   -  rotate 180 degrees along the x axis
         *  [1,  0,  0;
         *   0, -1,  0;
         *   0,  0, -1]
         */
        DirectionCosineMatrix dcm("1, 0, 0,  0, -1, 0,  0, 0, -1");
        q_s_to_u = dcm.to_quaternion();

        q_s_to_u_conj = q_s_to_u;
        q_s_to_u_conj = q_s_to_u.conj();
    }
    ~MyAhrsHasOwnCoordinate() {}

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
        data = sensor_data_transformed;
    }

    inline SensorData get_data() {
        LockGuard _l(lock);
        return sensor_data_transformed;
    }

protected:
    /*
     *  override event handler
     */
    void OnSensorData(int sensor_id, SensorData data) {
        sample_count++;
        {
            LockGuard _l(lock);
            sensor_data_original = data;
            sensor_data_transformed = data;

            /*
             *  original orientation
             */
            sensor_data_original.euler_angle = sensor_data_original.quaternion.to_euler_angle();

            /*
             *  coordinate transformation
             */

            // attitude
            sensor_data_transformed.quaternion = Quaternion::product(sensor_data_original.quaternion, q_s_to_u_conj);
            sensor_data_transformed.euler_angle = sensor_data_transformed.quaternion.to_euler_angle();

            // imu data
            coordinate_transform(sensor_data_transformed.imu.ax, sensor_data_transformed.imu.ay, sensor_data_transformed.imu.az);
            coordinate_transform(sensor_data_transformed.imu.gx, sensor_data_transformed.imu.gy, sensor_data_transformed.imu.gz);
            coordinate_transform(sensor_data_transformed.imu.mx, sensor_data_transformed.imu.my, sensor_data_transformed.imu.mz);
        }

        print_out(sensor_id);
    }

    void OnAttributeChange(int sensor_id, std::string attribute_name, std::string value) {
        printf("OnAttributeChange(id %d, %s, %s)\n", sensor_id, attribute_name.c_str(), value.c_str());
    }

private:
    void coordinate_transform(float& v_x, float& v_y, float& v_z) {
        Quaternion vec(v_x, v_y, v_z, 0);

        /*
         *  v_u = q * v_s * q_conj
         */
        Quaternion tmp = Quaternion::product(q_s_to_u, vec);
        tmp = Quaternion::product(tmp, q_s_to_u_conj);

        v_x = tmp.x;
        v_y = tmp.y;
        v_z = tmp.z;
    }

    void print_out(int sensor_id) {
        std::string line(50, '-');
        printf("%s\n", line.c_str());

        Quaternion& q_org = sensor_data_original.quaternion;
        EulerAngle& e_org = sensor_data_original.euler_angle;
        ImuData<float>& imu_org = sensor_data_original.imu;

        printf("%04d) sensor_id %d, Quaternion O(xyzw)=%.4f,%.4f,%.4f,%.4f, Angle(rpy)=%.1f, %.1f, %.1f, Accel(xyz)=%.4f,%.4f,%.4f, Gyro(xyz)=%.4f,%.4f,%.4f, Magnet(xyz)=%.2f,%.2f,%.2f\n",
                sample_count,
                sensor_id,
                q_org.x, q_org.y, q_org.z, q_org.w,
                e_org.roll, e_org.pitch, e_org.yaw,
                imu_org.ax, imu_org.ay, imu_org.az,
                imu_org.gx, imu_org.gy, imu_org.gz,
                imu_org.mx, imu_org.my, imu_org.mz);

        Quaternion& q_trns = sensor_data_transformed.quaternion;
        EulerAngle& e_trns = sensor_data_transformed.euler_angle;
        ImuData<float>& imu_trns = sensor_data_transformed.imu;

        printf("%04d) sensor_id %d, Quaternion T(xyzw)=%.4f,%.4f,%.4f,%.4f, Angle(rpy)=%.1f, %.1f, %.1f, Accel(xyz)=%.4f,%.4f,%.4f, Gyro(xyz)=%.4f,%.4f,%.4f, Magnet(xyz)=%.2f,%.2f,%.2f\n",
                sample_count,
                sensor_id,
                q_trns.x, q_trns.y, q_trns.z, q_trns.w,
                e_trns.roll, e_trns.pitch, e_trns.yaw,
                imu_trns.ax, imu_trns.ay, imu_trns.az,
                imu_trns.gx, imu_trns.gy, imu_trns.gz,
                imu_trns.mx, imu_trns.my, imu_trns.mz);
    }
};


void ex7_coordinate_transform(const char* serial_device, int baudrate)
{
    printf("\n### %s() ###\n", __FUNCTION__);

    MyAhrsHasOwnCoordinate sensor(serial_device, baudrate);

    if(sensor.initialize() == false) {
        handle_error("initialize() returns false");
    }

    while(sensor.sample_count < 3000) {
        Platform::msleep(100);
    }

    printf("END OF TEST(%s)\n\n", __FUNCTION__);
}



/******************************************************************************************************************************
 *
 *  EXAMPLE 8
 *
 ******************************************************************************************************************************/

void ex8_synchronous_read_ascii_in_trigger_mode(const char* serial_device, int baudrate)
{
    printf("\n### %s() ###\n", __FUNCTION__);

    MyAhrsPlus sensor;
    SensorData sensor_data;
    uint32_t sample_count = 0;

    /*
     * 	start communication with the myAHRS+.
     */
    if(sensor.start(serial_device, baudrate) == false) {
        handle_error("start() returns false");
    }

    /*
     *  set ascii output format
     *   - select euler angle
     */
    if(sensor.cmd_ascii_data_format("RPY") == false) {
        handle_error("cmd_ascii_data_format() returns false");
    }

    /*
     *  set divider
     *   - output rate(Hz) = max_rate/divider
     */
    if(sensor.cmd_divider(DIVIDER) ==false) {
        handle_error("cmd_divider() returns false");
    }

    /*
     *  set transfer mode
     *   - AT : ASCII Message & Trigger mode
     */
    if(sensor.cmd_mode("AT") ==false) {
        handle_error("cmd_mode() returns false");
    }

    while(sample_count < 300) {
    	sensor.cmd_trigger(); // send trigger signal to myAHRS+
        if(sensor.wait_data() == true) { // waiting for new data
        	// read counter
            sample_count = sensor.get_sample_count();

            // copy sensor data
            sensor.get_data(sensor_data);

            // print euler angle
            EulerAngle& e = sensor_data.euler_angle;
            printf("%04d) EulerAngle (roll = %.2f, pitch = %.2f, yaw = %.2f)\n", sample_count, e.roll, e.pitch, e.yaw);
        }
    }

    /*
     * 	stop communication
     */
    sensor.stop();

    printf("END OF TEST(%s)\n\n", __FUNCTION__);
}



/******************************************************************************************************************************
 *
 *
 *
 ******************************************************************************************************************************/

void usage(const char* prog)
{
#ifdef WIN32
    const char* dev_name_example = "COM3 COM4 ...";
#else
    const char* dev_name_example = "/dev/ttyACM0 /dev/ttyACM1 ...";
#endif
    printf("\nusage : %s \"example_number\" \"serial port list\"  \n\t ex) $ %s 1 %s\n\n", prog, prog, dev_name_example);
}

void read_serial_devices_from_command_line(std::vector<std::string>& args, std::vector<std::string>& serial_device_list)
{
    for(size_t i=1; i<args.size(); i++) {
        serial_device_list.push_back(args[i]);
    }
}

#ifdef WIN32
int _tmain(int argc, _TCHAR* argv[]) {
    std::vector<std::string> args;
    for(int i=0; i<argc; i++) {
        CString cstring(argv[i]);
        std::string s(CT2CA(cstring.operator LPCWSTR()));
        args.push_back(s);
    }
#else
int main(int argc, char* argv[]) {
    std::vector<std::string> args;
    for(int i=0; i<argc; i++) {
        args.push_back(std::string(argv[i]));
    }
#endif

    if(argc < 3) {
        printf("ERROR. need more arguments\n");
        usage(args[0].c_str());
        exit(1);
    }

    int example_id = atoi(args[1].c_str());

    std::vector<std::string> serial_device_list;
    for(size_t i=2; i<args.size(); i++) {
        serial_device_list.push_back(args[i]);
    }

    for(size_t i=0; i<serial_device_list.size(); i++) {
        printf(" - serial device(%d) : %s\n", i, serial_device_list[i].c_str());
    }

    switch(example_id) {
    case 1:
    	ex1_synchronous_read_ascii(serial_device_list[0].c_str(), BAUDRATE);
    	break;
    case 2:
    	ex2_synchronous_read_binary(serial_device_list[0].c_str(), BAUDRATE);
    	break;
    case 3:
    	ex3_asynchronous_read_binary(serial_device_list[0].c_str(), BAUDRATE);
    	break;
    case 4:
    	ex4_read_all_properties(serial_device_list[0].c_str(), BAUDRATE);
    	break;
    case 5:
    	ex5_user_defined_class(serial_device_list[0].c_str(), BAUDRATE);
    	break;
    case 6:
    	ex6_multiple_sensors(serial_device_list, BAUDRATE);
    	break;
    case 7:
        ex7_coordinate_transform(serial_device_list[0].c_str(), BAUDRATE);
        break;
    case 8:
    	ex8_synchronous_read_ascii_in_trigger_mode(serial_device_list[0].c_str(), BAUDRATE);
    	break;
    default:
    	handle_error("Invalid example id");
    	break;
    }

    wait_for_user_input();

    return 0;
}


