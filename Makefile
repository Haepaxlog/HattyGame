SOURCES = main.c

LIBS = -L$(LIB) -lraylib

LIB = ./lib

install: $(SOURCES) 
	gcc $(SOURCES) $(LIBS) -o main 