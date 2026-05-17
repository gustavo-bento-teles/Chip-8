CC = gcc

OUT = chip8

SRC = $(wildcard src/*.c)

OBJ = $(patsubst src/%.c,build/obj/%.o,$(SRC))

CFLAGS = \
	-Wall \
	-Wextra \
	-g

UNAME_S := $(shell uname -s)

ifeq ($(OS),Windows_NT)

	SDL_DIR = external/SDL2/windows

	OUT := $(OUT).exe

	INCLUDE = \
		-Isrc/include \
		-I$(SDL_DIR)/include

	LIBS = \
		-L$(SDL_DIR)/lib \
		-lmingw32 \
		-lSDL2main \
		-lSDL2

	COPYDLL = copy $(SDL_DIR)\bin\SDL2.dll build

	RUN = .\\build\\$(OUT)

	REMOVE = del /Q

else

	SDL_DIR = external/SDL2/linux

	INCLUDE = \
		-Isrc/include \
		-I$(SDL_DIR)/include/SDL2

	LIBS = \
		-L$(SDL_DIR)/lib \
		-Wl,-rpath,'$$ORIGIN/../external/SDL2/linux/lib' \
		-lSDL2

	COPYDLL =

	RUN = ./build/$(OUT)

	REMOVE = rm -f

endif

TARGET = build/$(OUT)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) $(LIBS) -o $@
	$(COPYDLL)

build/obj/%.o: src/%.c
	mkdir -p build/obj
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

run: all
	$(RUN)

clean:
	$(REMOVE) build/obj/*.o
	$(REMOVE) $(TARGET)

re: clean all
