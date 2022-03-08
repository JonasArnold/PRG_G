/**
 * \file
 * \brief Interface for lists
 * \author Erich Styger, erich.styger@hslu.ch
 *
 * This module implements a simple linked list
 */

#ifndef LIST_H_
#define LIST_H_

#include <stdbool.h>

/*!
 * \brief List element and type
 */
typedef struct list {
	int head; /*!< data of list element */
	struct list *tail; /*!< tail of list */
} *List;

/*! Function type to be used for the List_map() function */
typedef int List_Fun(int);

/*!
 * \brief allocates a new list with a single element
 * \param data head value
 * \return new List
 */
List List_new(int data);

/*!
 * \brief Selector which returns the element data
 * \param element Pointer to the element
 * \return element data
 */
int List_head(List element) ;

/*!
 * \brief Selector which returns list tail
 * \param list List used
 * \return pointer to the tail list
 */
List List_tail(List list);

/*!
 * \brief add a new element in front of the list
 * \param element New element (list with only one element) to add
 * \param list existing list, where to add the new element
 * \return the new list
 */
List List_add(List element, List list);

/*!
 * \brief decides if the list is empty or not
 * \param list list to be checked
 * \return true if the list is empty, false otherwise
 */
bool List_isEmpty(List list);

/*!
 * \brief Release the memory for the list
 * \param list Root of list to be deleted
 */
void List_delete(List list);

/*!
 * \brief returns the number of elements in a list
 * \param list list to be used
 * \return number of elements in the list
 */
int List_length(List list);

/*!
 * \brief Concatenates two lists
 * \param x first list
 * \param y second list
 * \return combined list
 */
List List_concat(List x, List y);

/*!
 * \brief Reverses the list members
 * \param x list to be reversed
 * \return reversed list
 */
List List_reverse(List x);

/*!
 * \brief List iterator function
 * \param f function to be called for each member of the list
 * \param x list to be mapped
 * \return mapped list
 */
List List_map(List_Fun f, List x);

/*!
 * \brief Removes and deallocates an element from a list
 * \param element element to remove, must be part of the list
 * \param list list where to remove the element
 * \return new list with the element removed
 */
List List_remove(List element, List list);

#endif /* LIST_H_ */
