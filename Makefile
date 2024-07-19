CC := clang++
FLAGS := -Wall -std=c++17
LIBS_PATH := -Ldependencies/lib
LIBS := -lglfw.3.4
INCLUDES := -Idependencies/include -Isrc -Isrc/vendor
SRC := src
CPP_SRCS=$(shell find $(SRC) -name "*.cpp")

debug:
	$(CC) $(FLAGS) src/glad.c $(CPP_SRCS) $(INCLUDES) -o out/game $(LIBS_PATH) $(LIBS) -DDEV_BUILD -g

release:
	$(CC) $(FLAGS) src/glad.c $(CPP_SRCS) $(INCLUDES) -o out/game $(LIBS_PATH) $(LIBS)

run:
	./out/game

clean:
	rm -rf out/* 

all: debug run

# run 'bear -- make debug' to generate compile_commands.json

