
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct list
{
  char *data; 
  struct list *next; 
  struct list *prev; 
};

char* Make_str(void)
{
	unsigned basis=4;
	unsigned size=0;
	unsigned i=0;
	char c;
	char* str;
	str = (char*)malloc(size+=basis);
	while ((c=getchar())!='\n')
	{
		str[i++]=c;
		if (i==size)
			str = (char*)realloc(str, size+=basis);
	}
	str[i] = '\0';
	return str;
}

struct list* Add_element(struct list *Lst, char* str)
{
	struct list *x;
	if ((Lst)==NULL)
	{
		Lst = (struct list*)malloc(sizeof(struct list));
		Lst->data = malloc(strlen(str)+1);
		strcpy(Lst->data, str);
		Lst->next = NULL;
		Lst->prev = NULL;
		return(Lst);
	}
	else
	{
		x = (struct list*)malloc(sizeof(struct list));
		x->data = malloc(strlen(str)+1);
		strcpy(x->data, str);
		x->prev = Lst;
		x->next = Lst->next;
		Lst->next = x;
		if (x->next!= NULL)
			x->next->prev = x;
		return(x);
	}	
}

struct list* Make_list_add_element(struct list *Lst)
{
	struct list *x;
	struct list *head=Lst;
	if ((Lst)==NULL)
	{
		Lst = (struct list*)malloc(sizeof(struct list));
		Lst->data = Make_str();
		Lst->next = NULL;
		Lst->prev = NULL;
		return(Lst);
	}
	else
	{
		while (Lst->next!=NULL)
		{
			Lst=Lst->next;
		}
		x = (struct list*)malloc(sizeof(struct list));
		x->data = Make_str();
		x->prev = Lst;
		x->next = Lst->next;
		Lst->next = x;
		if (x->next!= NULL)
			x->next->prev = x;
		return(head);
	}
}

struct list* Make_list(struct list *Lst, int n)
{
	char *str;
	for(int i=0;i<n;i++)
	{
		Lst=Make_list_add_element(Lst);
	}
	return Lst;
}

void Print_list(struct list *Lst)
{
	printf("Элементы списка: ");
	while (Lst!=NULL)
	{
		printf("%s  ", Lst->data);
		Lst=Lst->next;
	}
	printf("\n");
}

struct list* Delete_elem(struct list *Lst)
{
	struct list *pred, *post;
	pred = Lst->prev;
	post = Lst->next;
	if (pred != NULL)
		pred->next = Lst->next; 
	if (post != NULL)
		post->prev = Lst->prev; 
	if (pred==NULL)
	{
		free(Lst->data);
		free(Lst);
		return(post);
	}
	free(Lst->data);
	free(Lst);
	return(pred);
}

void Delete_list(struct list *Lst)
{
	struct list *x;
	while (Lst!=NULL)
		{
			x=Lst;
			Lst=Lst->next;
			free(x->data);
			free(x);
		}
	return;
} 

int Search(struct list *Lst,  char *str)
{
	while (Lst!=NULL)
	{
		if (!strcmp(Lst->data,str))
			return 1;
		Lst=Lst->next;
	}
	return 0;
}
struct list* L1_and_reverse_L2(struct list *L1, struct list **L2)
{
	struct list *L1_copy;
	L1_copy=L1;
	struct list *L2_copy;
	L2_copy=(*L2);
	if ((*L2)==NULL)
	{
		return (L1);
	}
	while (L2_copy->next!=NULL)
	{
		L2_copy=L2_copy->next;
	}
	if (L1_copy!=NULL)
	{
		while (L1_copy->next!=NULL)
		{
			L1_copy=L1_copy->next;
		}
	}
	while (L2_copy!=NULL)
	{
		if (L1==NULL)
		{
			L1=Add_element(L1, L2_copy->data);
			L1_copy=L1;
		}
		else
		{
			L1_copy=Add_element(L1_copy, L2_copy->data);
		}
		L2_copy=L2_copy->prev;
	}
	Delete_list(*L2);
	(*L2)=NULL;
	return (L1);
}

struct list* Search_and_delete_repition(struct list *Lst) 
{
	struct list *Lst_copy;
	Lst_copy=Lst;
	while (Lst_copy!=NULL)
	{
		if (Search(Lst_copy->next,Lst_copy->data))
		{
			struct list *Lst_help;
			Lst_help=Lst_copy->next;
			while (Lst_help!=NULL)
			{
				if (!strcmp(Lst_help->data,Lst_copy->data))
				{
					Lst_help=Delete_elem(Lst_help);
				}
				Lst_help=Lst_help->next;
			}
		}
		Lst_copy=Lst_copy->next;
	}
	return(Lst);
}

int main()
{	struct list *L1, *L2;
	int N, M;
	L1=NULL;
    printf("Количество элементов в первом списке: ");
	scanf("%d", &N);
	getchar();
	L1=Make_list(L1, N);
	printf("Cписок №1: ");
	Print_list(L1);
	L2=NULL;
	printf("Количество элементов во втором списке: ");
	scanf("%d", &M);
	getchar();
	L2=Make_list(L2, M);
	printf("Список №2: ");
	Print_list(L2);
	L1=L1_and_reverse_L2(L1,&L2);
	printf("Список №1 после вызова функции соедниения списков: ");
	Print_list(L1);
	L1=Search_and_delete_repition(L1);
	printf("Список после вызова функции удаления повторений: ");
	Print_list(L1);
	Delete_list(L1);
	Delete_list(L2);
	return 0;
}
