cmake_minimum_required(VERSION 3.3)
project(Chip8_Emulator)

set(CMAKE_C_COMPILER "/usr/bin/clang")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_C_FLAGS "${CMAKE_CXX_FLAGS} -std=c11 -ggdb -Wall -lSDL")

set(SOURCE_FILES src/main.c src/main.h
	src/cpu.c src/cpu.h
	src/errors.c src/errors.h
	src/graphics.c src/graphics.h
	src/input.c src/input.h
	src/memory.c src/memory.h
	src/opcodes.c src/opcodes.h
	src/rom.c src/rom.h)

add_executable(chip8emu ${SOURCE_FILES})
add_executable(chip8dis src/disassembler.c)
