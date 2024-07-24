.PHONY: build

build:
	cmake -B build
	make -C build -j

clean:
	rm -r build

