#include <stdlib.h>
#include <stdio.h>
#include "type.h"

typedef struct Stack {
	vtype_t tvalue;
	value_t *buffer;
	size_t size;
	size_t index;
};

extern Stack* new_stack(size_t size, vtype_t tvalue) {
	switch(tvalue) {
		case DECIMAL_TYPE: case REAL_TYPE: case STRING_TYPE:
		break;
		default:
			fprintf(stderr, "%s\n", "tvalue type not found");
			return NULL;
	}
	Stack *stack = (Stack*)malloc(sizeof(Stack));
	stack->buffer = (value_t*)malloc(sizeof(value_t)*size);
	stack->size = size;
	stack->index = 0;
	return stack;
}

extern void free_stack(Stack *stack) {
	free(stack->buffer);
	free(stack);
}

extern void set_stack(Stack *stack, size_t index, void *value) {
	_insert_stack(stack, index, value);
}

extern void push_stack(Stack *stack, void *value) {
	_insert_stack(stack, stack->index, value);
	stack->index += 1;
}