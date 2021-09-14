all: CMakeLists.txt
	$(MAKE) build/clean
	$(MAKE) main

build: CMakeLists.txt
	cmake -S . -B ./build

build/clean:
	$(MAKE) clean
	$(MAKE) build

main:
	rm -rf build/src/schedule
	$(MAKE) build/src/schedule
	rm -rf schedule
	cp build/src/schedule .

build/src/schedule: build
	$(MAKE) -f ./build/src/Makefile main

test: build/src/schedule
	./build/src/schedule --file ./examples/schedule.xlsx --output --config ./examples/config.json --log 2 -o

test/clean:
	rm -rf build/src/schedule
	$(MAKE) test

test/min: build/src/schedule
	./build/src/schedule --file ./examples/schedule.xlsx --output --config ./examples/config_minimal.json --log 2 -o

debug:
	$(MAKE) test/clean

debug/min:
	rm -rf build/src/schedule
	$(MAKE) test/min

clean:
	rm -rf build
	rm -rf schedule
	rm -f *.ics