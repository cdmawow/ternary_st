#ifndef _tst_search_tree_h_
#define _tst_search_tree_h_  1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* forward-reference ternary search tree node and typedef */
struct node_tst;
typedef struct node_tst node_tst;


/** tst_ins_del() ins/del copy or reference of 's' from ternary search tree.
 *  insert all nodes required for 's' in tree at eqkid node of leaf. if 'del'
 *  is non-zero deletes 's' from tree, otherwise insert 's' at node->eqkid
 *  with node->key set to the nul-chracter after final node in search path. if
 *  'cpy' is non-zero allocate storage for 's', otherwise save pointer to 's'.
 *  if 's' already exists in tree, increment node->refcnt. (to be used for del).
 *  returns address of 's' in tree on successful insert (or on delete if refcnt
 *  non-zero), NULL on allocation failure on insert, or on successful removal
 *  of 's' from tree.
 */
void *tst_ins_del (node_tst **root, char * const *s, const int del, const int cpy);

/** tst_search(), non-recursive find of a string in ternary tree.
 *  returns pointer to 's' on success, NULL otherwise.
 */
void *tst_search (const node_tst *p, const char *s);

/** tst_search_prefix() fills ptr array 'a' with words prefixed with 's'.
 *  once the node containing the first prefix matching 's' is found
 *  tst_suggest() is called to traverse the ternary_tree beginning
 *  at the node filling 'a' with pointers to all words that contain
 *  the prefix upto 'max' words updating 'n' with the number of words
 *  in 'a'. a pointer to the first node is returned on success
 *  NULL otherwise.
 */
void *tst_search_prefix (const node_tst *root, const char *s,
                        char **a, int *n, const int max);

/** print_word(), function for tst_traverse_fn, print each word. */
void print_word (const void *node, void *data);

/** tst_traverse_fn(), traverse tree calling 'fn' on each word.
 *  prototype for 'fn' is void fn(const void *, void *). data can
 *  be NULL if unused.
 */
void tst_traverse_fn (const node_tst *p, void(fn)(const void *, void *), void *data);

/** free the ternary search tree rooted at p, data storage internal. */
void tst_free_all (node_tst *p);

/** free the ternary search tree rooted at p, data storage external. */
void tst_free (node_tst *p);

/** access functions tst_get_key(), tst_get_refcnt, & tst_get_string().
 *  provide access to struct members through opague pointers availale
 *  to program.
 */
char tst_get_key (const node_tst *node);
unsigned tst_get_refcnt (const node_tst *node);
char *tst_get_string (const node_tst *node);

#endif

