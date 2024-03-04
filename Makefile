# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -std=c99 -g -I$(IDIR)

# Libraries
LIBS = -lraylib

# Directories
IDIR = ./include
ODIR = ./obj
RDIR = ./resources
SDIR = .

# Files
_DEPS = animacao.h entity.h projetil.h movimentacao.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = animacao.o main.o projetil.o movimentacao.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

# Default make
all: directories game

directories: ${ODIR}

${ODIR}:
	mkdir -p ${ODIR}

$(ODIR)/%.o: $(IDIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(ODIR)/main.o: main.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

game: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean directories

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~
