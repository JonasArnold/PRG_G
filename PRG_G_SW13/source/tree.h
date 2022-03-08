/**
 * \file
 * \brief Interface for trees
 * \author Erich Styger, erich.styger@hslu.ch
 *
 * This module implements a simple binary tree
 */

#ifndef TREE_H_
#define TREE_H_

#include <stdbool.h>

/*! type for tree node */
typedef struct tree {
	int head;			/*!< node value */
	struct tree *left; 	/*!< left subtree */
	struct tree *right; /*!< right subtree */
} *Tree;

/*!
 * \brief Creates a new tree node
 * \param val New value for head
 * \return new node created
 */
Tree Tree_new(int val);

/*!
 * \brief Adds left and right trees to a tree node
 * \param n node where to add left and right
 * \param l left tree part
 * \param r right tree part
 * \return new tree
 */
Tree Tree_add(Tree n, Tree l, Tree r);

/*!
 * \brief decides if a tree is empty
 * \param t tree to check
 * \return true if tree is empty, false otherwise
 */
bool Tree_isEmpty(Tree t);

/*!
 * \brief Returns the smallest number in a tree
 * \param t tree for the search
 * \return value of smallest tree node
 */
int Tree_smallest(Tree t);

/*!
 * \brief Returns the greatest number in a tree
 * \param t tree for the search
 * \return value of smallest tree node
 */
int Tree_greatest(Tree t);

/*!
 * \brief Inserts a tree element into a tree
 * \param node New element to insert
 * \param tree Existing tree where to insert the element
 * \return The new tree with the element inserted
 */
Tree Tree_insert(Tree node, Tree tree);

/*!
 * \brief Finds an element in a tree
 * \param t Tree where to search
 * \param value Value to find
 * \return Element found, or NULL if not found
 */
Tree Tree_find(Tree t, int value);

/*!
 * \brief Returns the greatest number in a tree
 * \param t tree for the search
 * \return value of smallest tree node
 */
int Tree_greatest(Tree t);

/*!
 * \brief Finds an element in a tree
 * \param t Tree where to search
 * \param value Value to find
 * \return Element found, or NULL if not found
 */
Tree Tree_find(Tree t, int value);

#endif /* TREE_H_ */
