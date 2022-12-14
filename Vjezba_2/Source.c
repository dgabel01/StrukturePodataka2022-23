#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>														
#include<string.h>
#include<ctype.h>																												
#define MAX (128)

struct _osoba;
typedef struct _osoba* position;

typedef struct _osoba {
    char ime[MAX];
    char prezime[MAX];
    int godina_rodenja;
    position next;
}osoba;

//Funkcije

int DodajNaPocetak(position p, char* ime, char* prezime, int godina_rodenja); //A
position StvoriOsobu(char* ime, char* prezime, int godina_rodenja); //pomocna
int IspisListe(position p);  //B
int DodajNaKraj(position p, char* ime, char* prezime, int godina_rodenja); //C
position PronadiPrezime(position p, char* prezime); //D
int BrisiOsobu(position p, char* prezime); //E
position PronadiPrethodnog(position p, char* prezime);  //pomocna za E




int main()
{
    osoba head = { .ime = {0}, .prezime = {0}, .godina_rodenja = 0 };
    //za unos
    char izbor = { 0 };
    char imeosobe[MAX] = { 0 };
    char prezimeosobe[MAX] = { 0 };
    int godinaosobe = 0;


    while (1) {
        printf("\nIzbornik:\nP - unos osobe na pocetak liste\nI - ispis liste\nK - unos osobe na kraj liste"
            "\nT - trazenje osobe po prezimenu \nB - brisanje osobe iz liste po prezimenu"
            "\nQ - kraj programa\n\n");
        scanf(" %c", &izbor);

        switch (toupper(izbor)) {
        case 'P':
            puts("Vrsi se unos osobe na pocetak liste.");
            printf("\nUnesite ime osobe.\n");
            scanf(" %s", imeosobe);
            printf("\nUnesite prezime osobe.\n");
            scanf(" %s", prezimeosobe);
            printf("\nUnesite godinu rodenja.\n");
            scanf("%d", &godinaosobe);

            DodajNaPocetak(&head, imeosobe, prezimeosobe, godinaosobe);

            printf("\nUspjesno dodana osoba na  pocetak liste.\n\n");
            break;

        case 'I':
            puts("Vrsi se ispis liste:");
            IspisListe(head.next);
            break;

        case 'K':
            puts("Vrsi se unos osobe na kraj liste:");

            printf("\nUnesite ime .\n");
            scanf(" %s", imeosobe);
            printf("\nUnesite prezime.\n");
            scanf(" %s", prezimeosobe);
            printf("\nUnesite godinu rodenja studenta.\n");
            scanf("%d", &godinaosobe);

            DodajNaKraj(&head, imeosobe, prezimeosobe, godinaosobe);

            printf("\nUspjesno dodana osoba na kraj liste.\n\n");
            break;

        case 'T':
            puts("Vrsi se trazenje studenta po prezimenu:");

            printf("\nUnesite prezime:\n");
            scanf(" %s", prezimeosobe);

            PronadiPrezime(head.next, prezimeosobe);
            break;

        case 'B':
            puts("Vrsi se brisanje studenta iz liste po prezimenu:");

            printf("\nUnesite prezime za brisanje iz liste:\n");
            scanf(" %s", prezimeosobe);

            BrisiOsobu(&head, prezimeosobe);
            break;

        case 'Q':
            puts("Kraj programa!\n");
            return 1;
            break;

        }
    }


    return 0;
}

position StvoriOsobu(char* ime, char* prezime, int godina_rodenja)
{
    position nova = NULL;
    nova = (position)malloc(sizeof(osoba));        //alociraj memoriju
    if (!nova) {
        printf("Gre?ka pri alokaciji!\n");
        return NULL;
    }
    strcpy(nova->ime, ime);                       //postavi vrijednosti
    strcpy(nova->prezime, prezime);
    nova->godina_rodenja = godina_rodenja;
    nova->next = NULL;

    return nova;
}


int DodajNaPocetak(position p, char* ime, char* prezime, int godina_rodenja)   //prima head
{
    position q = NULL;
    q = StvoriOsobu(ime, prezime, godina_rodenja);

    q->next = p->next;       //postavi pokazivace
    p->next = q;
    return 0;
}

int IspisListe(position p)     //prima head.next
{

    if (p == NULL) {
        printf("Prazna lista!\n");

    }
    else
        printf("Ime		 Prezime	Godina rodenja\n");
    while (p != NULL) {
        printf("%-8s\t %-8s\t %8d\n", p->ime, p->prezime, p->godina_rodenja);
        p = p->next;
    }

    return 0;
}

int DodajNaKraj(position p, char* ime, char* prezime, int godina_rodenja)  //prima head
{
    position q = NULL;
    while (p->next != NULL) {      //nadi zadnjeg
        p = p->next;
    }
    q = StvoriOsobu(ime, prezime, godina_rodenja);
    q->next = p->next;
    p->next = q;

    return 0;
}

position PronadiPrezime(position p, char* prezime)  //prima head.next
{
    int br = 1;  //za mjesto u listi

    while (p != NULL && strcmp(p->prezime, prezime)) {	//strcmp = 0 ako jednaki str1,str2					
        p = p->next;
        br++;
    }

    if (p == NULL) {
        printf("\nOsoba prezimena %s se ne nalazi unutar liste.\n", prezime);
        return NULL;
    }
    else {
        printf("\nOsoba %s %s (%d.) se nalazi na %d. mjestu u listi.\n", p->ime, p->prezime, p->godina_rodenja, br);
        return p;
    }
}


int BrisiOsobu(position p, char* prezime)  //prezime onoga koji se brise
{
    position prev = NULL;
    prev = PronadiPrethodnog(p, prezime);

    printf("\nOsoba%s %s (%d.) se izbrisala iz liste.\n", prev->next->ime, prev->next->prezime, prev->next->godina_rodenja);

    if (prev != NULL) {
        p = prev->next;
        prev->next = p->next;
        free(p);
    }

    return 0;
}

position PronadiPrethodnog(position p, char* prezime)
{
    position prev = p;
    p = p->next;

    while (p != NULL && strcmp(p->prezime, prezime)) {				  //pomicanje po listi sa 2 pokazivaca prev i p
        prev = p;
        p = p->next;
    }

    if (p == NULL) {
        printf("\nOsoba prezimena %s se ne nalazi unutar liste.\n", prezime);
        return NULL;
    }

    return prev;
}
