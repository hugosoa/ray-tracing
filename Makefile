# Short commands for day-to-day work (see docs/adr/0004-makefile-shortcuts.md).
# Every target only calls CMake/CTest: the real build lives in CMakeLists.txt.
#
#   make build                 configure (first time only) and compile
#   make start [ARGS="Alice"]  build, then run the ray tracer
#   make test                  build, then run the unit tests
#   make clean                 delete this preset's build folder
#
# Default preset is debug. Use another one with: make test PRESET=release

PRESET ?= debug
BUILD_DIR := build/$(PRESET)

.PHONY: build start test clean

# Configure only when the build folder has not been configured yet.
$(BUILD_DIR)/CMakeCache.txt:
	cmake --preset $(PRESET)

build: $(BUILD_DIR)/CMakeCache.txt
	cmake --build --preset $(PRESET)

start: build
	./$(BUILD_DIR)/src/raytracer $(ARGS)

test: build
	ctest --preset $(PRESET)

clean:
	rm -rf $(BUILD_DIR)
