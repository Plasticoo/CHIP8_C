CC = clang 
FLAGS = -Wall -Wextra -Wshadow -Wpointer-arith -Wcast-qual -Wfloat-equal -Wsign-compare -ggdb -std=c11 -pedantic

FILES = main.o cpu.o memory.o rom.o opcodes.o errors.o graphics.o input.o 
LIBS = -lSDL
EXE1 = chip8emu
EXE2 = chip8dis

build: $(FILES)
	$(CC) $(FLAGS) $(FILES) -o $(EXE1) $(LIBS)
	$(CC) src/disassembler.c -o $(EXE2)
	make clean

main.o: src/main.c
	$(CC) $(FLAGS) -c src/main.c $(LIBS)

cpu.o: src/cpu.c
	$(CC) $(FLAGS) -c src/cpu.c $(LIBS)

memory.o: src/memory.c
	$(CC) $(FLAGS) -c src/memory.c $(LIBS)

rom.o: src/rom.c
	$(CC) $(FLAGS) -c src/rom.c $(LIBS)

opcodes.o: src/opcodes.c
	$(CC) $(FLAGS) -c src/opcodes.c $(LIBS)

errors.o: src/errors.c
	$(CC) $(FLAGS) -c src/errors.c $(LIBS)

graphics.o: src/graphics.c
	$(CC) $(FLAGS) -c src/graphics.c $(LIBS)

input.o: src/input.c
	$(CC) $(FLAGS) -c src/input.c $(LIBS)

clean:
	rm *.o
	ctags -R .
