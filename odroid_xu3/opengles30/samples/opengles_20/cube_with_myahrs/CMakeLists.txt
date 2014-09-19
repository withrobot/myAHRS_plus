#
# This confidential and proprietary software may be used only as
# authorised by a licensing agreement from ARM Limited
#   (C) COPYRIGHT 2012 ARM Limited
#       ALL RIGHTS RESERVED
# The entire notice above must be reproduced on all authorised
# copies and copies may only be made to the extent permitted
# by a licensing agreement from ARM Limited.
#

project (cube_myahrs)

set(EXECUTABLE_NAME ${PROJECT_NAME})
set(CMAKE_CXX_FLAGS "-std=c++11")

# Retrieve all the source file names inside the current folder.
file(GLOB EXAMPLE_SOURCES *.cpp)

# Create an executable file called cube
add_executable(${EXECUTABLE_NAME} ${EXAMPLE_SOURCES})

# Link with the simple-framework and OpenGL ES libraries.
set(ALL_LIBRARIES simple_framework2 ${OPENGLES_LIBRARIES} ${PLATFORM_LIBRARIES})
target_link_libraries(${EXECUTABLE_NAME} ${ALL_LIBRARIES})

set(EXECUTABLE_DESTINATION "opengles_20/${EXECUTABLE_NAME}")

# Install the executable in the package folder.
install(TARGETS ${EXECUTABLE_NAME} 
        RUNTIME DESTINATION ${EXECUTABLE_DESTINATION}
        COMPONENT ${EXECUTABLE_NAME})
            
# Copy the assets folder in install directory.
install(DIRECTORY assets DESTINATION ${EXECUTABLE_DESTINATION})
