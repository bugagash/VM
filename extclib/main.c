#include "b_tree.h"


typedef struct HashTab {
	struct {
		vtype_tree_t key;
		vtype_tree_t value;
	} type;
	size_t size;
	Tree **table;
} HashTab;

extern HashTab* new_hashtab(size_t size, vtype_tree_t key, vtype_tree_t value);
extern void free_hashtab(HashTab *hashtab);
extern value_tree_t get_HashTab(HashTab *hashtab, void *key);
extern void set_HashTab(HashTab *hashtab, void *key, void *value);
extern void del_HashTab(HashTab *hashtab, void *key);
extern _Bool in_HashTab(HashTab *hashtab, void *key);



int main(void) {
	Tree *tree = new_tree(STRING_ELEM, DECIMAL_ELEM);
	print_tree_as_list(tree);
	free_tree(tree);
	return 0;
}