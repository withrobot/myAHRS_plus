# myAHRS+ SDK

This examples show you how to use the myAHRS+ SDK. 



## How to build it on linux 

Requirements

* g++ (support -std=c++11 option)


Download source tree from github. 

```
$ cd YOUR_WORKING_DIRECTORY
$ svn export https://github.com/withrobot/myAHRS_plus/trunk/common_cpp
```

Build.

```
$ cd common_cpp
$ make clean; make all
```

You can use the myAHRS+ SDK on embedded platform like odroid or raspberry pi. 

## How to build it on windows 

Requirements

* Visual studio 2010 

Download source tree from github. 

And open the solution file(YOUR_WORKING_DIRECTORY\common_cpp\windows_example\windows_example.sln) in Visual Studio.

## How to run

See comments in myahrs_plus_example.cpp. 

## Details   

* myahrs_plus.hpp 
  - myAHRS+ SDK
  - To use this SDK, include it to your own source file. 
* myahrs_plus_example.cpp
  - myAHRS+ SDK example

