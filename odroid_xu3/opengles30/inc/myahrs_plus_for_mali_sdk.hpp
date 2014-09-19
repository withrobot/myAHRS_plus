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
 *  myahrs_plus_for_mali_sdk.hpp
 *   - 2014.07.28 ('c')void
 */

#ifndef __MYAHRS_PLUS_FOR_MALI_SDK_H_
#define __MYAHRS_PLUS_FOR_MALI_SDK_H_

#include "myahrs_plus.hpp"

/*
 * for single sensor application 
 */
class MyAhrsPlusForMaliSdk : public WithRobot::iMyAhrsPlus
{
    WithRobot::Platform::Mutex lock;
    WithRobot::SensorData sensor_data;

    double accel_threshold;
    double gyro_threshold;    

public:
    int sample_count;

    MyAhrsPlusForMaliSdk(std::string port, unsigned int baudrate=115200)
    : iMyAhrsPlus(port, baudrate), sample_count(0), accel_threshold(0), gyro_threshold(0) {}
    virtual ~MyAhrsPlusForMaliSdk() {}

    bool initialize() {
        bool ok = false;
        do {
            if(start() == false) break;
            if(cmd_binary_data_format("QUATERNION, IMU") == false) break;
            if(cmd_divider("1") == false) break;
            if(cmd_mode("BC") == false) break;
            ok = true;
        } while(0);

        if(ok) {
            std::string attribute;
            get_attribute("accel_max", attribute);
            accel_threshold = atof(attribute.c_str()) - 2.0; 

            get_attribute("gyro_max", attribute);
            gyro_threshold = atof(attribute.c_str()) - 100.0;                
        } 

        return ok;
    }

    inline void get_data(WithRobot::SensorData& data) {
        WithRobot::LockGuard _l(lock); 
        data = sensor_data;
    }

    inline WithRobot::SensorData get_data() {
        WithRobot::LockGuard _l(lock);
        return sensor_data;
    }

protected:
    bool check_satruation(const char* name, double value, double threshold) {
        if(abs(value) > threshold) {
            printf("# Saturation warning. sensor_id(%d), %s\n", get_sensor_id(), name);
            return false;
        }
        else {
            return true;
        }           
    }    

    void OnSensorData(int sensor_id, WithRobot::SensorData data) {
        {
            WithRobot::LockGuard _l(lock);
            sample_count++;
            sensor_data = data;           
        }

        sensor_data.euler_angle = sensor_data.quaternion.to_euler_angle();

        do {
            if(check_satruation("acceleration x", sensor_data.imu.ax, accel_threshold) == false) break;
            if(check_satruation("acceleration y", sensor_data.imu.ay, accel_threshold) == false) break;
            if(check_satruation("acceleration z", sensor_data.imu.az, accel_threshold) == false) break;
            if(check_satruation("anguler rate x", sensor_data.imu.gx, gyro_threshold) == false) break;
            if(check_satruation("anguler rate y", sensor_data.imu.gy, gyro_threshold) == false) break;
            if(check_satruation("anguler rate z", sensor_data.imu.gz, gyro_threshold) == false) break; 
        }while(0); 
    }

    void OnAttributeChange(int sensor_id, std::string attribute_name, std::string value) {
        printf("OnAttributeChange(id %d, %s, %s)\n", sensor_id, attribute_name.c_str(), value.c_str());
    }
};


/*
 * for multi sensor application 
 */
class MyAhrsArrayForMaliSdk
{
    class AhrsElement : public WithRobot::iMyAhrsPlus
    {
        MyAhrsArrayForMaliSdk* owner;
        WithRobot::Platform::Mutex lock;
        WithRobot::SensorData sensor_data;

        double accel_threshold;
        double gyro_threshold;

    public:
        int sample_count;

        AhrsElement(MyAhrsArrayForMaliSdk* _owner, std::string port, unsigned int baudrate)
        : iMyAhrsPlus(port, baudrate), owner(_owner), sample_count(0), accel_threshold(0), gyro_threshold(0){}
        virtual ~AhrsElement() {}

        bool initialize() {
            bool ok = false;
            do {
                if(start() == false) break;
                if(cmd_binary_data_format("QUATERNION, IMU") == false) break;
                if(cmd_divider("1") == false) break;
                if(cmd_mode("BC") == false) break;
                ok = true;
            } while(0);

            if(ok) {
                std::string attribute;
                get_attribute("accel_max", attribute);
                accel_threshold = atof(attribute.c_str()) - 2.0; 

                get_attribute("gyro_max", attribute);
                gyro_threshold = atof(attribute.c_str()) - 100.0;                
            } 

            return ok;
        }

        WithRobot::SensorData get_data() {
            WithRobot::LockGuard _l(lock);  
            return sensor_data;
        }

    protected:
        bool check_satruation(const char* name, double value, double threshold) {
            if(abs(value) > threshold) {
                printf("# Saturation warning. sensor_id(%d), %s\n", get_sensor_id(), name);
                return false;
            }
            else {
                return true;
            }           
        }

        void OnSensorData(int sensor_id, WithRobot::SensorData d) {
            {
                WithRobot::LockGuard _l(lock);
                sample_count++;
                sensor_data = d;
            }

            sensor_data.euler_angle = sensor_data.quaternion.to_euler_angle();

            do {
                if(check_satruation("acceleration x", sensor_data.imu.ax, accel_threshold) == false) break;
                if(check_satruation("acceleration y", sensor_data.imu.ay, accel_threshold) == false) break;
                if(check_satruation("acceleration z", sensor_data.imu.az, accel_threshold) == false) break;
                if(check_satruation("anguler rate x", sensor_data.imu.gx, gyro_threshold) == false) break;
                if(check_satruation("anguler rate y", sensor_data.imu.gy, gyro_threshold) == false) break;
                if(check_satruation("anguler rate z", sensor_data.imu.gz, gyro_threshold) == false) break; 
            }while(0);

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
    MyAhrsArrayForMaliSdk(std::vector<std::string>& port_list, int baudrate, bool dbg=false) : activated(false), debug(dbg) {
        for(size_t i=0; i<port_list.size(); i++) {
            sensor_array.push_back(new AhrsElement(this, port_list[i], baudrate));
        }
    }

    virtual ~MyAhrsArrayForMaliSdk() {
        stop();
        for(size_t i=0; i<sensor_array.size(); i++) {
            delete sensor_array[i];
        }
        sensor_array.clear();
        sensor_map.clear();
    }

    size_t size() {
        return sensor_array.size();
    }

    bool initialize(bool assign_sensor_id=true) {
        if(activated) {
            return true;
        }

        activated = false;
        
        for(size_t i=0; i<sensor_array.size(); i++) {
            if(sensor_array[i]->initialize() == true) {

                if(assign_sensor_id) {
                    // assign new id to distinguish data event
                    char str_id[16];
                    sprintf(str_id, "%d", i);
                    sensor_array[i]->cmd_id(str_id);
                    sensor_map[i] = sensor_array[i];                    
                }
                else {
                    int sensor_id = sensor_array[i]->get_sensor_id();
                    sensor_map[sensor_id] = sensor_array[i];      

                    printf("seq %d sensor id %d\n", i, sensor_id);
                }

                WithRobot::Platform::msleep(10);
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

    bool get_data(int sensor_id, WithRobot::SensorData& data) {
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
    void OnSensorData(AhrsElement* sensor, int sensor_id, WithRobot::SensorData& data) {
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

#endif // __MYAHRS_PLUS_FOR_MALI_SDK_H_