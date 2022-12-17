#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

//binarno stablo - dodaj element, ispis(4), pretrazi, izbrisi 

struct Stablo;
typedef struct Stablo* position;

typedef struct Stablo {
	int vrijednost;
	position lijevo;
	position desno;
}Stablo;


//funkcije

position dodajElement(position root,int vrijednost);
position stvoriNovi(position vrijednost);
int inorder(position root);
int preorder(position root);
int postorder(position root);
position pretrazi(position root, int vrijednost);
position delete(position root, int vrijednost);
position minCvor(position cvor);

//levelorder
int levelorder(position root);
int printCurrentLevel(position root, int level);
int height(position root);



int main()
{
	//dodavanje
	position root = NULL;
	root =dodajElement(root, 50);
	dodajElement(root, 30);
	dodajElement(root, 20);
	dodajElement(root, 5);
	dodajElement(root, 4);
	dodajElement(root, 1);
	dodajElement(root, 2);
	//4 ispisa
	printf("inorder:\n");
	inorder(root);
	printf("\n\n");
	printf("preorder:\n");
	preorder(root);
	printf("\n\n");
	printf("postorder:\n");
	postorder(root);
	printf("\n\n");
	printf("levelorder:\n");
	levelorder(root);
	printf("\n\n");
	//pretraga
	position temp = pretrazi(root, 20);
	printf("%d ", temp->vrijednost);
	printf("\n");
	//brisanje
	root = delete(root, 1);
	root = delete(root, 2);
	preorder(root);
	
	



	return 0;
}


position dodajElement(position root, int vrijednost)
{
	if (!root) {
		return(stvoriNovi(vrijednost));
	}

	if (root->vrijednost > vrijednost) {
		root->lijevo = dodajElement(root->lijevo, vrijednost);
	}

	else {
		if (root->vrijednost < vrijednost) {
			root->desno = dodajElement(root->desno, vrijednost);
		}
	}
	
	return root;
}


position stvoriNovi(int vrijednost)
{

	position novi = malloc(sizeof(Stablo));
	novi->vrijednost = vrijednost;
	novi->lijevo = NULL;
	novi->desno = NULL;

	return novi;

}


int inorder(position root)
{
	if (root == NULL) {
		return;
	}
		inorder(root->lijevo);
		printf("%d ", root->vrijednost);
		inorder(root->desno);

	return 0;
}

int preorder(position root)
{
	if (root == NULL) {
		return;
	}
	printf("%d ", root->vrijednost);
	preorder(root->lijevo);
	preorder(root->desno);
	return 0;

}

int postorder(position root)
{
	if (root ==NULL) {
		return;
	}

	postorder(root->lijevo);
	postorder(root->desno);
	printf("%d ", root->vrijednost);

	return 0;
}

int levelorder(position root)
{
	int h = height(root);
	int i;
	for (i = 1; i <= h; i++)
		printCurrentLevel(root, i);

	return 0;
}


int printCurrentLevel(position root, int level)
{
	if (root == NULL) {
		return;
	}
	if (level == 1) {
		printf("%d ", root->vrijednost);
	}
	else if (level > 1) {
		printCurrentLevel(root->lijevo, level - 1);
		printCurrentLevel(root->desno, level - 1);
	}

	return 0;
}

int height(position root)
{
	if (root == NULL) {
		return 0;
	}
	else {
		/* compute the height of each subtree */
		int lheight = height(root->lijevo);
		int rheight = height(root->desno);

		/* use the larger one */
		if (lheight > rheight)
			return (lheight + 1);
		else
			return (rheight + 1);

		return 0;
	}

}

position pretrazi(position root, int vrijednost)
{
	if (root == NULL || root->vrijednost == vrijednost) {
		return root;
	}

	if (root->vrijednost < vrijednost) {
		return pretrazi(root->desno, vrijednost);
	}

	return pretrazi(root->lijevo, vrijednost);	


}


position delete(position root, int vrijednost)
{
	// base case
	if (root == NULL)
		return root;

	// If the key to be deleted
	// is smaller than the root's
	// key, then it lies in left subtree
	if (vrijednost < root->vrijednost)
		root->lijevo = delete(root->lijevo, vrijednost);

	// If the key to be deleted
	// is greater than the root's
	// key, then it lies in right subtree
	else if (vrijednost > root->vrijednost)
		root->desno= delete(root->desno, vrijednost);

	// if key is same as root's key,
	// then This is the node
	// to be deleted
	else {
		// node with only one child or no child
		if (root->lijevo == NULL) {
			position temp = root->desno;
			free(root);
			return temp;
		}
		else if (root->desno == NULL) {
			position temp = root->lijevo;
			free(root);
			return temp;
		}

		// node with two children:
		// Get the inorder successor
		// (smallest in the right subtree)
		position temp = minCvor(root->desno);

		// Copy the inorder
		// successor's content to this node
		root->vrijednost = temp->vrijednost;

		// Delete the inorder successor
		root->desno = delete(root->desno, temp->vrijednost);
	}
	return root;
}

position minCvor(position cvor)
{

	position current = cvor;

	while (current && current->lijevo != NULL)
		current = current->lijevo;

	return current;

}

