# Introduction

![ScreenShot](images/wiki_image_1.png)

The myAHRS+ is a low cost high performance AHRS(Attitude Heading Reference System). 
Its attitude output is more stable to acceleration and magnetic disturbances then other low cost AHRS/IMU products. 
Communication and configuration are enabled via UART/USB interface for user applications. And I2C interface is available for embedded application like arduino projects.
The GUI(myAHRS+ Monitor) is available, which allows users configure all myAHRS+  settings, view attitude of myAHRS+ and IMU(Inertial Measurement Unit) data in realtime and save sensor data in a text file. Custom user software may be developed using the myAHRS+ SDK.

## Features

* Sensors
  * Triple axis 16-bit gyroscope : ± 2,000 dps
  * Triple axis 16-bit accelerometer : ± 16 g
  * Triple axis 13-bit magnetometer  : ± 1200 μT
* On board software
  * Exteneded Kalman filter
  * max 100 Hz output rate
    * Attitude : Euler angle, Quaternion
    * sensor : acceleration, rotation rate, magnetic field
* Connectivity
  * USB : Virtual COM PORT
  * UART : Standard baud rates up to 460800 bps
  * I2C : up to 1kHz
* GUI(myAHRS+ Monitor)
  * display attitude and sensor data from myAHRS+ on various viewers
  * Configuration
  * magnetometer calibration

## Performance

Performance comparison between myAHRS+ and Razor 9 axis IMU.

[![ScreenShot](images/wiki_image_4_performance_l.png)](http://www.youtube.com/watch?v=vg1yE199DGE)

[![ScreenShot](images/wiki_image_4_performance_c.png)](http://www.youtube.com/watch?v=5NDU6PcPhBw)

Performance comparison between myAHRS+ and MPU9150 MotionFit.

[![ScreenShot](images/wiki_image_4_performance_l_2.png)](http://youtu.be/JtE3BCpq8MA?list=UUr3H8wg38P8b4skZZi_tpYA)

[![ScreenShot](images/wiki_image_4_performance_c_2.png)](http://youtu.be/AI0JuWKJFR8?list=UUr3H8wg38P8b4skZZi_tpYA)


## Pin map

![ScreenShot](images/wiki_image_3.png)

Pin | Name | Type | Description
------|------|------|-------------
J3-1 | INT | O | DATA READY interrupt output
J3-2 | SLEEP | I | Sleep mode selection input: L-sleep mode, H-normal mode. (Normal mode If not connected)
J3-3 | I2C_SCL | I | I2C clock input 
J3-4 | I2C_SDA |  I/O  | I2C data input and output 
J3-5 | USB_DM | I/O | USB D-
J3-6 | USB_DP | I/O | USB D+
J3-7 | NC |   | Do Not Connect
J3-8 | NC |   | Do Not Connect
J3-9 | NC |   | Do Not Connect
J3-10 | NC |   | Do Not Connect
J4-1 | VDD | PWR | +5V power input 
J4-2 | nRST | I | Reset input. L-reset, H-normal
J4-3 | NC |  | Do Not Connect
J4-4 | UART_TX | O | UART transmit
J4-5 | UART_RX | I | UART receive
J4-6 | NC |  | Do Not Connect
J4-7 | NC |  | Do Not Connect
J4-8 | NC |   | Do Not Connect    
J4-9 | NC |   | Do Not Connect    
J4-10| GND | PWR | Power ground. 0V


# Testing the myAHRS+

First, connect myAHRS+ to your PC via USB. And then, check LEDs on myAHRS+. The blinking yellow LED means that myAHRS+ is in normal state. And the red one means that myAHRS+ is connected to PC via USB successfuly. 

The following video shows the tesing procedure of myAHRS+ using GUI(myAHRS+ Monitor). 

[![ScreenShot](images/wiki_image_4_myahrs_monitor.png)](http://www.youtube.com/watch?v=bKS9wkH7ghY)


# Configuration

Using the myAHRS+ Monitor, user can change various properties of myAHRS+ for user application. 
Some properties are saved in non-volatile memory(flash memory), but others are not. Therefore, the volatile properties should be re-initialized to appropriate values when the user application starts.  

* Non-volatile properties
 * Sensor ID
 * Baudrate of UART interface
 * Sensor calibration parameters
* Volatile properties
 * Divider
 * Protocol
 * Transfer mode
 * ASCII output format
 * BINARY output format
 
To update the myAHRS+ settings(properties), run myAHRS+ Monitor. And then open the 'Configuration' dialog window.

![ScreenShot](images/wiki_image_2.png)

This video shows the setting procedure of myAHRS+ using myAHRS+ Monitor. 

[![ScreenShot](images/wiki_image_4_configuration.png)](http://www.youtube.com/watch?v=oncxaqOTxWY)




# Calibration

The magnetometer(compass) used to estimate yaw angle of AHRS. To get better measurment of yaw angle, the magnetometer of myAHRS+ should be calibrated by the user at the very place where it'll be used. The following description explains why to do so.

Measurement of magnetic field will be subjected to distortion. There are two categories of these distortions: the hard iron distortions and the soft iron distortions. The hard iron errors refer to the presence of magnetic fields around the sensor  such as magnets, power supply wires are related to the measurement offset errors, while the soft iron errors refer to the presence of the ferromagnetic materials around the sensor which skew the density of the Earth's magnetic field locally, are related to the scaling offset errors. (http://diydrones.com/profiles/blogs/advanced-hard-and-soft-iron-magnetometer-calibration-for-dummies)

This video shows the calibration procedure of myAHRS+ using myAHRS+ Monitor.

[![ScreenShot](images/wiki_imge_4_calibration.png)](http://www.youtube.com/watch?v=dX0QgiJZKYs)


# I2C Interface 

###1. I2C Interface

The myAHRS+ operates as I2C slave and the I2C bus requires the pull-up resistor.<br/>
Normally 4.7kΩ resistor is used but 1kΩ ~ 10kΩ resistor can be used depends on the situation.


![ScreenShot](images/wiki_image_5_I2C_circuit.JPG)


The I2C port operates in 3.3V voltage level and can be used directly with a MCU with 5V IO without an extra circuit.<br/>
* I2C Slave address: 7bit, 0x20
* Data bit: 8bit
* I2C clock speed: Normal mode(100KHz), Fast mode(400KHz)

I2C interface of the myAHRS+ supports four sequences shown below.


![ScreenShot](images/wiki_image_5_I2C_sequence.JPG)


###2. I2C Register description

Register Name | Attributes | Address | Dafault value | Description
------|------|------|---------- | ----------------
WHO_AM_I | R | 0x01 | 0xB1 | Sensor status
REV_ID_MAJOR | R | 0x02 | - | -
REV_ID_MINOR | R | 0x03 | - | -
STATUS | R |  0x04  | 0x80 | - 
I_ACC_X_LOW | R | 0x10 | DATA | Acceleration raw data
I_ACC_X_HIGH | R | 0x11 | DATA | Acceleration raw data
I_ACC_Y_LOW | R | 0x12 | DATA | Acceleration raw data
I_ACC_Y_HIGH | R | 0x13 | DATA | Acceleration raw data
I_ACC_Z_LOW | R | 0x14 | DATA | Acceleration raw data
I_ACC_Z_HIGH | R | 0x15 | DATA | Acceleration raw data
I_GYRO_X_LOW | R | 0x16 | DATA | Gyroscope raw data
I_GYRO_X_HIGH | R | 0x17 | DATA | Gyroscope raw data
I_GYRO_Y_LOW | R | 0x18 | DATA | Gyroscope raw data
I_GYRO_Y_HIGH | R | 0x19 | DATA | Gyroscope raw data
I_GYRO_Z_LOW | R | 0x1A | DATA | Gyroscope raw data
I_GYRO_Z_HIGH | R | 0x1B | DATA | Gyroscope raw data
I_MAGNET_X_LOW | R | 0x1C | DATA | Magnetometer raw data
I_MAGNET_X_HIGH | R | 0x1D | DATA | Magnetometer raw data
I_MAGNET_Y_LOW | R | 0x1E | DATA | Magnetometer raw data
I_MAGNET_Y_HIGH | R | 0x1F | DATA | Magnetometer raw data
I_MAGNET_Z_LOW | R | 0x20 | DATA | Magnetometer raw data
I_MAGNET_Z_HIGH | R | 0x21 | DATA | Magnetometer raw data
C_ACC_X_LOW | R | 0x22 | DATA | Calibrated acceleration data
C_ACC_X_HIGH | R | 0x23 | DATA | Calibrated acceleration data
C_ACC_Y_LOW | R | 0x24 | DATA | Calibrated acceleration data
C_ACC_Y_HIGH | R | 0x25 | DATA | Calibrated acceleration data
C_ACC_Z_LOW | R | 0x26 | DATA | Calibrated acceleration data
C_ACC_Z_HIGH | R | 0x27 | DATA | Calibrated acceleration data
C_GYRO_X_LOW | R | 0x28 | DATA | Calibrated gyroscope data
C_GYRO_X_HIGH | R | 0x29 | DATA | Calibrated gyroscope data
C_GYRO_Y_LOW | R | 0x2A | DATA | Calibrated gyroscope data
C_GYRO_Y_HIGH | R | 0x2B | DATA | Calibrated gyroscope data
C_GYRO_Z_LOW | R | 0x2C | DATA | Calibrated gyroscope data
C_GYRO_Z_HIGH | R | 0x2D | DATA | Calibrated gyroscope data
C_MAGNET_X_LOW | R | 0x2E | DATA | Calibrated magnetometer data
C_MAGNET_X_HIGH | R | 0x2F | DATA | Calibrated magnetometer data
C_MAGNET_Y_LOW | R | 0x30 | DATA | Calibrated magnetometer data
C_MAGNET_Y_HIGH | R | 0x31 | DATA | Calibrated magnetometer data
C_MAGNET_Z_LOW | R | 0x32 | DATA | Calibrated magnetometer data
C_MAGNET_Z_HIGH | R | 0x33 | DATA | Calibrated magnetometer data
TEMPERATURE_LOW | R | 0x34 | DATA | Temperature data
TEMPERATURE_HIGH | R | 0x35 | DATA | Temperature data
ROLL_LOW | R | 0x36 | DATA | Euler angle
ROLL_HIGH | R | 0x37 | DATA | Euler angle
PITCH_LOW | R | 0x38 | DATA | Euler angle
PITCH_HIGH | R | 0x39 | DATA | Euler angle
YAW_LOW | R | 0x3A | DATA | Euler angle
YAW_HIGH | R | 0x3B | DATA | Euler angle
QUATERNION_X_LOW | R | 0x3C | DATA | Quaternion
QUATERNION_X_HIGH | R | 0x3D | DATA | Quaternion
QUATERNION_Y_LOW | R | 0x3E | DATA | Quaternion
QUATERNION_Y_HIGH | R | 0x3F | DATA | Quaternion
QUATERNION_Z_LOW | R | 0x40 | DATA | Quaternion
QUATERNION_Z_HIGH | R | 0x41 | DATA | Quaternion
QUATERNION_W_LOW | R | 0x42 | DATA | Quaternion
QUATERNION_W_HIGH | R | 0x43 | DATA | Quaternion

###3. Data transform formula

* I_ACC_X_LOW ~ I_MAGNET_Z_HIGH
 * These registers store the sensor output value that is not compensated by the calibration parameter. Lower 8bit is saved in a LOW register and higher 8bit register is saved in a HIGH register. Since the value is originally Integer, there is no need to convert it into a Real number.

* C_ACC_X_LOW ~ C_ACC_Z_HIGH
 * These registers store the acceleration output value (signed 16bit) that is compensated by the calibration parameter. Lower 8bit is saved in a LOW register and higher 8bit register is saved in a HIGH register. Multiplying a scale factor (16 / 32767) converts the unit of acceleration value into the (g) unit.
 * Acceleration(g) = C_ACC × 16 / 32767

* C_GYRO_X_LOW ~ C_ GYRO _Z_HIGH
 * These registers store the gyroscope output value (signed 16bit) that is compensated by the calibration parameter. Lower 8bit is saved in a LOW register and higher 8bit register is saved in a HIGH register. Multiplying a scale factor (2000 / 32767) converts the unit of gyroscope value into the (dps / degree per second) unit.
 * Gyroscope(dps) = C_GYRO × 2000 / 32767

* C_MAGNET_X_LOW ~ C_ MAGNET _Z_HIGH
 * These registers store the magnetometer output value (signed 16bit) that is compensated by the calibration parameter. Lower 8bit is saved in a LOW register and higher 8bit register is saved in a HIGH register. The output value of a calibrated magnetometer sensor is not required to convert into a Real number, because there is no physical unit.
 * If you need magnetic field measurement, multiply the scale factor 0.3 to not-calibrated magnetometer output (I_MAGNET_X_LOW ~ I_MAGNET_Z_HIGH) then you can get the magnetic field measurement in uT.
 * Magnetometer(uT) = I_MAGNET × 0.3

* TEMPERATURE_LOW ~ TEMPERATURE_HIGH
 * These registers store the temperature output value (signed 16bit). Lower 8bit is saved in a LOW register and higher 8bit register is saved in a HIGH register. Multiplying a scale factor (200 / 32767) converts the unit of the temperature value into the (℃) unit.
 * Temperature(℃) = TEMPERATURE_N × 200 / 32767

* ROLL_LOW ~ YAW_HIGH
 * These registers store the Euler angle output value (signed 16bit). Lower 8bit is saved in a LOW register and higher 8bit register is saved in a HIGH register. Multiplying a scale factor (180 / 32767) converts the unit of the angle value into the (°) unit.
 * Euler angle(°) = ROLL(PITCH, YAW) × 180 / 32767

* QUATERNION_X_LOW ~ QUATERNION_W_HIGH
 * These registers store the quaternion output value (signed 16bit). Lower 8bit is saved in a LOW register and higher 8bit register is saved in a HIGH register. Multiplying a scale factor (1 / 32767) converts the value into the Real number.
 * Quaternion = X(Y, Z, W) / 32767


# UART Protocol

Describes the details of various messages used for communicating with myAHRS+ using serial port (USB/UART).<br/>
This will help you getting the sensor data and changing the settings.

###1. Message frame definition
myAHRS+ message format

Header | Function
------|------
@,~,$ | Start of Communication Frame
\r\n | End of Communication Frame
* | CRC delimeter

Request message
* A message from the Host(PC) to the sensor
* [@][body(N byte)][*][CRC(2byte)][\r\n]<br/>
Response Message
* A message from the sensor to the Host(PC) Request message
* [~][body(N byte)][*][CRC(2byte)][\r\n]<br/>
Data Message
* Supports ASCII and BINARY formats
* A message independent of Response message for Request message, sent to the Host which includes various sensor data<br/>

# Examples

Some useful examples for using the myAHRS+ are available for various platforms.

* [myAHRS+ SDK](../common_cpp).
* [python](../common_python).
* [odroid XU3](../odroid_xu3).
* [odroid C1](../odroid_c1).
* I2C Examples
 * [myCortex-STM32F4](https://github.com/withrobot/myCortex-STM32F4/tree/master/ex09.4_I2C_myAHRS%2B).
* UART Examples
 
