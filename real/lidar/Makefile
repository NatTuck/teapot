
SDK_PATH := /home/nat/Apps/rplidar_sdk/sdk
SDK_LIB  := $(SDK_PATH)/output/Linux/Release/librplidar_sdk.a
SDK_INC  := $(SDK_PATH)/sdk/include
SDK_SRC  := $(SDK_PATH)/sdk/src

CXXFLAGS := -g -I$(SDK_INC) -I$(SDK_SRC) `pkg-config --cflags gtkmm-3.0`
LDFLAGS  :=
LDLIBS   := `pkg-config --libs gtkmm-3.0` $(SDK_LIB) -lpthread

SRCS := $(wildcard *.cc)
OBJS := $(SRCS:.cc=.o)
HDRS := $(wildcard *.hh)

demo: $(OBJS) $(HDRS)
	g++ $(CXXFLAGS) $(LDFLAGS) -o demo $(OBJS) $(LDLIBS)

clean:
	rm -f *.o demo
