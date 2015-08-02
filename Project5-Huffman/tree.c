//Jonathan Sofer

//These functions will implement a binary tree abstract data type

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>

#include "tree.h"

struct tree
{
	int data;
	struct tree *left;
	struct tree *right;
	struct tree *parent;
};

//Function to detatch a node from its parent
void detatch(struct tree *root)
{
	if (root->parent == NULL)
		return;
	else if (root->parent->left == root) //I'm the left child
		root->parent->left = NULL;
	else if (root->parent->right == root) //I'm the right child
		root->parent->right = NULL;
	return;	
}

//Function to create a tree
//Runtime O(1)
struct tree *createTree(int data, struct tree *left, struct tree *right)
{
	struct tree *root;
	root = malloc(sizeof(struct tree));
	assert (root != NULL);
	root->data = data;
	root->left = left;
	root->right = right;
	root->parent = NULL;
	if (root->left != NULL)
	{
		detatch(root->left);
		root->left->parent = root;
	}	
	if (root->right != NULL)
	{	
		detatch(root->right);
		root->right->parent = root;
	}
    return root;	
}

//Function to destroy a tree using postorder
//Runtime O(n)
void destroyTree(struct tree *root)
{
	if (root == NULL)
		return;
	destroyTree(root->left);
	destroyTree(root->right);
	free(root);
}

//Function to return the data in the root of a subtree
//Runtime O(1)
int getData(struct tree *root)
{
	assert (root != NULL);
	return root->data;
}

//Function to return the data in the left subtree of the root
//Runtime O(1)
struct tree *getLeft(struct tree *root)
{
	assert (root != NULL);
	return root->left;
}

//Function to return the data in the right subtree of the root
//Runtime O(1)
struct tree *getRight(struct tree *root)
{
	assert (root != NULL);
	return root->right;
}

//Function to return the parent of the root
//Runtime O(1)
struct tree *getParent(struct tree *root)
{
	assert (root != NULL);
	return root->parent;
}

//Function to update the left subtree of root
//Runtime O(1)
void setLeft(struct tree *root, struct tree *left)
{
	assert (root != NULL);
	if (root->left != NULL)
		root->left->parent = NULL;
	root->left = left;
	if (left != NULL)
	{
		detatch(left);
		left->parent = root;
	}
}

//Function to update the right subtree of root
//Runtime O(1)
void setRight(struct tree *root, struct tree *right)
{
	assert (root != NULL);
	if (root->right != NULL)
		root->right->parent = NULL;
	root->right = right;
	if (right != NULL)
	{
		detatch(right);
		right->parent = root;
	}
}
