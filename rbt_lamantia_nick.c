#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
	int data;
	int color; /* 1 = red; 0 = black */
	struct Node *parent;
	struct Node *leftChild;
	struct Node *rightChild;
} Node;

int insert(Node **head, int value);
void freeAll(Node *head);

int main(void) {
	char *color;
	int value, size = 0, sizeOfDataFile;
	Node *root = NULL;
	while (scanf("%d\n", &value) != EOF) {
		printf("%d\n", value);
		size += insert(&root, value);
	}
	printf("Root: %d\tColor: %d\n", (root)->data, (root)->color);
	printf("Left Child: %d\tColor: %d\n", (root)->leftChild->data, (root)->leftChild->color);
	printf("Right Child: %d\tColor: %d\n", (root)->rightChild->data, (root)->rightChild->color);
	printf("Right Grandchild: %d\tColor: %d\n", (root)->rightChild->leftChild->data, (root)->rightChild->leftChild->color);
	printf("Left Grandchild: %d\tColor: %d\n", (root)->leftChild->leftChild->data, (root)->leftChild->leftChild->color);
	printf("Done\n");
	/*freeAll(root);*/
	return(0);
}

int insert(Node **head, int value) {
	int valueFound = 0, leafReached = 0;
	Node *traversePtr, *uncle, *current, *parent, *grandparent, *gpp, *gp;
	Node *newNode = malloc(sizeof(Node));
	if (newNode == NULL) {
		printf("Error allocating memory.\n");
		printf("Session terminated.\n");
		exit(0);
		return;
	}

	newNode->data = value;
	newNode->color = 1;
	newNode->parent = NULL;
	newNode->leftChild = NULL;
	newNode->rightChild = NULL;

	if (*head == NULL) {
		newNode->color = 0;
		*head = newNode;
		return 1;
	} else {
		traversePtr = *head;

		/* Infinite loop in some conditions.  Check nested if else below. */
		while (!valueFound && !leafReached) {
			printf("Value: %d\n", traversePtr->data);
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

		newNode->parent = traversePtr;

		current = newNode;
		parent = current->parent;
		grandparent = parent->parent;

		while (parent != NULL && parent->color == 1) {
			printf("Hello\n");
			if (parent == grandparent->leftChild) {
				uncle = grandparent->rightChild;
			} else {
				uncle = grandparent->leftChild;
			}

			if (uncle != NULL && uncle->color == 1) {
				printf("Red Uncle\n");
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

				if (grandparent != NULL) {
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
					printf("First if\n");
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
					
					parent = current->parent;
					if (parent != NULL) {
						grandparent = parent->parent;
						if (parent != *head) {
							if (parent == grandparent->leftChild) {
								uncle = grandparent->rightChild;
							} else {
								uncle = grandparent->leftChild;
							}
						}
					} else break;
				} else if (current == parent->rightChild && parent == grandparent->leftChild) {
					printf("First else if\n");
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
					current->rightChild = grandparent;
					current->color = 0;
					current->rightChild->color = 1;

					printf("Just before checking if grandparent is root\n");
					if (grandparent != *head) {					
						if (grandparent == grandparent->parent->leftChild) {
							grandparent->parent->leftChild = current;
						} else {
							grandparent->parent->rightChild = current;
						}
						current->parent = grandparent->parent;
						grandparent->parent = current;
					} else {
						grandparent->parent = current;
						*head = current;
						current->parent = NULL;
					}
					printf("Just after checking if grandparent is root\n");
					parent = current->parent;
					if (parent != NULL) {
						printf("Inside the if statement\n");
						grandparent = parent->parent;
						if (grandparent != NULL) {
							if (parent == grandparent->leftChild) {
								uncle = grandparent->rightChild;
							} else {
								uncle = grandparent->leftChild;
							}
						} else break;
					} else break;
					printf("End first else if\n");
				} else if (current == parent->leftChild && parent == grandparent->leftChild) {
					printf("Second else if\n");
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
						grandparent->parent = parent;
						*head = parent;
						parent->parent = NULL;
					}
					grandparent->color = 1;
					parent->color = 0;

					parent = current->parent;
					if (parent != *head) {
						grandparent = parent->parent;
						if (parent == grandparent->leftChild) {
							uncle = grandparent->rightChild;
						} else {
							uncle = grandparent->leftChild;
						}
					} else break;
				} else  {
					printf("Else\n");
					if (parent->leftChild != NULL) {
						parent->leftChild->parent = grandparent;
					}
					grandparent->rightChild = parent->leftChild;
					parent->leftChild = grandparent;
					if (grandparent != *head) {
						parent->parent = grandparent->parent;
						printf("before nested if\n");
						if (grandparent == grandparent->parent->leftChild) {
							printf("Nested if\n");
							grandparent->parent->leftChild = parent;
						} else {
							printf("Nested else\n");
							grandparent->parent->rightChild = parent;
						}
						printf("After nested if block\n");
						grandparent->parent = parent;
					} else {
						*head = parent;
						parent->parent = NULL;
						grandparent->parent = parent;
					}
					grandparent->color = 1;
					parent->color = 0;

					printf("Made it to reassignment\n");
					parent = current->parent;
					if (parent != NULL) {
						grandparent = parent->parent;
						if (grandparent !=  NULL) {
							if (parent == grandparent->leftChild) {
								uncle = grandparent->rightChild;
							} else {
								uncle = grandparent->leftChild;
							}
						}
					} else break;
				}				
			}
		}
		return 1;
		} else {
			free(newNode);
			return 0;
		}
	}
}

void freeAll(Node *head) {
	printf("%d\n", head->data);
	if (head->leftChild != NULL) freeAll(head->leftChild);
	if (head->rightChild != NULL) freeAll(head->rightChild);
	free(head);
}

