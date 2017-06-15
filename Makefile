CC = make -j install

all:
	mkdir -p build
	cd build && cmake .. && $(CC)

clean:
	rm -rf build
	rm -rf bin