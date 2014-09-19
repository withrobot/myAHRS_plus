#
# This confidential and proprietary software may be used only as
# authorised by a licensing agreement from ARM Limited
# (C) COPYRIGHT 2014 ARM Limited
#     ALL RIGHTS RESERVED
# The entire notice above must be reproduced on all authorised
# copies and copies may only be made to the extent permitted
# by a licensing agreement from ARM Limited.
#

project(skybox_myahrs)

set(EXECUTABLE_NAME ${PROJECT_NAME})

# Retrieve all the source file names inside the current folder
file(GLOB EXAMPLE_SOURCES *.cpp)

# Platform-dependend sources to exclude from whole list
file(GLOB PLATFORM_SOURCES WindowsPlatform.cpp DesktopLinuxPlatform.cpp LinuxOnARMPlatform.cpp)

# Only one of following platform-dependend file should be compiled and linked
list(REMOVE_ITEM EXAMPLE_SOURCES ${PLATFORM_SOURCES})

# Choose source file appropriate platform
if(${TARGET} STREQUAL "emulator")
    if(WIN32)
        file(GLOB PLATFORM_SOURCES WindowsPlatform.cpp)
    else()
        file(GLOB PLATFORM_SOURCES DesktopLinuxPlatform.cpp)
        set(CMAKE_CXX_FLAGS "-std=c++11")
    endif()
elseif(${TARGET} STREQUAL "arm")
    file(GLOB PLATFORM_SOURCES LinuxOnARMPlatform.cpp)
endif()

# Add platform dependent source file to compilation list
list(APPEND EXAMPLE_SOURCES ${PLATFORM_SOURCES})

# Create an executable file called skybox
add_executable(${EXECUTABLE_NAME} ${EXAMPLE_SOURCES})

# Link with OpenGL ES libraries
set(ALL_LIBRARIES ${OPENGLES_LIBRARIES} ${PLATFORM_LIBRARIES})
target_link_libraries(${EXECUTABLE_NAME} ${ALL_LIBRARIES})

set(EXECUTABLE_DESTINATION "opengles_30/${EXECUTABLE_NAME}")

# Install the executable in the package folder
install(TARGETS ${EXECUTABLE_NAME}
        RUNTIME DESTINATION ${EXECUTABLE_DESTINATION}
        COMPONENT ${EXECUTABLE_NAME})

# Copy the assets folder in install directory.
install(DIRECTORY assets DESTINATION ${EXECUTABLE_DESTINATION})
