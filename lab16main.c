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
    r = tree_insert(r, "Somnambulist");
    r = tree_insert(r, "Sonorous");
    r = tree_insert(r, "Serendipity");
    r = tree_insert(r, "Limerence");
    r = tree_insert(r, "Bombinate");
    r = tree_insert(r, "Ethereal");
    r = tree_insert(r, "Illicit");
    r = tree_insert(r, "Phosphenes");
    r = tree_insert(r, "Oblivion");
    r = tree_insert(r, "Ephemeral");

    
    tree_preorder(r, print_key);
    printf("Hello Mike\n");
    tree_inorder(r, print_key);

    depth = tree_depth(r);
    printf("Depth: %d\n", depth);
   

    return EXIT_SUCCESS;
}
