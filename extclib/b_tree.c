#include <stdio.h>

typedef enum {
	DECIMAL_ELEM,
	REAL_ELEM,
	STRING_ELEM,
} vtype_tree_t;

typedef union {
	int64_t decimal;
	double real;
	uint8_t *string;
} value_tree_t;

typedef struct tree_node {
	struct {
		value_tree_t ley;
		value_tree_t value;
	} data;
	struct tree_node* left;
	struct tree_node* right;
	struct tree_node* parent;
} tree_node;

typedef struct Tree {
	struct {
		vtype_tree_t key;
		vtype_tree_t value;
	} type;
	struct tree_node *root;
} Tree;

// new_tree(INT, STRING)

extern Tree* new_tree(vtype_tree_t key, vtype_tree_t value);
extern void free_tree(Tree *tree);
extern value_tree_t get_tree(Tree *tree, void *key);
extern void set_tree(Tree *tree, void *key, void *value);
extern void del_tree(Tree *tree, void *key);
extern _Bool in_tree(Tree *tree, void *key);
extern void* decimal(int64_t x);
extern void* real(double x);
extern void* string(uint8_t *x);
extern void print_tree(Tree* tree);
extern void print_tree_as_list(Tree *tree);
static tree_node* _new_node(vtype_tree_t tkey, vtype_tree_t tvalue, void *key, void *value);
static void _set_key(tree_node *node, vtype_tree_t tkey, void *key);
static void _set_value(tree_node *node, vtype_tree_t tvalue, void *value);



extern void* decimal(int64_t x) {
	return (void *)x
}

extern void* real(double x) {
	double *f = (double*)malloc(sizeof(double));
	*f = x;
	return (void *)f;
}

extern void* string(uint8_t *x){
	return (void *)x;
}

extern Tree* new_tree(vtype_tree_t key, vtype_tree_t value) {
	switch(key) {
		case DECIMAL_ELEM: case STRING_ELEM:
			break;
		default:
			fprintf(stderr, "%s\n", "error: key type not supported");
			return NULL;
	}
	Tree *tree = (Tree*)malloc(sizeof(Tree));
	tree->type.key = key;
	tree->type.value = key;
	tree->root = NULL;
	return tree;
}

extern void set_tree(Tree *tree, void *key, void *value){
	if (tree->root == NULL) {
		tree->root = _new_node(tree->type.key, tree->type.value, key, value);
		return;
	}
	_set_tree(root, tree->type.key, tree->type.value, key, value);
}

extern void print_tree(Tree* tree) {
	
}


static tree_node* _new_node(vtype_tree_t tkey, vtype_tree_t tvalue, void *key, void *value) {
	tree_node *node = (tree_node*)malloc(sizeof(tree_node));

	_set_key(node, tkey, key);
	_set_value(node, tvalue, value);
	tree_node->left = NULL;
	tree_node->right = NULL;
	tree_node->parent = NULL;
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

static _set_tree(tree_node *root, vtype_tree_t tkey, vtype_tree_t tvalue, void *key, void *value) {
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
			cond = strcmp(((uint8_t*)key, node->data.key.string));
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
}
*/









