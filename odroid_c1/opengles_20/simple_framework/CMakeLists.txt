#
# This confidential and proprietary software may be used only as
# authorised by a licensing agreement from ARM Limited
#   (C) COPYRIGHT 2012 ARM Limited
#       ALL RIGHTS RESERVED
# The entire notice above must be reproduced on all authorised
# copies and copies may only be made to the extent permitted
# by a licensing agreement from ARM Limited.
#

cmake_minimum_required (VERSION 2.8)

project (simple_framework)

file(GLOB COMMMON_SOURCES
    src/EGLRuntime.cpp
    src/ETCHeader.cpp
    src/HDRImage.cpp
    src/Matrix.cpp
    src/Platform.cpp
    src/Shader.cpp
    src/Text.cpp
    src/Texture.cpp    
    src/Timer.cpp
)

file(GLOB GLES3_SOURCES
    src/models/CubeModel.cpp
    src/models/PlaneModel.cpp
    src/models/SphereModel.cpp
    src/models/SuperEllipsoidModel.cpp
    src/models/TorusModel.cpp
)

if(${TARGET} STREQUAL "emulator")
    if(WIN32)
        file(GLOB PLATFORM_SOURCES
            src/WindowsPlatform.cpp
        )
    else()
        file(GLOB PLATFORM_SOURCES
            src/DesktopLinuxPlatform.cpp
        )
    endif()
elseif(${TARGET} STREQUAL "arm")
    file(GLOB PLATFORM_SOURCES
        src/LinuxOnARMPlatform.cpp
    )
endif()

add_library(simple_framework2 ${COMMMON_SOURCES} ${PLATFORM_SOURCES})
add_library(simple_framework3 ${COMMMON_SOURCES} ${GLES3_SOURCES} ${PLATFORM_SOURCES})

set_target_properties(simple_framework2 PROPERTIES COMPILE_FLAGS "-DGLES_VERSION=2")
set_target_properties(simple_framework3 PROPERTIES COMPILE_FLAGS "-DGLES_VERSION=3")
