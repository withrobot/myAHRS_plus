# Install script for directory: /home/odroid/work/myahrs/opengles/myahrs_example_with_odroidxu3_Mali_OpenGL_ES_SDK_v2.4.0/samples/opengles_20/cube_with_myahrs

# Set the install prefix
IF(NOT DEFINED CMAKE_INSTALL_PREFIX)
  SET(CMAKE_INSTALL_PREFIX "/home/odroid/work/myahrs/opengles/myahrs_example_with_odroidxu3_Mali_OpenGL_ES_SDK_v2.4.0/bin_emulator")
ENDIF(NOT DEFINED CMAKE_INSTALL_PREFIX)
STRING(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
IF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  IF(BUILD_TYPE)
    STRING(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  ELSE(BUILD_TYPE)
    SET(CMAKE_INSTALL_CONFIG_NAME "")
  ENDIF(BUILD_TYPE)
  MESSAGE(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
ENDIF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)

# Set the component getting installed.
IF(NOT CMAKE_INSTALL_COMPONENT)
  IF(COMPONENT)
    MESSAGE(STATUS "Install component: \"${COMPONENT}\"")
    SET(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  ELSE(COMPONENT)
    SET(CMAKE_INSTALL_COMPONENT)
  ENDIF(COMPONENT)
ENDIF(NOT CMAKE_INSTALL_COMPONENT)

# Install shared libraries without execute permission?
IF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  SET(CMAKE_INSTALL_SO_NO_EXE "1")
ENDIF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "cube_myahrs")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/opengles_20/cube_myahrs" TYPE EXECUTABLE FILES "/home/odroid/work/myahrs/opengles/myahrs_example_with_odroidxu3_Mali_OpenGL_ES_SDK_v2.4.0/samples/opengles_20/cube_with_myahrs/cube_myahrs")
  IF(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/opengles_20/cube_myahrs/cube_myahrs" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/opengles_20/cube_myahrs/cube_myahrs")
    IF(CMAKE_INSTALL_DO_STRIP)
      EXECUTE_PROCESS(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/opengles_20/cube_myahrs/cube_myahrs")
    ENDIF(CMAKE_INSTALL_DO_STRIP)
  ENDIF()
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "cube_myahrs")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/opengles_20/cube_myahrs" TYPE DIRECTORY FILES "/home/odroid/work/myahrs/opengles/myahrs_example_with_odroidxu3_Mali_OpenGL_ES_SDK_v2.4.0/samples/opengles_20/cube_with_myahrs/assets")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

