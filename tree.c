#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tree.h"

#define IS_BLACK(x) ((NULL == (x)) || (BLACK == (x)->colour))
#define IS_RED(x) ((NULL != (x)) && (RED == (x)->colour))

static tree_t typeOfTree;

struct tree_node { /* should live in tree.c */
    char *key;
    rbt_colour colour;
    tree_t treeType;
    tree left;
    tree right;
};

/*returns null node to represent empty new tree*/
tree tree_new(tree_t t) {
    if (t == BST) {
        typeOfTree = BST;
    } else {
        typeOfTree = RBT; 
    }
    /* typeOfTree = t; */
    return NULL;
}

int tree_search(tree r, char *key) {
    if (r == NULL) {
        return 0;
    }
    /* strcmp returns 0 if strings are equal, 1 if the current key is bigger than the key being searched, and negative if
     * the current key is less than the key being searched
    */
    /* If the keys are equal, return 1 */
    if (strcmp(r->key, key) == 0) {
        return 1;
    /* If the searched key is greater, search left tree instead */
    } if(strcmp(r->key, key) > 0) {
        return tree_search(r->left, key);
    /* If the searched key is less than, search right tree instead */
    } else if(strcmp(r->key, key) < 0) {
        return tree_search(r->right, key);
    }

}

tree tree_insert(tree r, char *key) {
    r = recursive_insert(r, &key);
     r->key->colour = BLACK;
     return r;
}

tree recursive_insert (tree r, char *key){
    /*If an empty tree, we can allocate memory, copy in the key into the node, and return the result. */
    if(r == NULL) {
        r = malloc(sizeof *r);
        r->key = malloc((strlen(key) + 1) * sizeof key[0]);
        r->left = NULL;
        r->right = NULL;
        r->key = strcpy(r->key, key);
        r->colour = RED;
        return r;
    }

    /* If the current top node value is greater than key being inserted, then we insert into the left subtree */
    if(strcmp(r -> key, key) > 0) {
        r->left = tree_insert(r->left, key);
        /* else if the current top node value is less than key being inserted, then we insert into the right subtree */
    } else if(strcmp(r -> key, key) < 0) {
        r->right = tree_insert(r->right, key);
    }

    r = tree_fix(r);
    /* return modified tree */
    return r;
}

tree tree_fix (tree r){
    if(IS_RED(r->left)){ /* If left child of root (A) is red */
    
        if(IS_RED(r->left->left)){ /* and if left-left child of root (C) is red, LL */ 
            if(IS_RED(r->right)){ /* and if the right child of root (B, the uncle of C) is red, R */
                r->colour = RED; /* set root (R) to red */
                r->left->colour = BLACK; /* set left child of root (A) to black */
                r->right->colour = BLACK; /* set right child of root (B) to black */
                
            }else { /* else if the right child of root (B, the uncle of C) is black, R */
                r = right_rotate(r); /* right-rotate root (R) */
                r->colour = BLACK; /* set new root (A) to black */
                r->right->colour = RED; /* set old root (new child, R) to red */
            } /*R*/
        } /*LL*/
        
        if(IS_RED(r->left->right)){/*when z is right and is red LR */
            if(IS_RED(r->right)){/*when uncle is red R*/
                r->colour = RED;
                r->left->colour = BLACK;
                r->right->colour = BLACK;
                
            }else {/*when uncle is BLACK R*/
                r->left = left_rotate(r->left);
                r = right_rotate(r);
                r->colour = BLACK;
                r->right->colour = RED;
            }/*R*/
        }/*LR*/
    }/*L*/

    if(IS_RED(r->right)){/* lets check if right is red*/
        if(IS_RED(r->right->left)){/*when z is left and parent is left and is red RL*/ 
            if(IS_RED(r->left)){/*when uncle is red L*/
                r->colour = RED;
                r->left->colour = BLACK;
                r->right->colour = BLACK;
                
            }else {/*when uncle is BLACK L*/
                r->right = right_rotate(r->right);
                r = left_rotate(r);
                r->colour = BLACK;
                r->left->colour = RED;
            }/*L*/
        }/*RL*/
        
        if(IS_RED(r->right->right)){/*when z is right and parent is left and is red RR */
            if(IS_RED(r->left)){/*when uncle is red L*/
                r->colour = RED;
                r->left->colour = BLACK;
                r->right->colour = BLACK;
                
            }else {/*when uncle is BLACK L*/
                r = left_rotate(r);
                r->colour = BLACK;
                r->left->colour = RED;
            }/*L*/
        }/*RR*/
    }/*R*/

    return r;
}

void tree_inorder(tree r, void f(char *s)) {
    /* if tree is null then return, stopping */
    if(r == NULL) {
        return;
    }
    /* call self on left subtree, traversing recursively */
    tree_inorder(r->left, f);
    /* call print method on current node */
    f(r->key);
    /* call self on right subtree, traversing recursively */
    tree_inorder(r->right, f);
}

void tree_preorder(tree r, void f(char *s)) {
    /* if tree is null then return, stopping */
    if(r == NULL) {
        return;
    }
    /* call print method on current node */
    f(r->key);
    /* call self on left and right, traversing subtree recursively */
    tree_preorder(r->left, f);
    tree_preorder(r->right, f);
}

tree tree_delete(tree r, char *key) {
    char *tmp;
    tree tmp_tree;

    /* if tree is null then return, stopping */
    if(r == NULL) {
        return NULL;
    }
 
    /* 
     * if node to delete matches node found then take out node, 
     *
     * else if nodes value is more than value of node to delete then call delete
     * recursively on left subtree
     * 
     * else if nodes value is less than value of node to delete then call delete 
     * recursively on right subtree
     */
    if(strcmp(r -> key, key) == 0) {
        if(r -> left == NULL) {
            free(r -> key);
            tmp_tree = r -> right;
            free(r);
            r = tmp_tree;
        } else if(r -> right == NULL) {
            free(r -> key);
            tmp_tree = r -> left;
            free(r);
            r = tmp_tree;
        } else {
            tmp_tree  = r -> right;
            while(tmp_tree -> left != NULL) {
                tmp_tree = tmp_tree -> left;
            }
            /* swap node values of node and leftmost node from right subtree,
             * then delete node */
            tmp = r -> key;
            r -> key = tmp_tree -> key;
            tmp_tree -> key = tmp;
            r -> right = tree_delete(r -> right, tmp_tree -> key);
        }
    } else if(strcmp(r -> key, key) > 0) {
        r -> left = tree_delete(r -> left, key);
    } else if(strcmp(r -> key, key) < 0) {
        r -> right = tree_delete(r -> right, key);
    }

    /* return modified tree */
    return r;
}

extern tree right_rotate(tree r){
    tree temp;

    temp = r;
    r = r->left;
    temp->left = r->right;
    r->right = temp;

    return r;
}
extern tree left_rotate(tree r){
    tree temp;

    temp = r;
    r = r->right;
    temp->right = r->left;
    r->left = temp;

    return r;
}

tree tree_free(tree r) {
    /* if tree is null then return, stopping */
    if(r == NULL) {
        return NULL;
    }

    /* free left and right subtrees recursively */
    tree_free(r -> left);
    tree_free(r -> right);

    /* free node and it's key */
    free(r -> key);
    free(r);
    return NULL;
}

