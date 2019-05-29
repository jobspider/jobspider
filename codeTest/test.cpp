#include"pch.h"
#include"test.h"
#include <iostream>



//add two number
struct ListNode*addTwoNumbers(struct ListNode*l1, struct ListNode*l2)
{
	int a = 0;
	struct ListNode *l3 = (struct ListNode *)malloc(10 * sizeof(struct ListNode));
	l1 = l1->next;
	l2 = l2->next;
	while (l1 != NULL && l2 != NULL) {
		if (l1 == NULL)
			l3->val = l2->val + a;
		else if (l2 == NULL)
			l3->val = l2->val + a;
		else {
			int temp = l1->val + l2->val + a;
			a = 0;
			if (temp >= 10)
			{
				l3->val = temp % 10;
				a++;
			}
			else
				l3->val = temp;
		}
		l1 = l1->next;
		l2 = l2->next;


	}
	return l3;


}