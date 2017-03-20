/*******************************************************************************************
* Nick LaMantia                        							   *
* 3/19/2017                            						   	   *
* Lab 1: Scarlet and Gray Trees	       							   *
* CSE 2331										   *
*											   *
* This program constructs a scarlet and gray tree (red black tree) using the numbers read  *
* in through standard input and displays the count and sum of values in the tree that fall *
* into each of the following ranges as well as the height of the overall tree: [0 - 1000], *
* [1000 - 2000], [2000 - 3000], and [3000 - 4000].					   *
*											   *
* Dr. Jones                            							   *
* Execution: ./a.out < input_file_name							   *
*                                      							   *
*******************************************************************************************/

#include <stdio.h>
#include <stdlib.h>

/* Data structure to represent each
 * node in the RBT
 */
typedef struct Node {
	int data;
	int color; /* 1 = red; 0 = black */
	struct Node *parent;
	struct Node *leftChild;
	struct Node *rightChild;
} Node;

/* Stores the count and sum for a given 
 * number range.
 */
typedef struct Data {
	int count;
	int sum;
} Data;

/* Creates a node for the value, if unique,
 * and places the node in its respective spot
 * in the tree
 */
void insert(Node **head, int value);

/* Clears all memory allocated to the tree nodes
 * and range data array
 */
void freeAll(Node *head);

/* Returns the height of the tree */
int height(Node *head);

/* Counts the number of values in each data range
 * and sums up all of the values in each range */
void countAndSumRanges(Node *head, Data *ranges);

int main(int argc, char **argv) {
	/* Temporarily stores the next value in the input file */
	int value;

	/* Initialize a pointer to the root node of the RBT */
	Node *root = NULL;

	/* Read in numbers and insert them into the tree until the
	 * end of the input file has been reached */
	while (scanf("%d\n", &value) != EOF) {
		insert(&root, value);
	}

	/* Store the count and sum of numbers in each of the following  ranges:
	 * [0 - 1000], [1000 - 2000], [2000 - 3000], and [30 - 4000] */
	Data *ranges = calloc(4, sizeof(Data));

	/* Obtain the values listed in the previous comment */
	countAndSumRanges(root, ranges);

	/* Display the required output */
	printf("The number of nodes with key values in the range [0 - 1000] is %d\n", (ranges + 0)->count);
	printf("The sum of the key values in the range [0 - 1000] is %d\n", (ranges  + 0)->sum);
	printf("The number of nodes with key values in the range [1000 - 2000] is %d\n", (ranges + 1)->count);
	printf("The sum of the key values in the range [1000 - 2000] is %d\n", (ranges  + 1)->sum);
	printf("The number of nodes with key values in the range [2000 - 3000] is %d\n", (ranges + 2)->count);
	printf("The sum of the key values in the range [2000 - 3000] is %d\n", (ranges  + 2)->sum);
	printf("The number of nodes with key values in the range [3000 - 4000] is %d\n", (ranges + 3)->count);
	printf("The sum of the key values in the range [3000 - 4000] is %d\n", (ranges + 3)->sum);
	printf("The height of your resulting tree is %d\n", height(root));

	/* Clear all memory allocated to tree nodes and range data */
	freeAll(root);
	free(ranges);

	/* Successfully terminate the program */
	return(0);
}

/* Returns the height of the tree */
int height(Node *head) {
	/* Height of the left and right subtrees of the root node (head) */
	int leftHeight = 0, rightHeight = 0;

	/* Determine the height of the left subtree if it exists */
	if (head->leftChild == NULL) {
		leftHeight = 0;
	} else {
		leftHeight += 1 + height(head->leftChild);
	}

	/* Determine the height of the right subtree if it exists */
	if (head->rightChild != NULL) {
		rightHeight += 1 + height(head->rightChild);
	} else {
		rightHeight = 0;
	}

	/* Return the height of the tallest subtree */
	if (rightHeight > leftHeight) {
		return rightHeight;
	} else {
		return leftHeight;
	}
}

/* Get the count and sum of values in each of the 4 ranges */
void countAndSumRanges(Node *head, Data *ranges) {
	/* Get the count and sum of values in the 4 ranges mentioned above
	 * in the left and right subtrees of head if they exist */
	if (head->leftChild != NULL) countAndSumRanges(head->leftChild, ranges);
	if (head->rightChild != NULL) countAndSumRanges(head->rightChild, ranges);

	/* Determine which range(s) the head's value belongs to and recalculate the
	 * count and sum for that range(s) */
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

/* Insert the given value into the tree */
void insert(Node **head, int value) {
	/* Boolean variables to dictate if a value exists in the tree and 
	 * if we have reached a leaf while traversing the tree */
	int valueFound = 0, leafReached = 0;

	/* Pointers to the current node while traversing the tree,
	 * the new node, the current node (new pointer to newNode), 
	 * the current node's parent, and grandparent */
	Node *traversePtr, *uncle, *current, *parent, *grandparent;

	/* Attempt to allocate memory for a new node; if it fails,
	 * display an error message and terminate the program */
	Node *newNode = malloc(sizeof(Node));
	if (newNode == NULL) {
		printf("Error allocating memory.\n");
		printf("Session terminated.\n");
		exit(0);
	}

	/* If memory allocation succeeds, store the given value in the
	 * new node and set its color to red (1) by default.
	 * NOTE: Red = 1 and Black = 0. */
	newNode->data = value;
	newNode->color = 1;
	newNode->parent = NULL;
	newNode->leftChild = NULL;
	newNode->rightChild = NULL;

	/* If the tree is empty, change the node's color to black and 
	 * set the head pointer to point to the new node. */
	if (*head == NULL) {
		newNode->color = 0;
		*head = newNode;
	} else {
		/* Otherwise, find where the node should be inserted 
		 * following Binary Search Tree properties */
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

		/* If the value doesn't already exist in the tree, insert the
		 * new node, and rotate and recolor the associated subtree as needed */
		if (!valueFound) {		
	
			newNode->parent = traversePtr;
	
			/* Create references to the new node's parent and grandparent */
			current = newNode;
			parent = current->parent;
			grandparent = parent->parent;
	
			/* Perform the following until RBT standards are met */
			while (current->color == 1 && parent->color == 1) {
				/* Determine the current node's uncle */
				if (parent == grandparent->leftChild) {
					uncle = grandparent->rightChild;
				} else {
					uncle = grandparent->leftChild;
				}
		
				/*If the uncle is red, change the parent and
				 * uncle's colors to black and the grandparent's
				 * color to red. Then, set current to current's 
				 * grandparent, and reset the values of parent
				 * and grandparent pointers */
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
				/* Otherwise, check the placement of the parent and grandparent with 
				 * respect to current and each other */
				} else if (uncle == NULL || uncle->color == 0) {
					
					/* If current is its parent's left child and current's parent is 
					 * current's grandparent's right child, rotate right around parent,
					 * rotate left around grandparent, and swap current and grandparent's
					 * colors. */
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

						/* Obtain a reference to the current node's new parent
						 * and grandparent if they exist */
						parent = current->parent;
						if (parent != NULL) {
							grandparent = parent->parent;
						} else break;

					/* If current is its parent's right child and current's parent is 
					 * current's grandparent's left child, rotate left around parent,
					 * rotate right around grandparent, and swap current and grandparent's
					 * colors. */
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

						/* Obtain a reference to the current node's new parent
						 * and grandparent if they exist */
						parent = current->parent;
						if (parent != NULL) {
							grandparent = parent->parent;
						} else break;

					/* If current is its parent's left child and current's parent is 
					 * current's grandparent's left child, rotate right around parent, 
					 * and swap parent and grandparent's colors. */
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
	
						/* Obtain a reference to the current node's new parent
						 * and grandparent if they exist */
						parent = current->parent;
						if (parent != NULL) {
							grandparent = parent->parent;
						} else break;

					/* If current is its parent's right child and current's parent is 
					 * current's grandparent's right child, rotate left around parent, 
					 * and swap parent and grandparent's colors. */
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
	
						/* Obtain a reference to the current node's new parent
						 * and grandparent if they exist */
						parent = current->parent;
						if (parent != NULL) {
							grandparent = parent->parent;
						} else break;
					}				
				}
			}
		/* If the value already exists in the tree, free the newly allocated node
		 * and move on to the next value, if applicable */
		} else {
			free(newNode);
		}
	}
}

/* Frees all of the memory allocated to the tree nodes */
void freeAll(Node *head) {
	/* Free the memory allocated to the given tree's left and
	 * right subtree nodes, if any exist */
	if (head->leftChild != NULL) freeAll(head->leftChild);
	if (head->rightChild != NULL) freeAll(head->rightChild);

	/* Free the memory allocated to the given tree's root node */
	free(head);
}

