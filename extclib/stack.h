#ifndef EXTCLIB_STACK_H_
#define EXTCLIB_STACK_H_

#include "type.h"
#include <stddef.h>

extern Stack *new_stack(size_t size, vtype_t tvalue);
extern void free_stack(Stack *stack);
extern void set_stack(Stack *stack, size_t index, void *value);
extern void push_stack(Stack *stack, void *value);
extern value_t pop_stack(Stack *stack);
extern value_t get_stack(Stack *stack, size_t index);
#endif