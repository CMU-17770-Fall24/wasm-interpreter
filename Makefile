.PHONY: build

build:
	cmake -B build
	make -C build

clean:
	rm -r build

