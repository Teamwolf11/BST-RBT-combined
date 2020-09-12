
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include "tree.h"
#include "mylib.h"

static tree_t type; 

static void print_info(int freq, char *word) {
    printf("%-4d %s\n", freq, word);
}

void print_key(char *s){
    printf("%5s\n",s);
}

int main(int argc, char **argv) {
    
    tree b;
    const char *optstring = "c:df:orh";
    char option;

    type = BST;

    while ((option = getopt(argc, argv, optstring)) != EOF) {
        switch (option) {
            case 'c':
                /* do something */
               
                    break;
            case 'd':
                /* the argument after the -b is available
                   in the global variable 'optarg' */


                /* tree_depth(b); */
                printf("print tree depth");
                exit(EXIT_SUCCESS);
                break;
            case 'f':
                /* do something else */
                break;
            case 'o':
                break;
            case 'r':
                type = RBT;
                break;
            case 'h':
            default:
                /* if an unknown option is given */
                if(option != 'h'){
                printf("unknown command line arg was given: -");
                printf("%c\n",option);
                }
                printf("Perform various operations using a binary tree.  By default, words\n");
                printf("are read from stdin and added to the tree, before being printed out\n");
                printf("alongside their frequencies to stdout.\n");
                printf("\n");
                printf("-c FILENAME  Check spelling of words in FILENAME using words\n");
                printf("             read from stdin as the dictionary.  Print timing\n");
                printf("             info & unknown words to stderr (ignore -d & -o)\n");
                printf("-d           Only print the tree depth (ignore -o)\n");
                printf("-f FILENAME  Write DOT output to FILENAME (if -o given)\n");
                printf("-o           Output the tree in DOT form to file 'tree-view.dot'\n");
                printf("-r           Make the tree an RBT (the default is a BST)\n");
                printf("\n");
                printf("-h           Print this message\n\n");

                exit(EXIT_FAILURE);
        }
    }
    if(type == RBT) printf("RBT\n");
    
    b = tree_new(type);
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
