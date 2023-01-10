#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#define MAX 32


struct stablo;
typedef struct stablo* position;

typedef struct stablo {
    int vrijednost;
    position l;
    position d;
}stablo;

//a)funkcija insert za brojeve 2, 5, 7, 8, 11, 1, 4, 2, 3, 7 spremljene u cvorove binarnog stabla

// 2 je root, livo veci(ili jednaki), desno manji(1)

//b)funckija replace koja mijenja svaki element stabla sa sumom elemenata u njegovom
//lijevom i desnom podstablu

//c)10 slucajnih brojeva u rasponu <10,90> te brojeve iz a) i b) u inorder prolasku zapisati u datoteku


position insert(position root, int vrijednost);
position noviCvor(int vrijednost);
int print(position root);
int replace(position root);
int slucajniBroj(int min, int max);
int upisiStablo(position root);
int inorder(FILE* fp, position root);

int main()
{


    //a)

    position root = NULL;
    root = insert(root, slucajniBroj(10, 90));
    root = insert(root, slucajniBroj(10, 90));
    root = insert(root, slucajniBroj(10, 90));
    root = insert(root, slucajniBroj(10, 90));
    root = insert(root, slucajniBroj(10, 90));
    root = insert(root, slucajniBroj(10, 90));
    root = insert(root, slucajniBroj(10, 90));
    root = insert(root, slucajniBroj(10, 90));
    root = insert(root, slucajniBroj(10, 90));
    root = insert(root, slucajniBroj(10, 90));
    FILE* fp1 = fopen("file1.txt", "w");
    inorder(fp1, root);
    fclose(fp1);






    //b)

    replace(root);
    FILE* fp2 = fopen("file2.txt", "w");
    inorder(fp2, root);
    fclose(fp2);





    return 0;
}



position insert(position root, int vrijednost)
{
    if (root == NULL) {
        return noviCvor(vrijednost);
    }
    if (root->vrijednost < vrijednost || root->vrijednost == vrijednost) {
        root->l = insert(root->l, vrijednost);
    }
    if (root->vrijednost > vrijednost) {
        root->d = insert(root->d, vrijednost);
    }

    return root;
}


position noviCvor(int vrijednost)
{
    position novi = NULL;
    novi = (position)malloc(sizeof(stablo));
    if (!novi) {
        printf("Greška alokacije!\n");
    }
    novi->vrijednost = vrijednost;
    novi->l = NULL;
    novi->d = NULL;
    return novi;
}

int print(position root)
{
    if (root == NULL) {
        return 1;
    }

    if (root != NULL) {
        printf("%d \n", root->vrijednost);
        print(root->l);
        print(root->d);
    }

    return 0;
}

int replace(position root)
{
    if (root == NULL) {
        return 0;
    }

    int stara_vrijednost = root->vrijednost;
    int nova_vrijednost = replace(root->l) + replace(root->d);
    root->vrijednost = nova_vrijednost;

    return nova_vrijednost + stara_vrijednost;
}

//c)

int slucajniBroj(int min, int max)
{
    int num = (rand() % (max - min + 1)) + min;

    return num;

}
/*
int upisiStablo(position root)
{
    FILE* fp = NULL;
   char filename[MAX] = {0};
    printf("Ime datoteke:\n");
    scanf("%s", filename);

    fp = fopen("file", "w");
    inorder(fp, root);

    fclose(fp);
    return 0;
}
*/
int inorder(FILE* fp, position root)
{
    if (root != NULL) {
        inorder(fp, root->l);
        fprintf(fp, "%d \n", root->vrijednost);
        inorder(fp, root->d);
    }
    return 0;
}