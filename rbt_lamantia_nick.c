#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
	int data;
	int color; /* 1 = red; 0 = black */
	struct Node *parent;
	struct Node *leftChild;
	struct Node *rightChild;
} Node;

typedef struct Data {
	int count;
	int sum;
} Data;

void insert(Node **head, int value);
void freeAll(Node *head);
int height(Node *head);
void countAndSumRanges(Node *head, Data *ranges);

int main(void) {
	char *color;
	int value, size = 0, sizeOfDataFile;
	Node *root = NULL;
	while (scanf("%d\n", &value) != EOF) {
		insert(&root, value);
	}
	Data *ranges = calloc(4, sizeof(Data));
	countAndSumRanges(root, ranges);

	printf("The number of nodes with key values in the range [0 - 1000] is %d\n", (ranges + 0)->count);
	printf("The sum of the key values in the range [0 - 1000] is %d\n", (ranges  + 0)->sum);
	printf("The number of nodes with key values in the range [1000 - 2000] is %d\n", (ranges + 1)->count);
	printf("The sum of the key values in the range [1000 - 2000] is %d\n", (ranges  + 1)->sum);
	printf("The number of nodes with key values in the range [2000 - 3000] is %d\n", (ranges + 2)->count);
	printf("The sum of the key values in the range [2000 - 3000] is %d\n", (ranges  + 2)->sum);
	printf("The number of nodes with key values in the range [3000 - 4000] is %d\n", (ranges + 3)->count);
	printf("The sum of the key values in the range [3000 - 4000] is %d\n", (ranges + 3)->sum);
	printf("The height of your resulting tree is %d\n", height(root));

	freeAll(root);
	free(ranges);
	return(0);
}

int height(Node *head) {
	int leftHeight = 0, rightHeight = 0;
	if (head->leftChild == NULL) {
		leftHeight = 0;
	} else {
		leftHeight += 1 + height(head->leftChild);
	}

	if (head->rightChild != NULL) {
		rightHeight += 1 + height(head->rightChild);
	} else {
		rightHeight = 0;
	}

	if (rightHeight > leftHeight) {
		return rightHeight;
	} else {
		return leftHeight;
	}
}

void countAndSumRanges(Node *head, Data *ranges) {
	if (head->leftChild != NULL) countAndSumRanges(head->leftChild, ranges);
	if (head->rightChild != NULL) countAndSumRanges(head->rightChild, ranges);

	if (head->data <= 1000) {
		(ranges + 0)->count++;
		(ranges + 0)->sum += head->data;
	}

	if (head->data >= 1000 && head->data <= 2000) {
		(ranges + 1)->count++;
		(ranges + 1)->sum += head->data;
	}

	if (head->data >= 2000 && head->data <= 3000) {
		(ranges + 2)->count++;
		(ranges + 2)->sum += head->data;
	}

	if (head->data >= 3000 && head->data <= 4000) {
		(ranges + 3)->count++;
		(ranges + 3)->sum += head->data;
	}
}

void insert(Node **head, int value) {
	int valueFound = 0, leafReached = 0;
	Node *traversePtr, *uncle, *current, *parent, *grandparent, *gpp, *gp;
	Node *newNode = malloc(sizeof(Node));
	if (newNode == NULL) {
		printf("Error allocating memory.\n");
		printf("Session terminated.\n");
		exit(0);
	}

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

		/* Infinite loop in some conditions.  Check nested if else below. */
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

		newNode->parent = traversePtr;

		current = newNode;
		parent = current->parent;
		grandparent = parent->parent;

		while (current->color == 1 && parent->color == 1) {
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
						current->parent = grandparent->parent;
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
					parent = current->parent;
					if (parent != NULL) {
						grandparent = parent->parent;
						if (grandparent != NULL) {
							if (parent == grandparent->leftChild) {
								uncle = grandparent->rightChild;
							} else {
								uncle = grandparent->leftChild;
							}
						} else break;
					} else break;
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
						grandparent->parent = parent;
					}
					grandparent->color = 1;
					parent->color = 0;

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
		} else {
			free(newNode);
		}
	}
}

void freeAll(Node *head) {
	if (head->leftChild != NULL) freeAll(head->leftChild);
	if (head->rightChild != NULL) freeAll(head->rightChild);
	free(head);
}

