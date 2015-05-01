# myAHRS+ python examples

This examples show you how to use the myAHRS+ with python.  

## Details of examples  

It is assumed that your myAHRS+ is connected to /dev/ttyACM0(linux) or COM1(windows).

### python_example.py

This is the simplest example. It prints out attitude and IMU data(acceleration, angular rate, magnetic fields) on your screen. 

Run this example as follows.

```
$ python python_example.py /dev/ttyACM0
```
