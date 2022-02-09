CC = g++
SRC_DIR = src
SRC_FILES = ${shell find src -name "*.cpp"}
COMPILER_FLAGS = -c -std=c++14 -m64 -g -Wall
INCLUDE_PATHS = -I include
LINKER_FLAGS = -lSDL2 -lSDL2_image
BUILD_DIR = build

clear:
	- rm build/*

all: clear
	${CC} ${SRC_FILES} ${COMPILER_FLAGS} ${INCLUDE_PATHS}
	mv *.o ${BUILD_DIR}
	${CC} ${BUILD_DIR}/*.o -o ${BUILD_DIR}/main ${LINKER_FLAGS}

run:
	./build/main
