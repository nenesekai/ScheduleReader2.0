all:

build: CMakeLists.txt
	cmake -S . -B ./build

main: build
	rm -rf build/src/schedule ./schedule
	$(MAKE) -f build/src/makefile main
	cp build/src/schedule .

test: src/test.cpp build
	rm -rf build/src/test ./test
	$(MAKE) -f build/src/makefile test
	cp build/src/test .
	./test

clean:
	rm -rf ./build schedule output.ics test