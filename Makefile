.PHONY: build

build:
	cmake -B build -DCMAKE_BUILD_TYPE=Debug -DCMAKE_VERBOSE_MAKEFILE=1
	make -C build

clean:
	rm -r build

