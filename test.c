#include "buddy_system.h"


int main()
{
	struct Node * tempNode1, *tempNode2, *tempNode3;
	int size = 10;
	struct HeadNode * tempHead = buddy_new(size);
	if (tempHead!=NULL)
	{
		//注意申请的空间最大不是2^k, 而是2^k - 1
		tempNode1 = buddy_alloc(tempHead,size,511);
		buddy_print(tempHead, size);
		tempNode2 = buddy_alloc(tempHead,size,10);
		buddy_print(tempHead, size);
		tempNode3 = buddy_alloc(tempHead,size,10);
		buddy_print(tempHead, size);
		buddy_combine(tempHead, size, tempNode3);
		buddy_print(tempHead, size);
		buddy_combine(tempHead, size, tempNode2);
		buddy_print(tempHead, size);
		buddy_combine(tempHead, size, tempNode1);
		buddy_print(tempHead, size);
	}
	buddy_free(tempHead);
	getchar();
	return 0;
}