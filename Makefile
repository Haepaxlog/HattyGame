SOURCES = main.c

LIBS = -L $(LIB)

LIB = lib/

INC = -I include/

ifeq ($(OS),Windows_NT)
	DEP = -O1 -Wall -std=c99 -Wno-missing-braces $(LIBS)/windows -lraylib -lopengl32 -lgdi32 -lwinmm
else
	DEP = $(LIBS)/linux -lraylib
endif

install: $(SOURCES) 
	gcc $(SOURCES) -o ./build/main  $(DEP)
