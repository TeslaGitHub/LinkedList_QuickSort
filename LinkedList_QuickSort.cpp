#include <stdio.h>
#include<stdlib.h>
typedef struct Item Item;
struct Item
{
	int index;
};
typedef struct Node
{
	struct Node* prev;
	Item Item;
	struct Node* next;
}Node;
typedef struct Nodes
{
	Node* start, * end;
}Nodes;

bool cmp(int, int);
Node* QuickSort(Node*);
void QuickSortdp(Nodes);
void output(Node*);
int cmpobj(Node* node) { return node->Item.index; }

int main()
{
	int tmp;
	Node* head = NULL, * cur = NULL;
	while ((tmp = getchar()-'0') != 'z'-'0')
	{
		if (head == NULL)
		{
			head = (Node*)malloc(sizeof(Node));
			head->Item.index = tmp;
			cur = head;
			head->prev = NULL;
		}
		else
		{
			cur->next = (Node*)malloc(sizeof(Node));
			cur->next->prev = cur;
			cur = cur->next;
			cur->Item.index = tmp;
		}
	}
	cur->next = NULL;
	output(head);
	head = QuickSort(head);
	output(head);
}

bool cmp(int x, int y) { return x >= y ? true : false; }

void output(Node* head)
{
	Node* cur = head;
	while (cur)
	{
		printf("%d\n", cmpobj(cur));
		cur = cur->next;
	}
}

void swap(Node* node1, Node* node2)
{
	/*Node* tmp = (Node*)malloc(sizeof(Node));
	*tmp = *node1;
	*node1 = *node2;
	*node2 = *tmp;*/
	if (node1 == node2)
		return;
	Node* tmp;
	if (node1->next == node2)
	{
		tmp = node2->next;
		node1->prev->next = node2;
		node2->prev = node1->prev;
		node2->next = node1;
		node1->prev = node2;
		node1->next = tmp;
		node1->next->prev = node1;
	}
	else
	{
		tmp = node1->next;
		node1->next = node2->next;
		node2->next = tmp; 
		tmp = node1->prev;
		node1->prev = node2->prev;
		node2->prev = tmp;
		node2->prev->next = node1;
		node1->prev->next = node2;
	}
}

Node* QuickSort(Node* head)
{
	Node* ExtraHead = (Node*)malloc(sizeof(Node)), * ExtraTail = (Node*)malloc(sizeof(Node)), * tmp = head;
	Nodes nodes;
	ExtraHead->next = head;
	head->prev = ExtraHead;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = ExtraTail;
	ExtraTail->prev = tmp;
	nodes = { ExtraHead->next,ExtraTail->prev };
	QuickSortdp(nodes);
	ExtraTail->prev->next = NULL;
	return ExtraHead->next;
}
void QuickSortdp(Nodes nodes)
{
	if (nodes.start == nodes.end || nodes.end->next == nodes.start)
		return;
	Node* key = nodes.start, * tmp, * start = nodes.start, * end = nodes.end;
	Nodes nodes_;
	while (true)
	{
		while (cmp(cmpobj(key), cmpobj(start)))
		{
			if (end == start||end->next==start)
				goto next;
			start = start->next;
		}
		while (!cmp(cmpobj(key), cmpobj(end)))
		{
			if (end == start || end->next == start)
				goto next;
			end = end->prev;
		}
		swap(start, end);
		/*tmp = start;
		start = end;
		end = tmp;*/
	}
next:
	swap(key, end);
	nodes_ = { nodes.start,key->prev };
	QuickSortdp(nodes_);
	nodes_ = { key->next,nodes.end };
	QuickSortdp(nodes_);
}