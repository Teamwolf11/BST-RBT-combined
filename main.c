#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include "tree.h"
#include "mylib.h"
#include <time.h>

#define WORDSIZE 10000

static tree_t type; 

/**
 * print function to pass to tree_preorder function in tree.c.
 * @param freq - frequency of key.
 * @param word - the key/value.
 **/
static void print_info(int freq, char *word) {
    printf("%-4d %s\n", freq, word);
}

/**
 * Main function for tree.c.
 * Takes each use case, and acts upon them accordingly.
 * @param argc - argument count.
 * @param argv - argument array.
 * @return - exit.
 **/
int main(int argc, char **argv) {
    tree b;
    const char *optstring = "c:df:orh";
    char option; 
    FILE *filename;
    FILE *dotFile;
    FILE *customDotFile;
    char wordOnDictionary[WORDSIZE];
    char word[WORDSIZE];
    int depth;
    int is_c = 0;
    int is_d = 0;
    int is_f = 0;
    int is_o = 0;
    /**print timing variables**/
    clock_t fillStart, fillEnd, searchStart, searchEnd;
    int unknownWord = 0;
    double fillTime = 0;
    double searchTime = 0;
    
    /* default BST. */
    type = BST;
 
    /**program flags**/
    while ((option = getopt(argc, argv, optstring)) != EOF) {
        switch (option) {
            case 'c':
                is_c = 1;
                filename =fopen(optarg, "r");
                break;
            case 'd':
                /* print tree depth. */
                /* the argument after the -b is available
                   in the global variable 'optarg' */
                is_d = 1;
                break;
            case 'f':
                is_f = 1;
                customDotFile = fopen(optarg, "w");                                      
                break;
            case 'o':
                is_o =1;
                break;
            case 'r':
                /* tree type becomes RBT. */
                type = RBT; 
                break;
            case 'h': /* help message. */
            default:
                printf("Perform various operations using a binary tree.\n");
                printf("By default, words are read from stdin and\n");
                printf("added to the tree, before being printed out\n");
                printf("alongside their frequencies to stdout.\n");
                printf("\n");
                printf("-c FILENAME  Check spelling of words in FILENAME\n");
                printf("             using words read from stdin as\n");
                printf("             the dictionary. Print timing info\n");
                printf("             & unknown words to stderr\n");
                printf("             (ignore -d & -o)");
                printf("-d           Only print the tree depth (ignore -o)\n");
                printf("-f FILENAME  Write DOT output to FILENAME\n");
                printf("             (if -o given)");
                printf("-o           Output the tree in DOT form to file\n");
                printf("             'tree-view.dot'");
                printf("-r           Make the tree an RBT\n");
                printf("             (changing from default is a BST)");
                printf("\n");
                printf("-h           Print this message\n\n");

                exit(EXIT_FAILURE);
        }
    }
    
    b = tree_new(type); 

    /*all the words from the dictionary.*/
    fillStart = clock();
    while (getword(wordOnDictionary, WORDSIZE, stdin) != EOF) {
        /*insert dictionary words into tree*/
        b = tree_insert(b,wordOnDictionary);
    } /* end while */
    fillEnd = clock();
    fillTime = (fillEnd - fillStart) / (double)CLOCKS_PER_SEC;

    /**spell check words from filename.**/
    if(is_c == 1){    
        searchStart = clock();
        while (getword(word, sizeof word, filename) != EOF) {                   
            if(tree_search(b, word) == 0){
                unknownWord++;
                printf("%s\n",word);
            }
        }/*end while*/
        searchEnd = clock();
        searchTime = (searchEnd - searchStart) / (double)CLOCKS_PER_SEC;
        
        
        /**print timing information.**/
        fprintf(stderr, "Fill time     : %.6f\nSearch Time   : %.6f\n"
                , fillTime, searchTime);
        fprintf(stderr, "Unknown Words = %d\n", unknownWord);

        fclose(filename);
        
    }

    /*if is_d, is_c ignored print the tree_depth.*/
    if(is_c == 0 && is_d == 1){
        depth = tree_depth(b); 
        printf("print tree depth: %d\n", depth);
        exit(EXIT_SUCCESS);
    }
  
    /*if is_f and i_o, is_c is ignored.*/
    if(is_f == 1 && is_o == 1 && is_c == 0){
        tree_output_dot(b, customDotFile);
        fclose(customDotFile);
    }else if(is_o == 1 && is_c == 0){
        dotFile = fopen("tree-view.dot", "w");
        printf("Creating dot file 'tree-view.dot'\n");
        tree_output_dot(b,dotFile); 
        fclose(dotFile);
    }

    if(is_c == 0 && is_d == 00 && is_f == 0 && is_o ==0){
        tree_preorder(b, print_info);
    }

    /* Memory deallocation */
    tree_free(b);
    
    return EXIT_SUCCESS;
}
