#ifndef TREE_H_
#define TREE_H_

#include <stdio.h>

typedef struct tree_node *tree;

typedef enum { RED, BLACK } rbt_colour;
typedef enum tree_e { BST, RBT } tree_t;

extern tree tree_new(tree_t type);
extern int  tree_search(tree r, char *key);
extern tree tree_insert(tree r, char *key);
extern void tree_inorder(tree r, void f(char *key));
extern void tree_preorder(tree r, void f(char *key));
extern tree tree_delete(tree r, char *key);
extern tree tree_free(tree r);

extern tree right_rotate(tree r);
extern tree left_rotate(tree r);
extern tree tree_fix (tree r);

#endif
