# Makefile for Proje1

# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -g

# Source files
SRC = main.c Proje1.c

# Header files
HEADERS = Proje1.h

# Output executable
OUT = program.exe

# Build target
all: $(OUT)

$(OUT): main.o Proje1.o
	$(CC) main.o Proje1.o -o $(OUT)

main.o: main.c $(HEADERS)
	$(CC) $(CFLAGS) -c main.c

Proje1.o: Proje1.c $(HEADERS)
	$(CC) $(CFLAGS) -c Proje1.c

# Clean target for Windows
clean:
	del /Q *.o $(OUT)
