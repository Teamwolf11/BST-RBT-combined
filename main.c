#include <stdio.h>
#include <stdlib.h>
#include "mylib.h"
#include "rbt.h"
void print_key(char *s){
    printf("%5s\n",s);
}

int main(void) {

    rbt b= rbt_new();
    b=rbt_insert(b,"abc");
    b=rbt_insert(b,"bbb");
    b=rbt_insert(b,"ccc");
    b=rbt_insert(b,"abc");
    b=rbt_insert(b,"bc");
    
    /* rbt_preorder(b, print_key); */

    rbt_inorder(b,print_key);
    b=rbt_delete(b,"bbc"); /* this doesn't exist */
    rbt_inorder(b,print_key);
    b=rbt_delete(b,"abc"); 
    rbt_inorder(b,print_key);
    b=rbt_delete(b,"bc");
    rbt_inorder(b,print_key);
    b=rbt_delete(b,"ccc");
    rbt_inorder(b,print_key);
    b=rbt_delete(b,"bbb");
    rbt_inorder(b,print_key);

    printf("%d\n",rbt_search(b,"abc"));
    return EXIT_SUCCESS;
}



