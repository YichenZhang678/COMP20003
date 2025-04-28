# Fill this makefile with the makefile format instructions to 
#   build your program.
CC = gcc
CFLAGS = -Wall -g

LDLIBS = 

SRC1 = dict2.c data.c list.c array.c
SRC2 = dict3.c data.c list.c radix_tree.c 

OBJ1 = $(SRC1:.c=.o)
OBJ2 = $(SRC2:.c=.o)

EXE1 = dict2
EXE2 = dict3

$(EXE1): $(OBJ1)
	$(CC) $(CFLAGS) -o $(EXE1) $(OBJ1) $(LDLIBS)

$(EXE2): $(OBJ2)
	$(CC) $(CFLAGS) -o $(EXE2) $(OBJ2) $(LDLIBS)

clean:
	rm -f $(OBJ1) $(EXE1) $(OBJ2) $(EXE2)

