LIB_DIR = ./lib
BUILD_DIR = ./build

build: CMakeLists.txt lib/OpenXLSX lib/json
	mkdir $(BUILD_DIR)
	cmake -S . -B $(BUILD_DIR)

lib/json: 
	git clone https://github.com/nlohmann/json $(LIB_DIR)/json

lib/OpenXLSX:
	git clone https://github.com/troldal/OpenXLSX $(LIB_DIR)/OpenXLSX

clean/build:
	rm -rf $(BUILD_DIR)

clean/lib:
	rm -rf $(LIB_DIR)

clean:
	$(MAKE) clean/build
	$(MAKE) clean/lib