
CC  = $(CROSS)gcc
CXX = $(CROSS)g++
AR  = $(CROSS)ar
STRIP = $(CROSS)strip
MV  = mv
CP  = cp
RM  = rm -rf
MKDIR = mkdir

TARGET = test_myahrs_plus

INCLUDE = -I./
 
CFLAGS   = -O2
CXXFLAGS = $(CFLAGS) -std=c++11

CPP_SRCS = $(wildcard *.cpp) 
C_SRCS   = $(wildcard *.c)

SRCS = $(CPP_SRCS) $(C_SRCS)
OBJS = $(CPP_SRCS:.cpp=.o) $(C_SRCS:.c=.o)


all : $(TARGET)

$(TARGET) : $(OBJS) myahrs_plus.hpp
	$(CXX) $(CFLAGS) -o $@ $(OBJS) -lm -lpthread 

clean :
	$(RM) *.o $(TARGET) *.a *.d *.bak *.map 

%.o: %.c $(wildcard *.h)  
	$(CC) $(CFLAGS) $(INCLUDE) -c -o $@ $<

%.o: %.cpp $(wildcard *.h)  
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c -o $@ $<	


