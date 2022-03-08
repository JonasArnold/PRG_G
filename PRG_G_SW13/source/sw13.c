
#include <stdio.h>

#include "uCUnit-v1.0.h"

#include "list.h"
#include "tree.h"

static void TreeTestCase(void);
static void ListTestCase(void);


int main(void) {

	init();

	UCUNIT_Init(); /* initialize test framework */

	ListTestCase();
	TreeTestCase();

	UCUNIT_WriteSummary();
	UCUNIT_Shutdown();
	return 0;

}

static void ListTestCase(void) {
	List x, y, one, two, three;

	UCUNIT_TestcaseBegin("list tests"); /* open test case */

	UCUNIT_CheckIsNull(List_remove(NULL, NULL));
	UCUNIT_CheckIsNull(List_remove(x, NULL));
	UCUNIT_CheckIsEqual(List_remove(NULL, x), x);

	y = List_new(20);
	UCUNIT_CheckIsNull(List_remove(y, y));

	x = List_add(one=List_new(1), List_add(two=List_new(2), three=List_new(3)));
	y = List_new(20);
	UCUNIT_CheckIsEqual(List_remove(y, x), x); /* should not be found */
	List_delete(y); /* free list */

	// FALSE TEST UCUNIT_CheckIsEqual(x=List_remove(one, x), two);
	UCUNIT_CheckIsEqual(x=List_remove(one, x), List_add(two=List_new(2), three=List_new(3)));
	UCUNIT_CheckIsEqual(x=List_remove(two, x), three);
	UCUNIT_CheckIsEqual(x=List_remove(three, x), NULL);

	x = List_add(one=List_new(1), List_add(two=List_new(2), three=List_new(3)));
	UCUNIT_CheckIsEqual(List_length(x), 3);
	UCUNIT_CheckIsEqual(x=List_remove(three, x), x);
	UCUNIT_CheckIsEqual(List_length(x), 2);
	UCUNIT_CheckIsEqual(x=List_remove(two, x), x);
	UCUNIT_CheckIsEqual(List_length(x), 1);
	UCUNIT_CheckIsEqual(x=List_remove(one, x), NULL);
	UCUNIT_CheckIsEqual(List_length(x), 0);

	x = List_add(one=List_new(1), List_add(two=List_new(2), three=List_new(3)));
	UCUNIT_CheckIsEqual(List_length(x), 3);
	UCUNIT_CheckIsEqual(x=List_remove(two, x), x);
	UCUNIT_CheckIsEqual(List_length(x), 2);
	UCUNIT_CheckIsEqual(x=List_remove(one, x), three);
	UCUNIT_CheckIsEqual(List_length(x), 1);
	UCUNIT_CheckIsEqual(x=List_remove(three, x), NULL);
	UCUNIT_CheckIsEqual(List_length(x), 0);

	UCUNIT_TestcaseEnd(); /* close test case */
}

static void TreeTestCase(void) {
	Tree t, n6, n5, n8, n12, n17;

	UCUNIT_TestcaseBegin("tree tests"); /* open test case */

	t = Tree_add(n6=Tree_new(6), n5=Tree_new(5), n8=Tree_new(8));
	t = Tree_add(n12=Tree_new(12), t, n17=Tree_new(17));

	UCUNIT_CheckIsEqual(Tree_smallest(t), 5);
	UCUNIT_CheckIsEqual(Tree_greatest(t), 17);

	UCUNIT_CheckIsEqual(Tree_greatest(t), 17);

	UCUNIT_CheckIsEqual(Tree_find(t, 100), NULL);
	UCUNIT_CheckIsEqual(Tree_find(t, 5), n5);
	UCUNIT_CheckIsEqual(Tree_find(t, 6), n6);
	UCUNIT_CheckIsEqual(Tree_find(t, 8), n8);
	UCUNIT_CheckIsEqual(Tree_find(t, 12), n12);
	UCUNIT_CheckIsEqual(Tree_find(t, 17), n17);

	UCUNIT_TestcaseEnd(); /* close test case */
}
