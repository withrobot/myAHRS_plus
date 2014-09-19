# This confidential and proprietary software may be used only as
# authorised by a licensing agreement from ARM Limited
#   (C) COPYRIGHT 2012 ARM Limited
#       ALL RIGHTS RESERVED
# The entire notice above must be reproduced on all authorised
# copies and copies may only be made to the extent permitted
# by a licensing agreement from ARM Limited.
#

cmake_minimum_required(VERSION 2.8)

project (DummyMaliDrivers)

add_library(GLESv1_CM SHARED GLESv1_CM.c)
add_library(GLESv2 SHARED GLESv2.c)
add_library(EGL SHARED EGL.c)