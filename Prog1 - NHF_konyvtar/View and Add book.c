#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "konyv.h"
#include "debugmalloc.h"
#pragma warning (disable:4996)

/*We dinamically assign a new array as it is being read from the user
and constantly update it 1 character at a time until it reaches its actual size-
* We use a helping array as we are extending the other and are constantly freeing it.
* Finally, return the dinamically allocated array.
*/
char* dinamikus_tomb()
{
	int db = 0;
	char* tomb = (char*)malloc(sizeof(char) * 1);
	tomb[0] = '\0';
	char ujkar;
	while (scanf("%c", &ujkar) == 1 && ujkar != '\n') {
		char* ujtomb = (char*)malloc(sizeof(char) * (db + 1 + 1));
		for (int i = 0; i < db; ++i)
			ujtomb[i] = tomb[i];
		free(tomb);
		tomb = ujtomb;
		ujtomb[db] = ujkar;
		ujtomb[db + 1] = '\0';
		++db;
	}
	return tomb;
}

void foglal(char*** ptomb, int szeles) {
	char** uj;
	uj = (char**)malloc(100 * (sizeof(char*)));
	int utolso = 0;
	printf("Enter the genre(s): ");
	for (int y = 0; y < szeles; ++y) {
		uj[y] = (char*)malloc(100 * sizeof(char));
		scanf("%s", uj[y]);
		//uj[y][10] = "\0";
	}

	*ptomb = uj; /* *ptomb → a char** típusú változó! */
}

/*Open file in reading mode
* If NULL then there is an error
* Otherwise we read every line using fgets
* and print it on the screen with its row number,
  (Except for the first 2 as thats the header)*/
void view(void)
{
	FILE* fp;
	fp = fopen("Konyvek.txt", "r");
	if (fp == NULL) {
		perror("Unable to open file");
		return;
	}
	printf("[R]: Rented \n[Number]: ID of Renter\n(Num): Row number\n");
	char line[1000];
	int n = num_lines();
	int i = 1;
	int j = 1;
	while (fgets(line, sizeof(line), fp))
	{
		if (i < 3)
		{
			printf("%s", line);
		}
		else
		{
			printf("(%d) %s", j, line);
			j++;
		}
		i++;
	}
	fclose(fp);
}

/*Open file in mode 'a' (writing while perserving old data)
* If NULL then there is an error
* When pressing enter while in main, it triggers the dynamically allocated array
* which is why we need the temp in order to execute the rest
* We dynamically allocate an array and then...*/
void add(int which_line)
{
	FILE* fp1, * fp2;

	char filename[] = "konyvek.txt";
	char temp_filename[] = "temp_konyvek.txt";

	char temp;
	scanf("%c", &temp);

	fp1 = fopen(filename, "r");
	fp2 = fopen(temp_filename, "w");

	if (fp1 == NULL || fp2 == NULL) {
		perror("Unable to open file");
		return;
	}

	char buffer[2000];
	bool keep_reading = true;
	int current_line = 5;
	which_line = which_line + 6;
	do
	{
		fgets(buffer, 2000, fp1);
		// if we've reached the end of the file, stop reading
		if (feof(fp1)) {
			keep_reading = false;
		}
		// if the line we've reached is the one we wish to replace, write the 
		// replacement text to this line of the temp file
		else if (current_line == which_line)
		{
			//Read all of the info using dynamic memory
			printf("Enter the books title: \n");
			char* title = dinamikus_tomb();
			if (which_line == 6)
			{
				fprintf(fp2, "\n%s - ", title);
			}
			else
			{
				fprintf(fp2, "%s - ", title);
			}
			free(title);
			printf("Enter the books author: \n");
			char* author = dinamikus_tomb();
			fprintf(fp2, "%s - ", author);
			free(author);

			printf("How many genres: \n");
			int szeles;
			scanf("%d", &szeles);
			/*char str[300];
			do
			{
				scanf("%s", &str);
				szeles = (int)strtol(str, NULL, 10);
				if (szeles!=9)
				{
					printf("Try again!");
					break;
				}
			} while (szeles!=9);*/
			char** genre;
			foglal(&genre, szeles);
			for (int i = 0; i < szeles; i++)
			{
				fprintf(fp2, "%s ", genre[i]);
			}
			fprintf(fp2, "- ");
			for (int y = 0; y < szeles; ++y)
				free(genre[y]);
			free(genre);

			date datum;
			printf("Enter the date of publication (yyyy.mm.dd format): \n");
			scanf("%d.%d.%d", &datum.ev, &datum.honap, &datum.nap);
			//Check for invalid date
			for (int i = 0; i < 100; i++)
			{
				if ((datum.ev > 2022 || datum.honap > 12 || datum.nap > 31 || datum.ev < 0 || datum.honap < 0 || datum.nap < 0))
				{
					printf("Invalid date!\nTry again:\n");
					scanf("%d.%d.%d", &datum.ev, &datum.honap, &datum.nap);
					if (datum.honap == 2 && datum.nap > 29)
					{
						printf("Invalid date!\nTry again:\n");
						scanf("%d.%d.%d", &datum.ev, &datum.honap, &datum.nap);
					}
				}
			}
			if (which_line != 6)
			{
				fprintf(fp2, "%d.%d.%d\n", datum.ev, datum.honap, datum.nap);
			}
			else
			{
				fprintf(fp2, "%d.%d.%d", datum.ev, datum.honap, datum.nap);
			}
			fputs(buffer, fp2);
		}
		else
		{
			fputs(buffer, fp2);
		}
		current_line++;

	} while (!feof(fp1));

	fclose(fp1);
	fclose(fp2);
	remove(filename);
	rename(temp_filename, filename);
}
