BUILD_DIR = build

ifeq ($(OS),Windows_NT)
	GENERATOR = -G "MinGW Makefiles"
else
	GENERATOR =
endif

all:
	cmake -B $(BUILD_DIR) $(GENERATOR)
	cmake --build $(BUILD_DIR)

clean:
	cmake -E rm -rf BUILD_DIR

rebuild: clean all

.PHONY: all clean rebuild
