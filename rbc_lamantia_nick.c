#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
	int data;
	int color; /* 1 = red; 0 = black */
	struct Node *parent;
	struct Node *leftChild;
	struct Node *rightChild;
} Node;

void insert(Node **head, int value, int *size);

int main(void) {
	char *color;
	int value, *size = 0;
	Node **root;
	*root = NULL;
	while (scanf("%d\n", &value) != EOF) {
		printf("%d\n", value);
		insert(root, value, size);
	}
	printf("Root: %d\tColor: %d\n", (*root)->data, (*root)->color);
	printf("Right Child: %d\tColor: %d\n", (*root)->rightChild->data, (*root)->rightChild->color);
	printf("Right Grandchild: %d\tColor: %d\n", (*root)->rightChild->rightChild->data, (*root)->rightChild->rightChild->color);
	printf("Done\n");
	return(0);
}

void insert(Node **head, int value, int *size) {
	int valueFound = 0, leafReached = 0;
	Node *traversePtr, *uncle, *current, *parent, *grandparent, *gpp, *gp;
	Node *newNode = malloc(sizeof(Node));

	newNode->data = value;
	newNode->color = 1;
	newNode->parent = NULL;
	newNode->leftChild = NULL;
	newNode->rightChild = NULL;

	if (*head == NULL) {
		newNode->color = 0;
		*head = newNode;
	} else {
		traversePtr = *head;
		while (!valueFound && !leafReached) {
			if (traversePtr->data == value) {
				valueFound = 1;
			} else if (traversePtr->data > value) {
				if (traversePtr->leftChild != NULL) {
					traversePtr = traversePtr->leftChild;
				} else {				
					leafReached = 1;
					traversePtr->leftChild = newNode;
				}
			} else {
				if (traversePtr->rightChild != NULL) {
					traversePtr = traversePtr->rightChild;
				} else {
					leafReached = 1;
					traversePtr->rightChild = newNode;
				}
			}
		}
		if (!valueFound) {
		*(size)++;

		newNode->parent = traversePtr;

		current = newNode;
		parent = current->parent;
		grandparent = parent->parent;

		while (parent->color == 1) {
			if (parent == grandparent->leftChild) {
				uncle = grandparent->rightChild;
			} else {
				uncle = grandparent->leftChild;
			}

			while (uncle->color == 1) {
				uncle->color = 0;
				parent->color = 0;
				
				if (grandparent != *head) {
				grandparent->color = 1;

				current = grandparent;
				parent = current->parent;
				grandparent = parent->parent;

				printf("Redesignating variables successful\n");

				if (parent == grandparent->leftChild) {
					uncle = grandparent->rightChild;
				} else {
					uncle = grandparent->leftChild;
				}
				} else break;
			}

			if (grandparent == *head) {
				break;
			}

			while (uncle->color == 0) {
				if (current == parent->leftChild &&  parent == grandparent->leftChild) {
					if (grandparent == grandparent->parent->leftChild) {
						grandparent->parent->leftChild = parent;
					} else {
						grandparent->parent->rightChild = parent;
					}
					parent->parent = grandparent->parent;

					grandparent->parent = parent;
					grandparent->leftChild = parent->rightChild;
					grandparent->leftChild->parent = grandparent;
					parent->rightChild = grandparent;
					parent->color = 0;
					grandparent->color = 1;
				} else if (current == parent->leftChild && parent == grandparent->rightChild) {
					grandparent->rightChild = current;
					current->parent = grandparent;

					parent->leftChild = current->rightChild;					
					current->rightChild = parent;
					parent->parent = current;

					current->parent = grandparent->parent;
					if (grandparent == grandparent->parent->leftChild) {
						grandparent->parent->leftChild = current;
					} else {
						grandparent->parent->rightChild = current;
					}
					
					grandparent->rightChild = current->leftChild;
					grandparent->rightChild->parent = grandparent;

					current->leftChild = grandparent;
					grandparent->parent = current;

					current->color = 0;
					grandparent->color = 1;
				} else if (current == parent->rightChild && parent == grandparent->leftChild) {
					grandparent->leftChild = current;
					current->parent = grandparent;

					parent->rightChild = current->leftChild;					
					current->leftChild = parent;
					parent->parent = current;

					current->parent = grandparent->parent;
					if (grandparent == grandparent->parent->leftChild) {
						grandparent->parent->leftChild = current;
					} else {
						grandparent->parent->rightChild = current;
					}
					
					grandparent->leftChild = current->rightChild;
					grandparent->leftChild->parent = grandparent;

					current->rightChild = grandparent;
					grandparent->parent = current;

					current->color = 0;
					grandparent->color = 1;
				} else {
					if (grandparent == grandparent->parent->leftChild) {
						grandparent->parent->leftChild = parent;
					} else {
						grandparent->parent->rightChild = parent;
					}
					parent->parent = grandparent->parent;

					grandparent->parent = parent;
					grandparent->rightChild = parent->leftChild;
					grandparent->rightChild->parent = grandparent;
					parent->leftChild = grandparent;
					parent->color = 0;
					grandparent->color = 1;
				}
				parent = current->parent;
				grandparent = parent->parent;
				if (parent == grandparent->leftChild) {
					uncle = grandparent->rightChild;
				} else {
					uncle = grandparent->leftChild;
				}
			}
			
		}
		} else {
			free(newNode);
		}
	}
}


