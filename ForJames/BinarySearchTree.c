#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct node {
    int data;
    struct node *right; 
    struct node *left;
}node_t;

node_t *newNode (int data) {
    node_t *p = NULL; 

    p = (node_t *)malloc(sizeof(node_t));

    if (p != NULL) {
        p->data = data;
        p->right = NULL;
        p->left = NULL;
    }
    return p;
}

node_t *insertNode (node_t *root, int data) {
    if (root == NULL) {
        return newNode(data);
    } else if (data > root->data) {
        root->right = insertNode(root->right, data);
    } else {
        root->left = insertNode(root->left, data);
    }
    return root;
}

node_t *findMax (node_t *root) {
    if (root == NULL) {
        return NULL;
    } else if (root->right != NULL){
        return findMax(root->right);
    }
    return root;
}

node_t *findMin (node_t *root) {
    if (root == NULL) {
        return NULL;
    } else if (root->left != NULL){
        return findMin(root->left);
    }
    return root;
}

void printAllNodes (node_t *root){
    if (root != NULL) {
        printAllNodes(root->left);
        printf("%i ", root->data);
        printAllNodes(root->right);
    }
}

void printMinOrMax (node_t *root, node_t *(*f)(node_t *)) {
    node_t *p = NULL;

    p = f(root);

    if (p != NULL) {
        if (f == &findMax) {
            printf("\nMax is %i\n", p->data);
        } else if (f == &findMin) {
            printf("\nMin is %i\n", p->data);
        } else {
            printf("Invalid function pointer\n");
        }
    }
}

void deleteAllNodes(node_t *root) {
    if (root != NULL) {
        deleteAllNodes(root->left);
        deleteAllNodes(root->right);
        printf("%i ", root->data);
        free(root);
    }
}

void deleteRoot(node_t **root) {
    if (*root != NULL) {
        printf("Delete all Nodes\n");
        deleteAllNodes(*root);
        printf("\n");
        *root = NULL;
    }
} 

int main() {
    node_t *root = NULL; 
	
	root = newNode(20);
	insertNode(root,42);
    insertNode(root,1);
	insertNode(root,5);
    insertNode(root,15);
    insertNode(root,9);
    insertNode(root,7);
    insertNode(root,12);
    insertNode(root,300);
    insertNode(root,25);
    insertNode(root,-40);
    insertNode(root,45);
    insertNode(root,0);

    printAllNodes(root);
    printMinOrMax(root, &findMax);
    printMinOrMax(root, &findMin);

    deleteRoot(&root);
    printAllNodes(root);

    system("pause");
    return 0; 
}