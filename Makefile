CC=gcc
CFLAGS=-c -Wall
SRC_DIR=./source/src/
SOURCES=$(SRC_DIR)main.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=method

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(OBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@
