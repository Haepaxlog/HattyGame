SOURCES = main.c

LIBS = -L $(LIB)

LIB = lib/

ifeq ($(OS),Windows_NT)
	install: $(SOURCES)
		gcc $(SOURCES) -o main -O1 -Wall -std=c99 -Wno-missing-braces -L lib/ -lraylib -lopengl32 -lgdi32 -lwinmm
else
	install: $(SOURCES) 
		gcc $(SOURCES) $(LIBS) -o main -lraylib
