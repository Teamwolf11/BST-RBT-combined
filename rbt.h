#ifndef RBT_H_
#define RBT_H_
typedef struct rbtnode *rbt;
typedef enum {RED,  BLACK} rbt_colour;

extern rbt rbt_delete(rbt b, char *str);
extern rbt rbt_free(rbt b);
extern void rbt_inorder(rbt b, void f(char *str));
extern rbt rbt_insert(rbt b, char *str);
extern rbt rbt_new();
extern void rbt_preorder(rbt b, void f(char *str));
extern int rbt_search(rbt b, char *str);
extern rbt right_rotate(rbt b);
extern rbt left_rotate(rbt b);
extern rbt rbt_fix (rbt b);
#endif
