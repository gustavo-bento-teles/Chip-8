CC = gcc

SRC = $(wildcard src/*.c)

OUT = chip8

CFLAGS = -Wall -Wextra

ifeq ($(OS),Windows_NT)

    OUT := $(OUT).exe

    INCLUDE = -I SDL2/include

    LIBS = -L SDL2/lib \
           -lmingw32 \
           -lSDL2main \
           -lSDL2

    COPYDLL = cmd /c copy SDL2\bin\SDL2.dll build

    RUN = .\build\$(OUT)

    CLEAN = cmd /c del /Q build\$(OUT)

else

    INCLUDE = $(shell sdl2-config --cflags)

    LIBS = $(shell sdl2-config --libs)

    COPYDLL =

    RUN = ./build/$(OUT)

    CLEAN = rm -f build/$(OUT)

endif

all:
	$(CC) $(SRC) $(CFLAGS) $(INCLUDE) $(LIBS) -o build/$(OUT)
	$(COPYDLL)

run:
	$(CC) $(SRC) $(CFLAGS) $(INCLUDE) $(LIBS) -o build/$(OUT)
	$(COPYDLL)
	$(RUN)

clean:
	$(CLEAN)