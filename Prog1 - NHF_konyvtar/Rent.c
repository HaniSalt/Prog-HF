#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "debugmalloc.h"
#include "olvasok.h"
//#include "./olvasok.h"
#pragma warning (disable:4996)
/*Count the number of lines of a file
* Parameter is filename, and we go through each and every
* single line of this file, until the end (EOF), while
* doing so we increase the value of the count variable
* and return it - 2 (as each file starts with a header and a breakline).
*/
int number_of_lines(char* filename)
{
	reader r;
	FILE* fp;
	fp = fopen(filename, "r");
	bool keep_reading = true;
	char buffer[2000];
	int count = 0;
	do
	{
		fgets(buffer, 2000, fp);
		if (feof(fp))
		{
			keep_reading = false;
		}
		count++;
	} while (keep_reading);
	fclose(fp);
	return count - 2;
}
/*This function works very similarly to the rent function, where
* we have 2 files, one is being read and the other is being modified.
* The do-while loop is the same, except for the 2nd condition, where
* we check if the id matches whats read in the buffer, if so write into
* the 2nd file. In the else part we go to the following line and read its info.
*/
void rent2(reader r) {

	FILE* fp3, * fp4;
	char filename[] = "olvasok.txt";
	char temp[] = "rented_books.txt";
	fp3 = fopen(filename, "r");
	fp4 = fopen(temp, "w");

	char buffer2[2000];
	bool keep_reading = true;
	char temp_ID[4];
	int c = 0;
	int i = 5;
	char stop = ']';
	int current_line = -2;
	int lines = number_of_lines(filename);
	if (fp3 == NULL || fp4 == NULL)
	{
		printf("Error file missing\n");
		exit(-1);
	}
	do
	{
		fgets(buffer2, 2000, fp3);
		if (feof(fp3))
		{
			keep_reading = false;
		}
		else if (strstr(buffer2, temp_ID) != 0)
		{
			fputs(buffer2, fp4);
			fprintf(fp4, "- %s", r.book_rented);	
		}
		else
		{
			c = 0;
			temp_ID[0] = '\0';
			//i = 5;
			while (buffer2[i] != stop && c < 5)
			{
				temp_ID[c++] = buffer2[i];
				i++;
			}
		}
		current_line++;
	} while (keep_reading);

	fclose(fp3);
	fclose(fp4);
}

/*We will be using 2 different files in this function,
* First we have the original file which we will be deleted
* and have its edited information stored in a second temporary file which will be renamed.
* In this function every line is read read in a buffer variable and stored,
* and we ask the user to choose a row number (which book to rent) as well a reader ID,
* and use a do-while loop with 2 conditions. First is to check whether we have reached
* the end of the file, if so then the (boolean) keep_reading variable is set to false
* and we exit the loop. Second is to check whether we have reached the row to be modified.
* If so, then we store the book we want in the (reader) r.book_rented variable and check
* if the book has been rented before or not. If it hasnt then we modify the row by adding the ID and [R] symbol.
* Finally, if neither of these conditions are met, then we just simply write the line onto the second file.
* After exiting this loop, we give the r information to the rent2 function which continues this.
*/
void rent()
{
	FILE* fp1, * fp2;
	char buffer[2000];
	char filename[] = "konyvek.txt";
	char temp[] = "temp_konyvek.txt";

	fp1 = fopen(filename, "r");
	fp2 = fopen(temp, "w");
	if (fp1 == NULL || fp2 == NULL) {
		perror("Unable to open fp");
		return;
	}

	int chosen_line;
	reader r;
	view();

	printf("\nChoose a book to rent: ");
	scanf("%d", &chosen_line);
	int n = number_of_lines(filename);
	for (int i = 0; i < 100; i++)
	{
		if (chosen_line > n)
		{
			printf("Total number of lines exceeded!\nTry again:\n");
			scanf("%d", &chosen_line);
		}
	}
	printf("Choose a student ID (to rent): ");
	scanf("%s", &r.ID);

	bool keep_reading = true;
	int current_line = 3;
	chosen_line = chosen_line + 4;

	do
	{
		fgets(buffer, 2000, fp1);
		if (feof(fp1))
		{
			keep_reading = false;
		}
		else if (current_line == chosen_line)
		{
			strcpy(r.book_rented, buffer);
			if (strstr(buffer, "[R]") != 0)
			{
				printf("Book already rented");
				fputs(buffer, fp2);
			}
			else
			{
				fprintf(fp2, "[R] [%s] ", r.ID);
				fputs(buffer, fp2);
			}
		}
		else
		{
			fputs(buffer, fp2);
		}
		current_line++;
	} while (keep_reading);

	fclose(fp1);
	fclose(fp2);
	remove(filename);
	rename(temp, filename);

	rent2(r);
}