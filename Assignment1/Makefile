# Fill this makefile with the makefile format instructions to 
#   build your program.
CC = gcc
CFLAGS = -Wall -g

LDLIBS = 

SRC = data.c list.c dict.c driver.c


OBJ = $(SRC:.c=.o)

EXE = dict1

$(EXE): $(OBJ)
	$(CC) $(CFLAGS) -o $(EXE) $(OBJ) $(LDLIBS)

clean:
	rm -f $(OBJ) $(EXE)
