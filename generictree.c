/**
 * Implementation of binary tree structure.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "generictree.h"
#include "stack.h"

Tree *initTree(int (*destroy)(void *data), char *(*toString)(void *data),
               int (*compare)(void *data1, void *data2)) {
    Tree *newTree;
    if ((newTree = malloc(sizeof(Tree))) == NULL) {
        fprintf(stderr, "ERROR: Couldn't malloc for new Tree\n");
        newTree = NULL;
    }
    else {
        newTree->size = 0;
        newTree->destroy = destroy;
        newTree->toString = toString;
        newTree->compare = compare;
        newTree->root = NULL;
    }
    return newTree;
}

TreeNode *initTreeNode(void *data, char *key, int nChildren) {
    TreeNode *newNode;
    if ((newNode = malloc(sizeof(TreeNode))) == NULL) {
        fprintf(stderr, "ERROR: Couldn't malloc for new TreeNode\n");
        newNode = NULL;
    }
    else {
        newNode->data = data;
        newNode->key = key;
        newNode->nChildren = nChildren;
        if (nChildren == 0)
            nodeChildren(newNode) = NULL;
        else {
            if((nodeChildren(newNode) = malloc(sizeof(TreeNode*) * nChildren)) == NULL) {
                fprintf(stderr, "ERROR: Couldn't malloc for TreeNode children\n");
                nodeChildren(newNode) = NULL;
            }
            else {
                for (int i = 0; i < nChildren; i++)
                    nodeChild(newNode, i) = NULL;  // Initialize each child to NULL
            }
        }
    }
    return newNode;
}

// Assumes tree is a binary search tree! If not, use addData()
TreeNode *addBinData(Tree *tree, void *data, char *key) {
    TreeNode *ptr = treeRoot(tree);
    TreeNode *newNode;
    if (ptr == NULL) {
        newNode = initTreeNode(data, key, 2);
        treeRoot(tree) = newNode;
        treeSize(tree)++;
    }
    else {
        while (1) {
            if (numChildren(ptr) != 2) {
                fprintf(stderr, "ERROR: Can't addBinData to non-binary tree\n");
                fprintf(stderr, "       node %s has %d children\n",
                                            nodeKey(ptr), numChildren(ptr));
                newNode = NULL;
                break;
            }
            else {
                newNode = initTreeNode(data, key, 2);
                int cmp = treecmp(tree, ptr, newNode);
                if (cmp < 0) {
                    // newNode less than ptr
                    if (nodeChild(ptr, 0) == NULL) {
                        nodeChild(ptr, 0) = newNode;
                        treeSize(tree)++;
                        break;
                    }
                    else
                        ptr = nodeChild(ptr, 0);
                }
                else if (cmp > 0) {
                    // newNode greater than ptr
                    if (nodeChild(ptr, 1) == NULL) {
                        nodeChild(ptr, 1) = newNode;
                        treeSize(tree)++;
                        break;
                    }
                    else
                        ptr = nodeChild(ptr, 1);
                }
                else {
                    // newNode already exists
                    fprintf(stderr, "ERROR: %s already exists; can't add to tree\n", key);
                    freeTreeNode(tree, newNode, 1);
                    newNode = NULL;
                    break;
                }
            }
        }
    }
    return newNode;
}

TreeNode *addData(Tree *tree, TreeNode *n, int at, void *data,
                  char *key, int nChildren) {
    TreeNode *newNode;
    if (n == NULL) {
        if (at != 0) {
            fprintf(stderr, "ERROR: addData to null tree should be at 0\n");
            newNode = NULL;
        }
        else {
            treeRoot(tree) = initTreeNode(data, key, nChildren);
            treeSize(tree)++;
        }
    }
    else if (numChildren(n) < at) {
        fprintf(stderr, "ERROR: Can't add more children to TreeNode than indicated\n");
        newNode = NULL;
    }
    else {
        newNode = initTreeNode(data, key, nChildren);
        nodeChild(n, at) = newNode;
        treeSize(tree)++;
    }
    return newNode;
}

// Assumes child nodes (if any) are handled elsewhere
TreeNode *freeTreeNode(Tree *tree, TreeNode *node, int clearData) {
    if (clearData) {
        destroyTreeNode(tree, node);
        free(node->key);
    }
    free(nodeChildren(node));
    free(node);
}

void freeTree(Tree *tree) {
    if (treeRoot(tree) != NULL)
        freeAllNodes(tree, treeRoot(tree));
    free(tree);
}

void freeAllNodes(Tree *tree, TreeNode *n) {
    if (n != NULL) {
        for (int i = 0; i < numChildren(n); i++)
            freeAllNodes(tree, nodeChild(n, i));
        freeTreeNode(tree, n, 1);
    }
    // If n == NULL, node is empty so don't do anything
}

// Prints the tree in order if tree is binary, pre-order if not
void printTree(Tree *tree, TreeNode *node, int isBinary, int lvl) {
    if (isBinary) {
        if (node == NULL) {
            if (lvl > 0) {
                printf("|--");
                for (int i = 1; i < lvl; i++)
                    printf("----");
                printf(" %d) ", lvl);
            }
            printf("%s:\t%s\n", "{NULLKEY}", (tree->toString)(node));
            return;
        }
        printTree(tree, nodeChild(node, 0), 1, lvl + 1);
        if (lvl > 0) {
            printf("|--");
            for (int i = 1; i < lvl; i++)
                printf("----");
            printf(" %d) ", lvl);
        }
        printf("%s:\t%s\n", nodeKey(node), nodeStr(tree, node));
        printTree(tree, nodeChild(node, 1), 1, lvl + 1);
    }
    else {
        if (lvl > 0) {
            printf("|-");
            for (int i = 1; i < lvl; i++)
                printf("--");
            printf(" %d) ", lvl);
        }
        printf("%s:\t%s\n", (node == NULL) ? "{NULLKEY}" : nodeKey(node),
               (tree->toString)((node == NULL) ? NULL : node->data));
        if (node == NULL)
            return;
        for (int i = 0; i < numChildren(node); i++)
            printTree(tree, nodeChild(node, i), 0, lvl + 1);
    }
}

// Searches for the specified TreeNode in the Tree. If void *d != NULL (data),
// that's used as the key instead of string key. Does an in-order traversal for
// binary trees, and a pre-order traversal for non-binary trees.
TreeNode *findNode(Tree *tree, int isBinary, char *key, void *d) {
    Stack *stk = initStack(tree->destroy, tree->toString, tree->compare);
    TreeNode *n = treeRoot(tree);
    while (!stackEmpty(stk) || n != NULL) {
        if (isBinary) {
            /* Traverse a binary tree */
            if (n != NULL) {
                push(stk, n);
                n = nodeChild(n, 0);
            }
            else {
                n = (TreeNode*)pop(stk);
                // Check this node
                if ((d != NULL && (tree->compare)(n->data, d) == 0) ||
                                (key != NULL && strcmp(key, nodeKey(n)) == 0))
                    return n;
                n = nodeChild(n, 1);
            }
        }
        else {
            /* Traverse a non-binary tree */
            if (n != NULL) {
                // Check this node
                if ((d != NULL && (tree->compare)(n->data, d) == 0) ||
                                (key != NULL && strcmp(key, nodeKey(n)) == 0))
                    return n;
                if (numChildren(n) != 0) {
                    for (int i = numChildren(n) - 1; i >= 0; i--) {
                        // Add each child to the stack
                        push(stk, nodeChild(n, i));
                    }
                }
            }
            // First child if there were any, otherwise just next node
            n = (TreeNode*)pop(stk);
        }
    }
    freeStack(stk);
    return NULL;
}

// Deletes a TreeNode from the Tree. If void *d (data) != NULL, uses that to
// find the node to delete. Otherwise, uses the key.
// If the node to delete is a leaf, simply delete. If it has a single child,
// move the subtree starting from the child into its place. If it has multiple
// children, move the appropriate one if it's a binary tree, or just add them
// all as children to the deleted node's parent if it isn't a binary tree.
void deleteNode(Tree *tree, int isBinary, char *key, void *d) {
    TreeNode *n = treeRoot(tree);
    if (isBinary) {
        binarydelete(tree, n, key, d);
    }
    else {
        Stack *stk = initStack(tree->destroy, tree->toString, tree->compare);
        while (!stackEmpty(stk) || n != NULL) {
            /* Traverse a non-binary tree */
            if (n != NULL) {
                // Check this node
                TreeNode *nKid;
                for (int i = 0; i < numChildren(n); i++) {
                    nKid = nodeChild(n, i);
                    if ((d != NULL && (tree->compare)(nKid->data, d) == 0) ||
                            (key != NULL && strcmp(key, nodeKey(nKid)) == 0)) {
                        // found node to delete
                        if (numChildren(nKid) == 0)
                            nodeChild(n, i) = NULL;
                        else if (numChildren(nKid) == 1)
                            nodeChild(n, i) = nodeChild(nKid, 0);
                        else {
                            // node child has multiple children itself
                            int old = numChildren(n);
                            int p = numChildren(nKid);
                            if ((nodeChildren(n) = realloc(nodeChildren(n),
                                    sizeof(TreeNode*) * (old + p - 1))) == NULL) {
                                fprintf(stderr, "ERROR: Couldn't realloc nodeChildren\n");
                            }
                            else {
                                for (i; i < numChildren(n) - 1; i++)
                                    nodeChild(n, i) = nodeChild(n, i + 1);
                                for (int j = 0; j < p; j++)
                                    nodeChild(n, old - 1 + j) = nodeChild(nKid, j);
                                numChildren(n) = old + p - 1;
                            }

                        }
                        freeTreeNode(tree, nKid, 1);
                        return;
                    }
                }
                if (numChildren(n) != 0) {
                    for (int i = numChildren(n) - 1; i >= 0; i--) {
                        // Add each child to the stack
                        push(stk, nodeChild(n, i));
                    }
                }
            }
            n = (TreeNode*)pop(stk);
        }
        freeStack(stk);
    }
}

TreeNode *binarydelete(Tree *tree, TreeNode *n, char *key, void *d) {
    if (n == NULL)
        return n;
    else if ((d != NULL && (tree->compare)(n->data, d) > 0) ||
                (key != NULL && strcmp(nodeKey(n), key) > 0))
        nodeChild(n, 1) = binarydelete(tree, nodeChild(n, 1), key, d);
    else if ((d != NULL && (tree->compare)(n->data, d) < 0) ||
                (key != NULL && strcmp(nodeKey(n), key) < 0))
        nodeChild(n, 0) = binarydelete(tree, nodeChild(n, 0), key, d);
    else {  // found node to delete
        if (numChildren(n) == 0) {
            freeTreeNode(tree, n, 0);
            n = NULL;
        }
        else if (nodeChild(n, 0) == NULL) {
            TreeNode *temp = n;
            n = nodeChild(n, 1);
            freeTreeNode(tree, temp, 0);
        }
        else if (nodeChild(n, 1) == NULL) {
            TreeNode *temp = n;
            n = nodeChild(n, 0);
            freeTreeNode(tree, temp, 0);
        }
        else {
            TreeNode *tmp = binarymin(nodeChild(n, 0));
            nodeData(n) = nodeData(tmp);
            nodeKey(n) = nodeKey(tmp);
            nodeChild(n, 0) = binarydelete(tree, nodeChild(n, 0),
                                            nodeKey(tmp), nodeData(tmp));
        }
    }
    return n;
}

// Gets the smallest node starting from TreeNode n
TreeNode *binarymin(TreeNode *n) {
    while (nodeChild(n, 1) != NULL)
        n = nodeChild(n, 1);
    return n;
}

