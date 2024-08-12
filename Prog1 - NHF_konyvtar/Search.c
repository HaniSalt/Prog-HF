#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "konyv.h"
#pragma warning (disable:4996)

/*In this function we enter a key word, then while its not 9 (which return back to menu) 
* check if we havent reached the end of the file, if not,
* compare the key word with whats being read in the file using strstr, 
* if it matches, then we get it using fgets and print it onto the screen. 
*/
void search(void)
{
	char string[500];
	char konyvek[100] = { 0 };
	char buffer[2000];
	while (konyvek[0] != '9')
	{
		FILE* fp = fopen("konyvek.txt", "r");
		if (fp == NULL)
		{
			printf("Error file missing\n");
			exit(-1);
		}

		printf("Please enter a title (9 to end)\n");
		scanf("%s", konyvek);
		while (fscanf(fp, "%s", string) == 1)
		{
			if (konyvek[0] == '9')
			{
				break;
			}

			if (islower(konyvek[0]))
			{
				konyvek[0] = toupper(konyvek[0]);
			}

			if (strstr(string, konyvek) != 0)
			{
				fgets(buffer, 2000, fp);
				printf("%s%s\n", konyvek, buffer);
			}
		}
		fclose(fp);
	}
}



