CC=gcc
.PHONY: default build run
default: build run
build: main.c
	$(CC) main.c b_tree.c -o main
run: main
	./main
main.c:
	$(error "undefined main.c")