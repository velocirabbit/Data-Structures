/**
 * Header file for implementation of binary tree structure.
 *
 */
#ifndef GENERICTREE
#define GENERICTREE

// Macro functions
#define treeRoot(tree)  ((tree)->root)
#define treeSize(tree)  ((tree)->size)
#define destroyTreeNode(tree, node)     (((tree)->destroy)((node)->data))
#define numChildren(node)   ((node)->nChildren)
#define nodeChildren(node)  ((node)->children)
#define nodeChild(node, i)  (((node)->children)[i])
#define treecmp(tree, n1, n2)   (((tree)->compare)((n1)->data, (n2)->data))

typedef struct treenode_ {
    int nChildren;
    void *data;
    char *key;
    struct treenode_ **children;
} TreeNode;

typedef struct tree_ {
    int size;
    int (*destroy)(void *data);
    char *(*toString)(void *data);
    int (*compare)(void *key1, void *key2);
    TreeNode *root;
} Tree;

Tree *initTree(int (*destroy)(void *data), char *(*toString)(void *data),
               int (*compare)(void *data1, void *data2));
TreeNode *initTreeNode(void *data, char *key, int nChildren);
TreeNode *addBinData(Tree *tree, void *data, char *key);
TreeNode *addData(Tree *tree, TreeNode *n, int at, void *data,
                  char *key, int nChildren);
TreeNode *freeTreeNode(Tree *tree, TreeNode *node);
void freeTree(Tree *tree);
void freeAllNodes(Tree *tree, TreeNode *n);

//TODO: print, search, insert, remove


#endif