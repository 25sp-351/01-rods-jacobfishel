CC = gcc
CFLAGS = -g -Wall -Wextra -Werror -std=c99 -I.
LDFLAGS = 

# Object files
OBJ = test.o functions.o munit.o

# Targets
all: test

test: $(OBJ)
	$(CC) $(OBJ) -o test $(LDFLAGS)

test.o: test.c munit.h functions.h
	$(CC) $(CFLAGS) -c test.c

functions.o: functions.c functions.h
	$(CC) $(CFLAGS) -c functions.c

munit.o: munit.c munit.h
	$(CC) $(CFLAGS) -c munit.c

clean:
	rm -f *.o test
