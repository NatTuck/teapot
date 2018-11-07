
all: libcontrol_plugin.so

libcontrol_plugin.so: $(wildcard *.cc)
	mkdir -p build
	(cd build && cmake ..)
	(cd build && make)
	cp build/libcontrol_plugin.so .

clean:
	rm -rf build libcontrol_plugin.so
