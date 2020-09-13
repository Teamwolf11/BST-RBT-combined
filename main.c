
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include "tree.h"
#include "mylib.h"

#define WORDSIZE 10000

static tree_t type; 


/* 
 * print function to pass to tree_preorder function in tree.c.
 * @param freq - frequency of key.
 * @param word - the key/value.
 */
static void print_info(int freq, char *word) {
    printf("%-4d %s\n", freq, word);
}

/*
 * @param s.
 */
void print_key(char *s){
    printf("%5s\n",s);
}

/* 
 * tree main function.
 * @param argc - argument count.
 * @param argv - argument array.
 * @return - exit.
 */
int main(int argc, char **argv) {
    tree b;
    const char *optstring = "c:df:orh";
    char option;
    /* int i; */
    FILE *filename;
    char wordOnDictionary[WORDSIZE];
    /* int wordcountDictionary; */
    char word[WORDSIZE];
    /* char **listToCheck= NULL; */
    /* int countList; */
    int searchResult;
    int  is_c =0;
    int depth;
    int is_d_called =0;
    int is_f = 0;
    int is_o =0;
    
    /* default BST. */
    type = BST;
 
    /**program flags**/
    while ((option = getopt(argc, argv, optstring)) != EOF) {
        switch (option) {
            case 'c':
                /* do something */
                is_c = 1;
                filename =fopen(optarg, "r");
                /* printf("10"); */
                break;
            case 'd':
                /* print tree depth. */
                /* the argument after the -b is available
                   in the global variable 'optarg' */
                is_d_called = 1;
                break;
            case 'f':
                /* do something else */
                is_f = 1;

                break;
            case 'o':
                is_o =1;
                
                    printf("-o works");
                
                break;
            case 'r':
                /* tree type becomes RBT. */
                type = RBT; 
                break;
            case 'h': /* help message. */
            default:
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
        /* printf("9"); */
    }
    
    /* if(type == RBT) printf("RBT\n"); */
    /* printf("14"); */
    b = tree_new(type); /* we have to put this new after switch somehow IDK how
                           (i was thinking just after but we can make this a method)
                           as the -r  might be the last arg given and therefore if we run it
                           early, we won't have the right RBT/BST */
    /* printf("15"); */
    while (getword(wordOnDictionary, WORDSIZE, stdin) != EOF) {
        /*this will get all the words from the dictionary*/
        b = tree_insert(b,wordOnDictionary);/*this will insert dictionary words into tree
                                              but this has to happen before the comparison step*/
    } /* end while */
    /* printf("11"); */
    if(is_c == 1){
        /*-------------------------------------------------------------------------------------------------------------*/

        /* word = ""; */
        /* printf("12\n"); */
       
        /**checks spelling of words from file using words passed to stdin as the dictionary.**/
        while (getword(word, sizeof word, filename) != EOF) {
            /*this can happen before the insertion
              of dictionary words into tree as it is not affected by order*/
            searchResult = tree_search(b, word);
                   
                if(searchResult == 0){
                    printf("%s\n",word);
                }else if(searchResult == 1){
                    /* printf("Found the word: %s\n", word); */
                }
                else{
                    printf("Something went wrong when word was sent to the search function in main and it made searchResult a bad value");
                }
        }/*end while loop for going through all the words in the filetobespellchecked (aka filename)*/
        fclose(filename);
        
        /*------------------------------------------------------------------------------------------------------------*/
    }/** if the is_c ==1 */
   

    /*if is_d_called and is_c ignored print the tree_depth.*/
    if(is_c == 0 && is_d_called == 1){
        depth = tree_depth(b); 
        printf("print tree depth: %d\n", depth);
        exit(EXIT_SUCCESS);

    }
    /* tree_preorder(b, print_key); */
    /* printf("Hello Mike\n"); */
    /* tree_inorder(b, print_key); */

   

    /* printf("%d\n",rbt_search(b,"abc")); */
    return EXIT_SUCCESS;
}
