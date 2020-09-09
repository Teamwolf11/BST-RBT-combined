#include <stdio.h>
#include <stdlib.h>
#include "mylib.h"
#include "rbt.h"
#include <string.h>

#define IS_BLACK(x) ((NULL == (x)) || (BLACK == (x)->colour))
#define IS_RED(x) ((NULL != (x)) && (RED == (x)->colour))

struct rbtnode { /*should live in rbt.c*/
    char *key;
    rbt_colour colour;
    rbt left;
    rbt right;
};



int rbt_search(rbt b, char *key){
    if(b==NULL){
        return 0;
    }else if(strcmp((b->key),key)==0){
        return 1;
    }else if(strcmp((b->key),key) < 0){
        return rbt_search(b->right,key);
    }else if(strcmp((b->key),key) > 0){
        return rbt_search(b->left,key);
    }else{
        printf("This should never happen, it somehow didn't meet any of the if statments, in the rbt search method in the rbt.c class");
        exit(EXIT_FAILURE);
    }/*END ELSE*/
    
}/* end method rbt_search */

rbt rbt_insert(rbt b, char *strToInsert){
    if(b==NULL){
        b=emalloc(sizeof *b);
        b->key=emalloc((strlen(strToInsert)+1) * sizeof(b->key[0]));
        strcpy(b->key,strToInsert);
        b->colour = RED;
       
    }else if(strcmp((b->key),strToInsert) == 0){
        printf("The key is already there\n");
    }else if(strcmp((b->key),strToInsert) < 0){
        b->right = rbt_insert(b->right,strToInsert);
        
    }else if(strcmp((b->key),strToInsert) > 0){
        b->left = rbt_insert(b->left,strToInsert);
       
    }else{
        printf("This should never happen, it somehow didn't meet any of the if statments, in the rbt insert  method in the rbt.c class");
        exit(EXIT_FAILURE);
    }/*END ELSE*/
    /* printf("this only happens if key is already in there\n"); */
    b=rbt_fix(b);
    return b;
}/*end metho rbt insert*/

rbt rbt_new(){
    rbt b= NULL;
    return b;
}

rbt rbt_fix (rbt b){
    if(IS_RED(b->left)){/*when parent is left and red L */
        if(IS_RED(b->left->left)){/*when z is left and parent is red and is red LL*/ 
            if(IS_RED(b->right)){/*when uncle is red R*/
                b->colour = RED;
                b->left->colour = BLACK;
                b->right->colour = BLACK;
                
            }else {/*when uncle is BLACK R*/
                b = right_rotate(b);
                b->colour = BLACK;
                b->right->colour = RED;
            }/*R*/
        }/*LL*/
        
        if(IS_RED(b->left->right)){/*when z is right and is red LR */
            if(IS_RED(b->right)){/*when uncle is red R*/
                b->colour = RED;
                b->left->colour = BLACK;
                b->right->colour = BLACK;
                
            }else {/*when uncle is BLACK R*/
                b->left = left_rotate(b->left);
                b = right_rotate(b);
                b->colour = BLACK;
                b->right->colour = RED;
            }/*R*/
        }/*LR*/
    }/*L*/

    if(IS_RED(b->right)){/* lets check if right is red*/
        if(IS_RED(b->right->left)){/*when z is left and parent is left and is red RL*/ 
            if(IS_RED(b->left)){/*when uncle is red L*/
                b->colour = RED;
                b->left->colour = BLACK;
                b->right->colour = BLACK;
                
            }else {/*when uncle is BLACK L*/
                b->right = right_rotate(b->right);
                b = left_rotate(b);
                b->colour = BLACK;
                b->left->colour = RED;
            }/*L*/
        }/*RL*/
        
        if(IS_RED(b->right->right)){/*when z is right and parent is left and is red RR */
            if(IS_RED(b->left)){/*when uncle is red L*/
                b->colour = RED;
                b->left->colour = BLACK;
                b->right->colour = BLACK;
                
            }else {/*when uncle is BLACK L*/
                b = left_rotate(b);
                b->colour = BLACK;
                b->left->colour = RED;
            }/*L*/
        }/*RR*/
    }/*R*/

    return b;
}/* end rbt fix method gG*/





void rbt_inorder(rbt b, void f(char *word)){
    if(b==NULL){
        return;
    }else{
        rbt_inorder(b->left,f);
        f(b->key);
        rbt_inorder(b->right,f);
    } /* end else */
    
}/* end method inorder */

void rbt_preorder(rbt b, void f(char *word)){
    if(b==NULL){
        return;
    }else{
        f(b->key);
        rbt_preorder(b->left,f);
        rbt_preorder(b->right,f);
    } /* end else */
}/* end method preorder */
   
rbt rbt_delete (rbt b, char *deletingString){
    rbt temp = NULL;
    char  *tempKey=NULL;
    
    if(b==NULL){
        printf("string doesn't exist\n");
              
    }else if(strcmp((b->key),deletingString) == 0){
        if(b->left == NULL && b->right == NULL){
            free(b->key);
            free(b);
            b = NULL;
        }else if(b->left == NULL){
            free(b->key);
            temp = b->right;
            free(b);
            b = temp;
        }else if(b->right == NULL){
            free(b->key);
            temp = b->left;
            free(b);
            b = temp;
        }else{
            rbt findSuccessor = b->right;
            while(findSuccessor->left != NULL){
                findSuccessor=findSuccessor->left;
            }
            tempKey = findSuccessor->key;
            findSuccessor->key=b->key;
            b->key=tempKey;

            return rbt_delete(findSuccessor,deletingString);
        }/*end else*/
            
    }else if(strcmp((b->key),deletingString) < 0){
        b->right = rbt_delete(b->right,deletingString);

    }else if(strcmp((b->key),deletingString) > 0){
        b->left = rbt_delete(b->left,deletingString);
    }
   
    return b;
}

rbt right_rotate (rbt tree){
    rbt temp;

    temp=tree;
    tree=tree->left;
    temp->left=tree->right;
    tree->right=temp;

    return tree;
}

rbt left_rotate (rbt tree){
    rbt temp;

    temp=tree;
    tree=tree->right;
    temp->right=tree->left;
    tree->left=temp;

    return tree;
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

