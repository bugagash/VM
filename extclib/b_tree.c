#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "b_tree.h"

static tree_node* _new_node(vtype_tree_t tkey, vtype_tree_t tvalue, void *key, void *value);
static void _set_tree(tree_node *root, vtype_tree_t tkey, vtype_tree_t tvalue, void *key, void *value);
static void _set_key(tree_node *node, vtype_tree_t tkey, void *key);
static void _set_value(tree_node *node, vtype_tree_t tvalue, void *value);
static void _print_tree(tree_node *node, vtype_tree_t tkey, vtype_tree_t tvalue);
static void _print_tree_as_list(tree_node *node, vtype_tree_t tkey, vtype_tree_t tvalue);
static void _print_tree_elem(tree_node *node, vtype_tree_t tkey, vtype_tree_t tvalue);
static void _free_tree(tree_node *node);
static tree_node* _get_tree(tree_node* node, vtype_tree_t tkey, void* key);
static tree_node* _del1_tree(Tree *tree, vtype_tree_t tkey, void *key);
static void _del2_tree(Tree *tree, tree_node *node);
static void _del3_tree(tree_node *node);


extern void* decimal(int64_t x) {
	return (void *)x;
}

extern void* real(double x) {
	double *f = (double*)malloc(sizeof(double));
	*f = x;
	return (void *)f;
}

extern void* string(uint8_t *x){
	return (void *)x;
}

extern Tree* new_tree(vtype_tree_t tkey, vtype_tree_t tvalue) {
	switch(tkey) {
		case DECIMAL_ELEM: case STRING_ELEM:
			break;
		default:
			fprintf(stderr, "%s\n", "error: key type not supported");
			return NULL;
	}
	Tree *tree = (Tree*)malloc(sizeof(Tree));
	tree->type.key = tkey;
	tree->type.value = tvalue;
	tree->root = NULL;
	return tree;
}

extern void set_tree(Tree *tree, void *key, void *value){
	if (tree->root == NULL) {
		tree->root = _new_node(tree->type.key, tree->type.value, key, value);
		return;
	}
	_set_tree(tree->root, tree->type.key, tree->type.value, key, value);
}

extern void print_tree(Tree* tree) {
	_print_tree(tree->root, tree->type.key, tree->type.value); // requires realization!
	putchar('\n');
}

extern void print_tree_as_list(Tree* tree) {
	printf("[");
	_print_tree_as_list(tree->root, tree->type.key, tree->type.value); // requires realization!!!
	printf("]\n");
}

extern void free_tree(Tree *tree) {
	_free_tree(tree->root);
	free(tree);
}

extern value_tree_t get_tree(Tree *tree, void *key) {
	tree_node *node = _get_tree(tree->root, tree->type.key, key);
	if (node == NULL) {
		fprintf(stderr, "%s\n", "error: value undefined");
		value_tree_t none = {
			.decimal = 0,
		};
		return none;
	}
	return node->data.value;
}

extern _Bool in_tree(Tree *tree, void *key){
	return _get_tree(tree->root, tree->type.key, key) != NULL;
}

extern void del_tree(Tree *tree, void *key){
	tree_node* node = _del1_tree(tree, tree->type.key, key);
	if (node == NULL) {
		return;
	} else if (node->left != NULL && node->right != NULL) {
		_del3_tree(node);
		return;
	}
	_del2_tree(tree, node);
}




static tree_node* _del1_tree(Tree *tree, vtype_tree_t tkey, void *key) {
	tree_node *node = tree->root;
	node = _get_tree(node, tkey, key);
	if (node == NULL) {
		return NULL;
	}
	if (node->left != NULL || node->right != NULL) {
		return node;
	}
	tree_node *parent = node->parent;
	if (parent == NULL) {
		tree->root = NULL;
	} else if (parent->left == node) {
		parent->left = NULL;
	} else {
		parent->right = NULL;
	}
	free(node);
	return NULL;
}

static void _del2_tree(Tree *tree, tree_node *node) {
	tree_node *parent = node->parent;
	tree_node *tmp;
	if (node->right != NULL) {
		tmp = node->right;
	} else {
		tmp = node->left;
	}
	if (parent == NULL) {
		tree->root = tmp;
	} else if (parent->left == node) {
		parent->left = tmp;
	} else {
		parent->right = tmp;
	}
	tmp->parent = parent;
	free(node);
}

static void _del3_tree(tree_node *node) {
	tree_node *ptr = node->right;
	while(ptr->left != NULL) {
		ptr = ptr->left;
	}
	node->data.key = ptr->data.key;
	node->data.value = ptr->data.value;
	tree_node *parent = ptr->parent;
	if (parent->left == ptr) {
		parent->left = NULL;
	} else {
		parent->right = NULL;
	}
	free(ptr);
}

static tree_node* _get_tree(tree_node* node, vtype_tree_t tkey, void* key) {
	int cond;
	if(node == NULL) {
		return NULL;
	}
	switch(tkey) {
		case DECIMAL_ELEM:
			if ((uint64_t)key > node->data.key.decimal) {
				return _get_tree(node->right, tkey, key);
			} else if ((uint64_t)key < node->data.key.decimal) {
				return _get_tree(node->left, tkey, key);
			}
		break;
		case STRING_ELEM:
			cond = strcmp((uint8_t*)key, node->data.key.string);
			if (cond > 0) {
				return _get_tree(node->right, tkey, key);
			} else if (cond < 0) {
				return _get_tree(node->left, tkey, key);
			}
		break;
	}
	return node;
}

static void _free_tree(tree_node *node) {
	if (node == NULL) {
		return;
	}
	_free_tree(node->left);
	_free_tree(node->right);
	free(node);
}

static void _print_tree_as_list(tree_node *node, vtype_tree_t tkey, vtype_tree_t tvalue) {
	if (node == NULL) {
		return;
	}
	_print_tree_as_list(node->left, tkey, tvalue);
	_print_tree_elem(node, tkey, tvalue);
	_print_tree_as_list(node->right, tkey, tvalue);
}


static void _print_tree(tree_node *node, vtype_tree_t tkey, vtype_tree_t tvalue) {
	if (node == NULL) {
		printf("null");
		return;
	}
	putchar('(');
	_print_tree(node->left, tkey, tvalue);
	_print_tree_elem(node, tkey, tvalue);
	_print_tree(node->right, tkey, tvalue);
	putchar(')');
}

static void _print_tree_elem(tree_node *node, vtype_tree_t tkey, vtype_tree_t tvalue) {
	switch(tkey) {
		case DECIMAL_ELEM:
			printf("[%d => ", node->data.key.decimal);
			switch(tvalue) {
				case DECIMAL_ELEM:
					printf("%d] ", node->data.value.decimal);
				break;
				case REAL_ELEM:
					printf("%lf] ", node->data.value.real);
				break;
				case STRING_ELEM:
					printf("%s] ", node->data.value.string);
				break;
			}
		break;
		case STRING_ELEM:
			printf("[%s => ", node->data.key.string);
			switch(tvalue) {
				case DECIMAL_ELEM:
					printf("%d] ", node->data.value.decimal);
				break;
				case REAL_ELEM:
					printf("%lf] ", node->data.value.real);
				break;
				case STRING_ELEM:
					printf("%s] ", node->data.value.string);
				break;
			}
		break;
	}
}

static tree_node* _new_node(vtype_tree_t tkey, vtype_tree_t tvalue, void *key, void *value) {
	tree_node *node = (tree_node*)malloc(sizeof(tree_node));

	_set_key(node, tkey, key);
	_set_value(node, tvalue, value);
	node->left = NULL;
	node->right = NULL;
	node->parent = NULL;
	return node;
}

static void _set_key(tree_node *node, vtype_tree_t tkey, void *key) {
	switch(tkey) {
		case DECIMAL_ELEM:
			node->data.key.decimal = (int64_t)key;
		break;
		case STRING_ELEM:
			node->data.key.string = (uint8_t*)key;
		break;
		default: ;
	}
}

static void _set_value(tree_node *node, vtype_tree_t tvalue, void *value) {
	switch(tvalue) {
		case DECIMAL_ELEM:
			node->data.value.decimal = (int64_t)value;
		break;
		case REAL_ELEM:
			node->data.value.real = *(double*)value;
			free((double*)value);
		break;
		case STRING_ELEM:
			node->data.value.string = (uint8_t*)value;
		break;
		default: ;
	}
}

static void _set_tree(tree_node *root, vtype_tree_t tkey, vtype_tree_t tvalue, void *key, void *value) {
	int cond;
	switch(tkey) {
		case DECIMAL_ELEM:
			if ((int64_t)key > root->data.key.decimal) {
				if (!root->right) {
					root->right = _new_node(tkey, tvalue, key, value);
					root->right->parent = root;
				} else {
					_set_tree(root->right, tkey, tvalue, key, value);
				}
			} else if ((int64_t)key < root->data.key.decimal) {
				if (!root->left) {
					root->left = _new_node(tkey, tvalue, key, value);
					root->left->parent = root;
				} else {
					_set_tree(root->left, tkey, tvalue, key, value);
				}
			} else {
				_set_value(root, tvalue, value);
			}
		break;
		case STRING_ELEM:
			cond = strcmp((uint8_t*)key, root->data.key.string);
			if ((int64_t)key > root->data.key.decimal) {
				if (cond > 0) {
					root->right = _new_node(tkey, tvalue, key, value);
					root->right->parent = root;
				} else {
					_set_tree(root->right, tkey, tvalue, key, value);
				}
			} else if (cond < 0) {
				if (!root->left) {
					root->left = _new_node(tkey, tvalue, key, value);
					root->left->parent = root;
				} else {
					_set_tree(root->left, tkey, tvalue, key, value);
				}
			} else {
				_set_value(root, tvalue, value);
			}
		break;
	}
}


/*

int main(void) {
	Tree* tree = new_tree(DECIMAL_ELEM, STRING_ELEM);
	set_tree(tree, decimal(50), string("A"));
	set_tree(tree, decimal(40), string("B"));
	set_tree(tree, decimal(60), string("C"));

	set_tree(tree, decimal(12), string("D"));
	set_tree(tree, decimal(10), string("E"));
	set_tree(tree, decimal(6), string("F"));
	set_tree(tree, decimal(333), string("G"));

	print_tree_as_list(tree);
	del_tree(tree, decimal(40));
	print_tree_as_list(tree);
	free_tree(tree);
	return 0;
}

*/


