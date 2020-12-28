CC=g++
CFLAGS=-std=c++14 -pedantic
OUTPUT=oop_exercise_06

all:
	$(CC) $(CFLAGS) Allocator.h Rhombus.h List.h main.cpp -o $(OUTPUT)
run:
	./$(OUTPUT)