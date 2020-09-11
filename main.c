#include <stdio.h>
#include <stdlib.h>

#include "tree.h"
#include "mylib.h"

static void print_info(int freq, char *word) {
    printf("%-4d %s\n", freq, word);
}

void print_key(char *s){
    printf("%5s\n",s);
}

int main(void) {

    tree b= tree_new(RBT);
    b=tree_insert(b,"h");
    b=tree_insert(b,"l");
    b=tree_insert(b,"i");
    b=tree_insert(b,"f");
    b=tree_insert(b,"j");
    b=tree_insert(b,"g");
    b=tree_insert(b,"k");
    b=tree_insert(b,"d");
    b=tree_insert(b,"a");
    b=tree_insert(b,"e");
    b=tree_insert(b,"b");
    b=tree_insert(b,"c");
    
    tree_preorder(b, print_key);
    printf("Hello Mike\n");
    tree_inorder(b, print_key);

   

    /* printf("%d\n",rbt_search(b,"abc")); */
    return EXIT_SUCCESS;
}
