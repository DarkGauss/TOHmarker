#******************************
# Example TOH program
# Made by Robert Goes (2019)
#******************************

CC = gcc
CFLAGS = -Wall -std=gnu99
MAIN_NAME = example_program.c
FILENAME = example

.PHONY: all clean debug
#*****************************

all: clean $(FILENAME)

debug: CFLAGS += -g
debug: $(FILENAME)

clean:
	-rm -f *.o $(FILENAME)
#******************************
$(FILENAME): main.o 
	$(CC) $(CFLAGS) -o $(FILENAME) main.o -lm

main.o: $(MAIN_NAME)
	$(CC) $(CFLAGS) -c -o main.o $(MAIN_NAME)
