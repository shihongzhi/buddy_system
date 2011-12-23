#include "buddy_system.h"

//¿¿
//Node      :  ¿¿¿¿¿¿¿¿
//HeadNode  :  ¿¿¿¿¿
//avail     :  ¿¿¿¿¿¿¿¿
//size      :  ¿¿¿¿¿¿¿¿¿¿2^size



//sizeof(Node) = 16
struct Node{
	int tag;               //0:unused  1:used
	int kval;              //0~size
	struct Node * llink;   //point to left Node  
	struct Node * rlink;   //point to right Node
};

struct HeadNode{
	int nodesize;          //1<<size
	struct Node * first;   //point to Node
};

//¿¿¿¿¿¿¿¿
struct Node * node_start;  

//¿¿¿¿
struct HeadNode * buddy_new(int size)
{
	int i;
	struct Node * node_self;
	struct HeadNode * head_self = malloc(sizeof(struct HeadNode)*(size+1));
	for (i=0; i<=size; ++i)
	{
		head_self[i].nodesize = (1<<i);
		head_self[i].first = NULL;
	}

	node_self = head_self[size].first = malloc((1<<size) * sizeof(struct Node));
	node_start = node_self;  //
	if (head_self!=NULL && head_self[size].first!=NULL)
	{
		node_self->llink = node_self->rlink = node_self;
		node_self->tag = 0;
		node_self->kval = size;
		return head_self;
	}
	return NULL;
}

//¿¿¿¿
//n  ¿¿¿¿¿¿¿¿¿
struct Node * buddy_alloc(struct HeadNode * avail, int size, int n){
	struct Node * pa, * pi, * pre, * suc;
	int k, i;
    //¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿
	for (k=0; k<=size&&(avail[k].nodesize<n+1||!avail[k].first); ++k);

    //¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿
	if (k > size)
		return NULL;
	else{
		pa = avail[k].first;
		pre = pa->llink;
		suc = pa->rlink;
		if (pa == suc)                                 //¿¿¿¿¿¿
			avail[k].first = NULL;
		else{
			pre->rlink = suc;
			suc->llink = pre;
			avail[k].first = suc;
		}
		for (i=1; avail[k-i].nodesize>=n+1; ++i)
		{
			pi = pa + (1<<(k-i));
			pi->rlink = pi->llink = pi;
			pi->tag = 0;
			pi->kval = k-i;
			avail[k-i].first = pi;
		}
		pa->tag = 1;
		pa->kval = k - (--i);
	}
	return pa;
}

//¿¿buddy Node
struct Node * buddy(struct Node * p){
    //p¿¿¿¿¿
	if((p-node_start)%(1<<(p->kval+1)) == 0)
		p = p + (1<<p->kval);
	else  //p¿¿¿¿¿
		p = p - (1<<p->kval);
	return p;
}

//¿¿p¿¿¿¿¿¿¿
void buddy_combine(struct HeadNode * avail, int size, struct Node * p){
	struct Node * buddy_node = NULL;
	//¿¿Node
	buddy_node = buddy(p);

	//buddy_node¿¿¿¿¿¿¿ ¿¿tag==0
	while (buddy_node>=node_start && buddy_node<node_start+(1<<size) && buddy_node->tag==0)
	{
        //¿¿¿¿¿¿
		if (buddy_node->llink == buddy_node && buddy_node->rlink == buddy_node)
			avail[buddy_node->kval].first = NULL;
		else
		{
			buddy_node->llink->rlink = buddy_node->rlink;
			buddy_node->rlink->llink = buddy_node->llink;
			if (avail[buddy_node->kval].first == buddy_node)    //¿¿¿¿
				avail[buddy_node->kval].first = buddy_node->rlink;
		}

		if ((p-node_start)%(1<<(p->kval+1)) == 0)                 //p¿¿¿¿¿
		{
			p->kval++;
		}
		else                                                    //p¿¿¿¿¿
		{
			buddy_node->kval++;
			p = buddy_node;
		}
		buddy_node = buddy(p);
	}
	p->tag = 0;
	if (avail[p->kval].first == NULL)  //¿¿¿¿
	{
		p->llink = p;
		p->rlink = p;
		avail[p->kval].first = p;
	}
	else  //¿¿¿¿¿¿¿¿
	{
		avail[p->kval].first->llink->rlink = p;
		p->llink = avail[p->kval].first->llink;
		avail[p->kval].first->rlink->llink = p;
		p->rlink = avail[p->kval].first->rlink;
		avail[p->kval].first = p;
	}
}


void buddy_free(struct HeadNode * avail)
{
	free(avail);
	free(node_start);
}

void buddy_print(struct HeadNode * avail, int size){
	struct Node * first, *cur;
	int i;
	for (i=0; i<=size; ++i)
	{
		first = avail[i].first;
		printf("avail[%d]: ", i);
		if (first!=NULL)
		{
			printf("%d-%x", 1<<first->kval, first);
			cur = first->rlink;
			while (cur && cur!=first)
			{
				printf(", %d-%x", 1<<cur->kval, cur);
			}
		}
		printf("\n");
	}
}
