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
SDIR = ./src

# Files
_DEPS = animacao.h movimentacao.h movimentacao.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = animacao.o main.o movimentacao.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

# Default make
all: directories game

directories: ${ODIR}

${ODIR}:
	mkdir -p ${ODIR}

$(ODIR)/%.o: $(SDIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

game: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean directories

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~
