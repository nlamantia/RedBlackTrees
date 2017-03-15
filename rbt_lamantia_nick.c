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
	Node *root = NULL;
	while (scanf("%d\n", &value) != EOF) {
		printf("%d\n", value);
		insert(&root, value, size);
	}
	printf("Root: %d\tColor: %d\n", (root)->data, (root)->color);
	printf("Left Child: %d\tColor: %d\n", (root)->leftChild->data, (root)->leftChild->color);
	printf("Right Child: %d\tColor: %d\n", (root)->rightChild->data, (root)->rightChild->color);
	printf("Right Grandchild: %d\tColor: %d\n", (root)->rightChild->leftChild->data, (root)->rightChild->leftChild->color);
	printf("Left Grandchild: %d\tColor: %d\n", (root)->leftChild->leftChild->data, (root)->leftChild->leftChild->color);
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

		while (parent->color == 1 && grandparent != NULL) {
			if (parent == grandparent->leftChild) {
				uncle = grandparent->rightChild;
			} else {
				uncle = grandparent->leftChild;
			}

			if (uncle != NULL && uncle->color == 1) {
				if (uncle != NULL) {
					uncle->color = 0;
				}
				parent->color = 0;
				
				if (grandparent != *head) {				
					grandparent->color = 1;
				}
				
				current = grandparent;
				if (current != NULL) {
					parent = current->parent;
					if (parent != NULL) {
						grandparent = parent->parent;
					} else break;
				} else break;

				if (grandparent != NULL && grandparent != *head) {
				if (parent == grandparent->leftChild) {
					uncle = grandparent->rightChild;
				} else {
					uncle = grandparent->leftChild;
				}
				} else {
					break;
				}
			} else if (uncle == NULL || uncle->color == 0) {
				if (current == parent->leftChild && parent == grandparent->rightChild) {

					if (current->rightChild != NULL) {
						current->rightChild->parent = parent;
					}
					parent->leftChild = current->rightChild;
					current->rightChild = parent;
					parent->parent = current;

					grandparent->rightChild = current;
					current->parent = grandparent;

					if (current->leftChild != NULL) {
						current->leftChild->parent = grandparent;
					}
					grandparent->rightChild = current->leftChild;
					current->leftChild = grandparent;

					current->color = 0;
					grandparent->color = 1;

					if (grandparent != *head) {
						if (grandparent == grandparent->parent->leftChild) {
							grandparent->parent->leftChild = current;
						} else {
							grandparent->parent->rightChild = current;
						}
					} else {
						*head = current;
						current->parent = NULL;
					}
					grandparent->parent = current;
					
					break;
				} else if (current == parent->rightChild && parent == grandparent->leftChild) {
					parent->parent = current;

					if (current->leftChild != NULL) {
						current->leftChild->parent = parent;
					}
					parent->rightChild = current->leftChild;
					current->leftChild = parent;

					grandparent->leftChild = current;
					current->parent = grandparent;

					if (current->rightChild != NULL) {
						current->rightChild->parent = grandparent;
					}					
					grandparent->leftChild = current->rightChild;
					grandparent->parent = current;
					current->rightChild = grandparent;

					current->color = 0;
					current->rightChild->color = 1;

					if (grandparent != *head) {					
						if (grandparent == grandparent->parent->leftChild) {
							grandparent->parent->leftChild = current;
						} else {
							grandparent->parent->rightChild = current;
						}
						current->parent = grandparent->parent;
						current = grandparent;
						parent = current->parent;
						if (parent != NULL) {
							grandparent = parent->parent;
						} else {
							break;
						}
					} else {
						*head = current;
						current->parent = NULL;
						break;
					}					
				} else if (current == parent->leftChild && parent == grandparent->leftChild) {
					if (parent->rightChild != NULL) {
						parent->rightChild->parent = grandparent;
					}
					grandparent->leftChild = parent->rightChild;
					parent->rightChild = grandparent;
					if (grandparent != *head) {
						parent->parent = grandparent->parent;
						if (grandparent == grandparent->parent->leftChild) {
							grandparent->parent->leftChild = parent;
						} else {
							grandparent->parent->rightChild = parent;
						}
						grandparent->parent = parent;
					} else {
						*head = parent;
						parent->parent = NULL;
					}
					grandparent->color = 1;
					parent->color = 0;
				} else  {
					if (parent->leftChild != NULL) {
						parent->leftChild->parent = grandparent;
					}
					grandparent->rightChild = parent->leftChild;
					parent->leftChild = grandparent;
					if (grandparent != *head) {
						parent->parent = grandparent->parent;
						if (grandparent == grandparent->parent->leftChild) {
							grandparent->parent->leftChild = parent;
						} else {
							grandparent->parent->rightChild = parent;
						}
						grandparent->parent = parent;
					} else {
						*head = parent;
						parent->parent = NULL;
					}
					grandparent->color = 1;
					parent->color = 0;
				}				
			}
			
		}
		} else {
			free(newNode);
		}
	}
}


