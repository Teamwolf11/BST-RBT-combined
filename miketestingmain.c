
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include "tree.h"
#include "mylib.h"

static tree_t type; 


static void print_info(int freq, char *word) {
    /*This is the method to be passsed to teh tree_ppreorder function in tree.c*/
    printf("%-4d %s\n", freq, word);
}

void print_key(char *s){
    printf("%5s\n",s);
}

int main(int argc, char **argv) {
    
    tree b;
    const char *optstring = "c:df:orh";
    char option;
    int i;
    char *fileToSpellcheck;
    char *wordOnDictionary;
    char **dictionary = NULL;
    int wordcountDictionary;
    char *word;
    char **listToCheck= NULL;
    int countList;
    int whileLoopCounter;
    int searchResult;
    int boolean;
    
    type = BST;
    boolean =0;/* I change this to true in case c*/
    
    while ((option = getopt(argc, argv, optstring)) != EOF) {
        switch (option) {
            case 'c':
                /* do something */
                boolean=1;            
                
                wordcountDictionary = 0;
                fileToSpellcheck = optarg;
                wordOnDictionary ="";
                while (getword(wordOnDictionary, sizeof wordOnDictionary, stdin) != EOF) {
                    /*this will get all the words from the dictionary*/
                    dictionary[wordcountDictionary++] = wordOnDictionary;
                } /* end while */


                
               
               


                word = "";
                while (getword(word, sizeof word, fileToSpellcheck) != EOF) {
                    /*this can happen before the insertion
                      of dictionary words into tree as it is not affected by order*/

                    /* This will get all the words for the file we want to spell check*/
                    listToCheck[countList++] = word;
                }/* end while*/

                
                
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
    if(boolean == 1){
    /* I put this in brackets as Idk where to put it, read comments below for more info*/
    /*---------------------------------------------------------------------------------------------------------------*/
    b = tree_new(type); /* we have to put this new after switch somehow IDK how
                           (i was thinking just after but we can make this a method)
                           as the -r  might be the last arg given and therefore if we run it
                           early, we won't have the right RBT/BST */
    for(i=0; i<wordcountDictionary;i++){
        b=tree_insert(b,dictionary[i]);/*this will insert dictionary words into tree
                                         but this has to happen before the comparison step*/
    }
    /*--------------------------------------------------------------------------------------------------------------*/



    
    /* I put this in brackets as Idk where to put it, due to the search call, marked with a lot of X this has to happen
       after the new function is called on the tree b*/
    /*---------------------------------------------------------------------------------------------------------------*/
    /*---------------------------------------------------------------------------------------------------------------*/
    for(i=0; i<countList; i++){/*this will go through all the words in the listToCheck*/

        while(whileLoopCounter++ < wordcountDictionary){

            searchResult = tree_search(b, listToCheck[whileLoopCounter]);/*XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX*/
            /*I added the XXX thingy so that I know that b has to be created before this happens*/


                        
            if(searchResult == 0){
                printf("%s",listToCheck[whileLoopCounter]);
            }else if(searchResult == 1){
                printf("Found the word: %s", listToCheck[whileLoopCounter]);
            }else{
                printf("Something went wrong when word was sent to the search function in main and it made searchResult a bad value");
            }
                        
        }/*end while*/
    }/*end for loop for going through all the words in the listToCheck*/
    /*---------------------------------------------------------------------------------------------------------------*/
    /*---------------------------------------------------------------------------------------------------------------*/
    }/** if the boolean ==1 */
    tree_preorder(b, print_key);
    printf("Hello Mike\n");
    tree_inorder(b, print_key);

   

    /* printf("%d\n",rbt_search(b,"abc")); */
    return EXIT_SUCCESS;
}
