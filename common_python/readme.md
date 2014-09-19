# myAHRS+ python examples

This examples show you how to use the myAHRS+ with python.  

## Requirements

* python 2.7
* pySerial
* PyQt4
* PyOpenGL

## Details of examples  

It is assumed that your myAHRS+ is connected to /dev/ttyACM0(linux) or COM1(windows).

### python_example.py

This is the simplest example. It prints out attitude and IMU data(acceleration, angular rate, magnetic fields) on your screen. 

Run this example as follows.

```
$ python python_example.py /dev/ttyACM0
```


### pyqt_example.py

![ScreenShot](images/windows_sample.PNG)

It displays a box that rotates along with the attitude of the myAHRS+. 

Run this example as follows.

```
$ python pyqt_example.py /dev/ttyACM0
```

Note) Since the ARM-linux does not support PyOpenGL, You can't run this example on odroid(or raspberry pi).  
