CC=gcc
LN=ld

CFALGS=-Wall -Wextra

HEADERS=stack.h type.h
SOURCES=stack.c type.c
OBJECTS=stack.o type.o

.PHONY: default buidlink clean
default: build link

build: $(HEADERS) $(SOURCES)
	$(CC) $(OPT) $(CFALGS) -c $(SOURCES)
link: $(OBJECTS)
	$(LN) -r $(OBJECTS) -o extclib.o
clean:
	rm -f *.o *.i *.s