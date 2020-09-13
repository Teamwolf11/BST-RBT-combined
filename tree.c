#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"
#include "mylib.h"

#define IS_BLACK(x) ((NULL == (x)) || (BLACK == (x)->colour))
#define IS_RED(x) ((NULL != (x)) && (RED == (x)->colour))

static tree_t tree_type;

/*
 * tree node
 * key - value
 * left - pointer to left child node
 * right - pointer to right child node
 */
struct tree_node { 
    char *key;
    int frequency;
    rbt_colour colour;
    tree_t typeOfTree;
    tree left;
    tree right;
};

/**
 * combination tree ADT of either BST or RBT.
 * tree type based off enumerated type passed through.
 * returns null node to represent empty new tree.
 * @param t - the tree.
 */
tree tree_new(tree_t t) {
    if (t == BST) {
        tree_type = BST;
    } else {
        tree_type = RBT; 
    }
    /* tree_type = t; */
    return NULL;
}

/**
 * search for node based on value.
 * @param r - the tree to start at.
 * @param key - value we are searching for.
 * @return 0 if not found, 1 if found.
 */
int tree_search(tree r, char *key) {
    if (r == NULL) {
        return 0;
    }
    /* strcmp returns 0 if strings are equal, 1 if the current key is bigger than the key being searched, and negative if
     * the current key is less than the key being searched
     */

    /* If the searched key is greater, search left tree instead */
    if (strcmp(r->key, key) > 0) {
        return tree_search(r->left, key);
        /* If the searched key is less than, search right tree instead */
    } else if(strcmp(r->key, key) < 0) {
        return tree_search(r->right, key);
    }
    /* If the keys are equal, return 1 */
    return 1;
}

/*
 * insert function.
 * @param r - tree to insert into.
 * @param key - value we want to insert.
 * @return r - the modified tree.
 */
tree recursive_insert (tree r, char *key){
    /*If an empty tree, we can allocate memory, copy in the key into the node, and return the result. */
    if(r == NULL) {
        r = emalloc(sizeof *r);
        r->key = emalloc((strlen(key) + 1) * sizeof key[0]);
        r->left = NULL;
        r->right = NULL;
        r->key = strcpy(r->key, key);
        r->colour = RED;
        r->frequency = 1;
        return r;
    }

    /* If the current top node value is greater than key being inserted, then we insert into the left subtree */
    if(strcmp(r -> key, key) > 0) {
        r->left = recursive_insert(r->left, key);
        /* else if the current top node value is less than key being inserted, then we insert into the right subtree */
    } else if(strcmp(r -> key, key) < 0) {
        r->right = recursive_insert(r->right, key);
    } else {
        r->frequency++;
    }
    if(tree_type == RBT){
        r = tree_fix(r);
    } /* this is for when it is an RBT it will run the fix function */
    
    /* return modified tree */
    return r;
}

/*
 * insert function continued.
 * @param r - tree to insert into.
 * @param key - value we want to insert.
 * @return r - the modified tree.
 */
tree tree_insert(tree r, char *key) {
    r = recursive_insert(r, key);
    r->colour = BLACK;
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

/*
 * rotate function for tree_fix.
 * @param r - the tree to right rotate.
 */
tree right_rotate(tree r){
    tree temp;

    temp = r;
    r = r->left;
    temp->left = r->right;
    r->right = temp;

    return r;
}

/*
 * rotate function for tree_fix.
 * @param r - the tree to left rotate.
 */
tree left_rotate(tree r){
    tree temp;

    temp = r;
    r = r->right;
    temp->right = r->left;
    r->left = temp;

    return r;
}

/*
 * print function for inorder.
 * @param r - the tree to print.
 * @param f - print function.
 */
void tree_inorder(tree r, void f(char *s)) {
    /* if tree is null then return, stopping */
    if(r == NULL) {
        return;
    }
    /* call self on left subtree, traversing recursively */
    tree_inorder(r->left, f);

    if (IS_RED(r)) {
        printf("red:\t");
    } else {
        printf("black:\t");
    }
    
    /* call print method on current node */
    f(r->key);
    /* call self on right subtree, traversing recursively */
    tree_inorder(r->right, f);
}

/*
 * print function for preorder.
 * @param r - the tree to print.
 * @param f - print function.
 */
void tree_preorder(tree r, void f(char *s)) {
    /* if tree is null then return, stopping */
    if(r == NULL) {
        return;
    }
    if (IS_RED(r)) {
        printf("red:\t");
    } else {
        printf("black:\t");
    }
    /* call print method on current node */
    f(r->key);
    /* call self on left and right, traversing subtree recursively */
    tree_preorder(r->left, f);
    tree_preorder(r->right, f);
}


/*
 * computes the 'maximum' depth of a tree.
 * the number of nodes along the longest path,
 * from the root node down to the farthest leaf node.
 * @param r - the tree.
 */
int tree_depth(tree r){
int lDepth = 0;
int rDepth = 0;
if (r == NULL)
    return -1;
else
    {
        /* compute the depth of each subtree */
        lDepth = tree_depth(r->left);
        rDepth = tree_depth(r->right);
  
        /* use the larger one */
        if (lDepth > rDepth){
            return(lDepth+1);
        }else{
            return(rDepth+1);
        }
    }
}

/*
 * tree destruction function - frees nodes and nodes key recursively.
 * @param r - node to free.
 * @return NULL - a null pointer.
 */
tree tree_free(tree r) {
    /* if tree is null then return, stops */
    if(r == NULL) {
        return NULL;
    }
    /* free left and right subtrees recursively */
    tree_free(r -> left);
    tree_free(r -> right);

    /* free node and the key */
    free(r -> key);
    free(r);
    return NULL;
}

/**
 * Traverses the tree writing a DOT description about connections, and
 * possibly colours, to the given output stream.
 *
 * @param t the tree to output a DOT description of.
 * @param out the stream to write the DOT output to.
 */
static void tree_output_dot_aux(tree t, FILE *out) {
    if(t->key != NULL) {
        fprintf(out, "\"%s\"[label=\"{<f0>%s:%d|{<f1>|<f2>}}\"color=%s];\n",
                t->key, t->key, t->frequency,
                (RBT == tree_type && RED == t->colour) ? "red":"black");
    }
    if(t->left != NULL) {
        tree_output_dot_aux(t->left, out);
        fprintf(out, "\"%s\":f1 -> \"%s\":f0;\n", t->key, t->left->key);
    }
    if(t->right != NULL) {
        tree_output_dot_aux(t->right, out);
        fprintf(out, "\"%s\":f2 -> \"%s\":f0;\n", t->key, t->right->key);
    }
}

/**
 * Output a DOT description of this tree to the given output stream.
 * DOT is a plain text graph description language (see www.graphviz.org).
 * You can create a viewable graph with the command
 *
 *    dot -Tpdf < graphfile.dot > graphfile.pdf
 *
 * You can also use png, ps, jpg, svg... instead of pdf
 *
 * @param t the tree to output the DOT description of.
 * @param out the stream to write the DOT description to.
 */
void tree_output_dot(tree t, FILE *out) {
    fprintf(out, "digraph tree {\nnode [shape = Mrecord, penwidth = 2];\n");
    tree_output_dot_aux(t, out);
    fprintf(out, "}\n");
}
