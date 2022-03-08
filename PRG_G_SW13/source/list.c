/**
 * \file
 * \brief Implementation module for lists
 * \author Erich Styger, erich.styger@hslu.ch
 *
 * This module implements a simple linked list
 */

#include "list.h"
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

List List_new(int data) {
	List x = malloc(sizeof(struct list));
	// malloc check
	if(x == NULL){
		printf("Could not aquire memory, malloc returned NULL.");
		return NULL;
	}
	x->head = data;
	x->tail =  NULL;
	return x;
}

int List_head(List element) {
	return element->head;
}

List List_tail(List list) {
	return list->tail;
}

List List_add(List element, List list) {
	element->tail = list;
	return element;
}

bool List_isEmpty(List list) {
	return list==NULL;
}

void List_delete(List list) {
	if (!List_isEmpty(list->tail)) {
		List_delete(list->tail);
	}
	free(list);
}

int List_length(List list) {
	int count = 0;
	List currentList = list;

	while(true){
		if(List_isEmpty(currentList)){
			break;
		} else{
			currentList = list->tail;
			count++;
		}
	}

	return count;
}

List List_concat(List x, List y) {
	if (List_isEmpty(x)) {
		return y;
	} else if (List_isEmpty(x->tail)) {
		x->tail = y;
		return x;
	}
	x->tail = List_concat(x->tail, y);
	return x;
}

List List_reverse(List x) {
	List y;

	if (List_isEmpty(x) || List_isEmpty(x->tail)) {
		return x;
	}
	y = x->tail;
	x->tail = NULL; /* cut list into two lists */
	return List_concat(List_reverse(y), x);
}

List List_map(List_Fun f, List x) {
	if (List_isEmpty(x)) {
		return NULL;
	}
	x->head = f(x->head);
	x->tail = List_map(f, x->tail);
	return x;
}

List List_remove(List element, List list) {
	List previousListElement = list;
	List currentListElement = list;
	while(true){
		if(List_isEmpty(currentListElement)){
			break; // not found => return just the existing list
		}
		// compare current element
		if(currentListElement == element){
			previousListElement->tail = currentListElement->tail;  // change tail
			free(currentListElement);  // free memory
			break;  // exit while
		} else{
			previousListElement = currentListElement;       // update previous List element
			currentListElement = currentListElement->tail;  // set next element
		}
	}
	return list;
}

// Print list
// Example: < 3 2 1 >
void List_print(List list){
	printf("< ");
	while(list != NULL){
		printf("%d ", list->head);
		list = list->tail;
	}
	printf(">\n");
}

// Print list recursive:
// Example: 3 2 1
void List_printr(List list){
	if(list == NULL){
		// last element reached => cancel
		return;
	}
	printf(" %d ", list->head);
	List_printr(list->tail);
}

