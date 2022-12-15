#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 32

typedef struct node* Directory;
typedef struct stog* Position;

struct node {
	char name[MAX];
	Directory sibling;
	Directory child;
};

struct stog {
	Directory data;
	Position next;
};

Directory createNewTree();
Position createNode();
int mkdir(Directory S, char ime[]);
int dir(Directory S);
int Push(Directory S, Position P);
Directory Pop(Position P);
Directory cddir(Directory S, Position P, char ime[]);

int main()
{
	Directory root;
	Directory current;
	root = createNewTree();
	current = createNewTree();
	current = root;
	int x;
	char temp[MAX];
	Position head;
	head = createNode();
	strcpy(root->name, "root");

	while (1)
	{
		printf("Izbornik:\n");
		printf("1 - md\n");
		printf("2 - cd dir\n");
		printf("3 - cd..\n");
		printf("4 - dir\n");
		printf("5 - izlaz\n");
		printf("\nIzbor:\n\n");
		scanf(" %d", &x);

		switch (x)
		{
		case 1:
			printf("Unesite ime direktorija:\n");
			scanf(" %s", temp);
			mkdir(current, temp);
			break;
		case 2:
			printf("Unesite ime direktorija:\n");
			scanf(" %s", temp);
			current = cddir(current, head, temp);
			break;
		case 3:
			current = Pop(head);
			break;
		case 4:
			dir(current);
			break;
		case 5:
			printf("Kraj.\n");
			return 1;
			break;

		default:
			printf("Krivi unos!\n");
			break;
		}
	}

	return 0;
}

Directory createNewTree()
{
	Directory temp = NULL;
	temp = (Directory)malloc(sizeof(struct node));
	temp->child = NULL;
	temp->sibling = NULL;
	strcpy(temp->name, " ");

	if (!temp)
	{
		printf("Greska pri alokaciji memorije.\n");
		return -1;
	}

	return temp;
}

Position createNode()
{
	Position temp = NULL;
	temp = (Position)malloc(sizeof(struct stog));
	temp->next = NULL;
	temp->data = NULL;

	if (!temp)
	{
		printf("Greska pri alokaciji memorije.\n");
		return -1;
	}

	return temp;
}

int mkdir(Directory S, char ime[])
{
	Directory novi = createNode();
	strcpy(novi->name, ime);
	if (S->child == NULL)
		S->child = novi;
	else
	{
		S = S->child;
		if (S->sibling == NULL)
		{
			S->sibling = novi;
		}
		else
		{
			while (S->sibling != NULL)
			{
				S = S->sibling;
			}
			S->sibling = novi;
		}
	}
	return 0;
}

int dir(Directory S)
{
	if (S->child == NULL)
	{
		printf("Prazan direktorij.\n");
	}
	else
	{
		if (S->child->sibling == NULL)
		{
			printf("%s\n", S->child->name);
		}
		else
		{
			S = S->child;
			while (S->sibling != NULL)
			{
				printf("%s\n", S->name);
				S = S->sibling;
			}
			printf("%s\n", S->name);
		}
	}
	return 0;
}

int Push(Directory S, Position P)
{
	Position novi = NULL;

	if (P->next == NULL)
	{
		novi = createNode();
		novi->data = S;
		P->next = novi;
	}
	else
	{
		while (P->next != NULL)
		{
			P = P->next;
		}

		novi = createNode();
		novi->data = S;
		P->next = novi;
	}
	return 0;
}

Directory Pop(Position P)
{
	Directory x;
	Position temp;

	while (P->next->next != NULL)
	{
		P = P->next;
	}
	x = P->next->data;
	temp = P->next;
	P->next = temp->next;
	free(temp);

	return x;
}

Directory cddir(Directory S, Position P, char ime[])
{
	Push(S, P);
	Directory glavni = S;

	if (S->child == NULL)
	{
		printf("Prazan direktorij\n");
	}
	else
	{
		S = S->child;
		while (S->sibling != NULL)
		{
			if (!(strcmp(S->name, ime)))
			{
				return S;
			}
			S = S->sibling;
		}

		if (!(strcmp(S->name, ime)))
		{
			printf("Trenutni direktorij: %s\n", ime);
			return S;
		}
		else
		{
			printf("Direktorij ne postoji.\n");
			return glavni;
		}
	}
}