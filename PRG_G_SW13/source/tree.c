/**
 * \file
 * \brief Implementation module for trees
 * \author Erich Styger, erich.styger@hslu.ch
 *
 * This module implements a simple binary tree
 */

#include "tree.h"
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

Tree Tree_new(int val) {
	Tree n = malloc(sizeof(struct tree));
	n->head = val;
	n->left = NULL;
	n->right = NULL;
	return n;
}

Tree Tree_add(Tree n, Tree l, Tree r) {
	n->left = l;
	n->right = r;
	return n;
}

int Tree_smallest(Tree t) {
	if (Tree_isEmpty(t->left)) {
		return t->head;
	}
	return Tree_smallest(t->left);
}

int Tree_greatest(Tree t) {
	if (Tree_isEmpty(t->right)) {
		return t->head;
	}
	return Tree_greatest(t->right);
}

bool Tree_isEmpty(Tree t) {
	return (t == NULL);
}

Tree Tree_find(Tree t, int value) {
	Tree currentTree = t;
	// search direction "right"
	while(true){
		if(currentTree == NULL){
			break;  // not found in this direction
		}
		if(currentTree->head == value){
			return currentTree;
		}else{
			currentTree = currentTree->right;
		}
	}
	currentTree = t; // set back to start element
	// search direction "left"
	while(true){
		if(currentTree == NULL){
			return NULL; // not found in both directions
		}
		if(currentTree->head == value){
			return currentTree;
		}else{
			currentTree = currentTree->left;
		}
	}
}

Tree Tree_insert(Tree node, Tree tree) {
	if (Tree_isEmpty(tree)) {
		return node; /* insert here */
	}
	if (node->head > tree->head) { /* insert on right side */
		return Tree_add(tree, tree->left, Tree_insert(node, tree->right));
	} else { /* insert on left side */
		return Tree_add(tree, Tree_insert(node,tree->left), tree->right);
	}
}

