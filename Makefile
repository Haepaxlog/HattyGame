SOURCES = ./build/player.o ./build/letter.o ./build/main.o

LIBS = -L $(LIB)

LIB = lib/

INC = -I include/

ifeq ($(OS),Windows_NT)
	DEP = -O1 -Wall -std=c99 -Wno-missing-braces $(LIBS)windows -lraylib -lopengl32 -lgdi32 -lwinmm
else
	DEP = $(LIBS)linux -lraylib
endif

Player: player.c 
	gcc -c -o ./build/player.o player.c $(INC) $(DEP)

Letter: letter.c
	gcc -c -o ./build/letter.o letter.c $(INC) $(DEP)

Main: main.c
	gcc -c -o ./build/main.o main.c $(INC) $(DEP)

install: $(SOURCES)  
	gcc -o ./build/main $(SOURCES) $(INC) $(DEP)