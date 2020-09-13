#include <stdio.h>
#include <stdlib.h>
#include "mylib.h"
#include "tree.h"

static void print_info(int freq, char *word) {
    printf("%-4d %s\n", freq, word);
}

void print_key(char *s){
    printf("%5s\n",s);
}

int main(void) {
    int depth;
    
    tree r = tree_new(RBT);
    r = tree_insert(r, "h");
    r = tree_insert(r, "l");
    r = tree_insert(r, "i");
    r = tree_insert(r, "f");
    r = tree_insert(r, "j");
    r = tree_insert(r, "g");
    r = tree_insert(r, "k");
    r = tree_insert(r, "d");
    r = tree_insert(r, "a");
    r = tree_insert(r, "e");
    r = tree_insert(r, "b");
    r = tree_insert(r, "c");
    
    tree_preorder(r, print_key);
    printf("Hello Mike\n");
    tree_inorder(r, print_key);

    depth = tree_depth(r);
    printf("Depth: %d\n", depth);
   

    return EXIT_SUCCESS;
}
