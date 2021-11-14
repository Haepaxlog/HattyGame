SOURCES = main.c

LIBS = -L $(LIB)

LIB = lib/

ifeq ($(OS),Windows_NT)
	DEP = -O1 -Wall -std=c99 -Wno-missing-braces $(LIBS) -lraylib -lopengl32 -lgdi32 -lwinmm
else
	DEP = $(LIBS) -lraylib
endif

install: $(SOURCES) 
	gcc $(SOURCES) -o ./build/main $(DEP)
