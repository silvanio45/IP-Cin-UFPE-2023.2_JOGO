# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -std=c99 -g -I$(IDIR)

# Libraries
LIBS = -lraylib -lm

# Directories
IDIR = .\\include
ODIR = .\\obj
RDIR = .\\resources
SDIR = .\\src

# Files
_DEPS = animacao.h ataque.h movimentacao.h
DEPS = $(patsubst %,$(IDIR)\\%,$(_DEPS))

_OBJ = animacao.o main.o
OBJ = $(patsubst %,$(ODIR)\\%,$(_OBJ))

# Default make
all: game

$(ODIR)\\%.o: $(SDIR)\\%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

game: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	del /F /Q $(ODIR)\\*.o *~ core $(INCDIR)\\*~
