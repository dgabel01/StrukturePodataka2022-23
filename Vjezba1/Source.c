#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_SIZE (128)
#define MAX_LINE (1024)

typedef struct _student {
	char ime[MAX_SIZE];
	char prezime[MAX_SIZE];
	double bodovi;
}student;

int ProcitajRetke(char* nazivDatoteke);
student* AlocirajMemorijuProcitajDatoteku(int brojStudenata, char* nazivDatoteke);


int main()
{
	int i = 0, brojStudenata = 0;
	double relativnibodovi = 0, maxbodovi = 0;
	student* studenti = NULL;
	char ImeDatoteke[MAX_SIZE] = { 0 };
	char txt[] = ".txt";
	

	printf("Unesite ime datoteke: \n");                 
	scanf(" %s", ImeDatoteke);

	strcat(ImeDatoteke, txt);
	

	
	brojStudenata = ProcitajRetke(ImeDatoteke);

	studenti = AlocirajMemorijuProcitajDatoteku(brojStudenata, ImeDatoteke);

	for (i = 0; i < brojStudenata; i++ ) {
		maxbodovi += studenti[i].bodovi;
	}

	for (i = 0; i < brojStudenata; i++) {
		relativnibodovi = 0;
		relativnibodovi = (studenti[i].bodovi / maxbodovi) * 100;
		printf("%s %s %lf %lf \n", studenti[i].ime, studenti[i].prezime, studenti[i].bodovi, relativnibodovi);
	}

	return 0;
}


int ProcitajRetke(char* nazivDatoteke)
{
	char buffer[MAX_SIZE] = { 0 };
	FILE* datoteka = NULL;
	int brojac = 0;

	datoteka = fopen(nazivDatoteke, "r");
	if (!datoteka) {
		printf("Greska pri otvaranju datoteke!\n");
		return -1;
	}

	while (!feof(datoteka))
	{
		fgets(buffer, MAX_LINE, datoteka);
		brojac++;
	}
	fclose(datoteka);

	return brojac;
}

student* AlocirajMemorijuProcitajDatoteku(int brojStudenata, char* nazivDatoteke)
{
	student* studenti = NULL;
	FILE* datoteka = NULL;
	int brojac = 0;

	 studenti = (student*)malloc(brojStudenata * sizeof(student));

	datoteka = fopen(nazivDatoteke, "r");
	if (!datoteka) {
		printf("Greska u otvaranju datoteke!\n");
			return -2;
	}

	while (!feof(datoteka))
	{
		fscanf(datoteka, "%s %s %lf", studenti[brojac].ime, studenti[brojac].prezime, &studenti[brojac].bodovi);
		brojac++;
	}
	
	fclose(datoteka);
	return studenti;
}


