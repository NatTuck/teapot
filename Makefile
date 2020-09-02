
all:
	(cd sim/cmd && make)
	(cd sim/plugins/car_control && make)

clean:
	(cd sim/cmd && make clean)
	(cd sim/plugins/car_control && make clean)

.PHONY: all clean
