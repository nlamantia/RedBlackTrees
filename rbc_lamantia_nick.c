#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
	int data;
	int color; /* 1 = red; 0 = black */
	struct Node *parent;
	struct Node *leftChild;
	struct Node *rightChild;
} Node;

void insert(Node **head, int value);

int main(void) {
	int value;
	Node **root = NULL;
	while (scanf("%d", &value)) {
		insert(root, value);
	}

	return(0);
}

void insert(Node **head, int value) {
	int valueFound = 0;
	Node *traversePtr, *uncle, *current, *parent, *grandparent;
	Node *newNode = malloc(sizeof(Node));

	newNode->data  = value;
	newNode->color = 1;
	newNode->parent = NULL;
	newNode->leftChild = NULL;
	newNode->rightChild = NULL;

	if (head == NULL) {
		newNode->color = 0;
		*head = newNode;
	} else {
		traversePtr = *head;
		while (!valueFound) {
			if (traversePtr->data == value) {
				valueFound = 1;
			} else if (traversePtr->data > value) {
				if (traversePtr->leftChild != NULL) {
					traversePtr = traversePtr->leftChild;
				} else {				
					valueFound = 1;
					traversePtr->leftChild = newNode;
				}
			} else {
				if (traversePtr->rightChild != NULL) {
					traversePtr = traversePtr->rightChild;
				} else {
					valueFound = 1;
					traversePtr->rightChild = newNode;
				}
			}
		}
		newNode->parent = traversePtr;

		current = newNode;
		parent = current->parent;
		grandparent = parent->parent;

		while (parent->color == 1) {
			if (newNode->parent == newNode->parent->parent->leftChild) {
				uncle = current->parent->parent->rightChild;
			} else {
				uncle = current->parent->parent->leftChild;
			}

			while (uncle->color == 1) {
				uncle->color = 0;
				parent->color = 0;
				grandparent->color = 1;

				current = grandparent;
				parent = current->parent;
				grandparent = parent->parent;

				if (newNode->parent == newNode->parent->parent->leftChild) {
					uncle = current->parent->parent->rightChild;
				} else {
					uncle = current->parent->parent->leftChild;
				}
			}

			while (uncle->color == 0) {
				if (current == parent->leftChild &&  parent == grandparent->leftChild) {
					
				} else if (current == parent->leftChild && parent == grandparent->rightChild) {
					
				} else if (current == parent->rightChild && parent  == grandparent->leftChild) {
					
				} else {
					
				}
			}
			
		}
	}
}


