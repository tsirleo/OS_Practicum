#include <stdio.h>
#include <stdlib.h>

struct list
{
	int data;
	struct list *next;
};

struct tree
{
	int data;
	struct tree *left;
	struct tree *right;
};

struct list* Make_list(struct list *Lst, int n)
{
	struct list *Lst_copy=NULL, *Lst_cur;
	int x;
	for(int i=0;i<n;i++)
	{
		scanf("%d", &x);
		Lst_cur=(struct list*)malloc(sizeof(struct list));
		Lst_cur->data=x;
		Lst_cur->next=NULL;
		if (Lst_copy!=NULL)
		{
			Lst_copy->next=Lst_cur;
			Lst_copy=Lst_copy->next;
		}
		else
		{
			Lst=Lst_copy=Lst_cur;
		}
	}
	return (Lst);
}

void Delete_list(struct list *Lst)
{
	while(Lst!=NULL)
	{
		struct list *Lst_copy=Lst;
		Lst=Lst->next;
		free(Lst_copy);
	}
}

void Add_element_in_tree(struct tree **Tr, int x)
{
	if ((*Tr)==NULL)
	{
		(*Tr)=(struct tree*)malloc(sizeof(struct tree));
		(*Tr)->data=x;
		(*Tr)->left=NULL;
		(*Tr)->right=NULL;
	}
	else if (x < (*Tr)->data)
		Add_element_in_tree(&(*Tr)->left,x);
	else if (x > (*Tr)->data)
		Add_element_in_tree(&(*Tr)->right,x);
	else
		return;
}

void Print_tree(struct tree *Tr)
{	
	if (Tr==NULL)
		return;
	Print_tree(Tr->left);
	printf("%d ", Tr->data);
	Print_tree(Tr->right);
}

void Delete_tree(struct tree *Tr)
{
	if (Tr!=NULL)
	{
		Delete_tree(Tr->left);
		Delete_tree(Tr->right);
		free(Tr);
	}
	return;
}

int main()
{
	struct list *Lst=NULL, *Lst_copy=Lst;
	struct tree *Tr=NULL;
	int N;
	printf("Количество элементов в cписке: ");
	scanf("%d", &N);
	getchar();
	Lst=Make_list(Lst, N);
	Lst_copy=Lst;
	while (Lst_copy!=NULL)
	{
		Add_element_in_tree(&Tr, Lst_copy->data);
		Lst_copy=Lst_copy->next;
	}
	Print_tree(Tr);
	printf("\n");
	Delete_list(Lst);
	Delete_tree(Tr);
	return 0;
}
