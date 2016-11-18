/**
 * Implementation of binary tree structure.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include "generictree.h"

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
        if((nodeChildren(newNode) = malloc(sizeof(TreeNode*) * nChildren)) == NULL) {
            fprintf(stderr, "ERROR: Couldn't malloc for TreeNode children\n");
            nodeChildren(newNode) = NULL;
        }
        else {
            for (int i = 0; i < nChildren; i++)
                nodeChild(newNode, i) = NULL;
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
                    fprintf(stderr, "ERROR: %s already exists; can't add to tree", key);
                    freeTreeNode(tree, newNode);
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
TreeNode *freeTreeNode(Tree *tree, TreeNode *node) {
    destroyTreeNode(tree, node);
    free(node->key);
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
        freeTreeNode(tree, n);
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