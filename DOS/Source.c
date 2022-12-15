#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 64

struct _Tree;
typedef struct _Tree* position;

typedef struct _Tree {
	char* name[MAX];
	position parent;
	position firstChild;
	position nextSibling;

}Tree;



// md,cd dir,cd..,dir,exit
//funkcije:

position createNode(char* name, position parent);
int addChild(position parent, position child);
int createDirectory(char* name, position parent);
int printTree(position node, int depth);
position cd(char* dir, position current);


int main()
{
	position root = createNode("C", NULL);
	position current = malloc(sizeof(Tree));
	current = root;
	char ime[MAX]={0};


	int izbor = 0;

	while (1) {
		printf("Izbornik:\n");
		printf("1-md:\n");
		printf("2-cd dir\n");
		printf("3-dir\n");
		printf("4-izlaz\n");
		scanf("%d", &izbor);
		switch (izbor) {
		case 1:
			printf("Ime direktorija:\n");
			scanf("%s", ime);
			createDirectory(ime,current);
			break;
	
		case 2:
			printf("Ime direktorija:\n");
			scanf("%s", ime);
			cd(ime, current);
			break;

		case 3:
			printf("Ime direktorija:\n");
			printTree(current, 0);
			break;

		case 4:
			exit(1);
			break;

		default:
			printf("Krivi unos.\n");
			break;
		}



	}

	return 0;
}



position createNode(char* name, position parent)
{
	position node = malloc(sizeof(Tree));
	if (!node) {
		printf("Greska pri alokaciji!\n");
		exit(-1);
	}
	strcpy(node->name, name);
	node->parent = parent;
	node->firstChild = NULL;
	node->nextSibling = NULL;

	return node;

}


int addChild(position parent, position child)
{
	//ako parent nema dijete
	if (parent->firstChild == NULL) {
		parent->firstChild = child;
	}

	//ako ima,dodaj dijete kao next sibling parentovog last childa
	else {
		position lastChild = parent->firstChild;
		while (lastChild->nextSibling != NULL) {
			lastChild = lastChild->nextSibling;
		}
		lastChild->nextSibling = child;
	}


	return 0;
}



//md-stvori direktorij
int createDirectory(char* name, position parent)
{
	position directory = createNode(name, parent);
	addChild(parent, directory);

	return 0;
}


//dir-ispisi sadrzaj danog direktorija

int printTree(position node, int depth)
{
	printf("%*s%s\n", depth * 2, "", node->name);

	position child = node->firstChild;
	while (child != NULL) {
		printTree(child, depth + 1);
		child = child->nextSibling;
	}

	return 0;
}


//cd dir-promijeni direktorij   cd.. vrati parent 


position cd(char* dir, position current)
{
	//ako je unos ..
	if (strcmp(dir, "..") == 0) {
		return current->parent;
	}

	//vidi je li postoji taj dir



	//ako nije, trai ga u djeci trenutnog
	position child = current->firstChild;
	while (child != NULL) {
		if (strcmp(child->name, dir) == 0) {
			return child;
		}
		child = child->nextSibling;
	}

	return current;
}

