#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "konyv.h"
#include "debugmalloc.h"
#pragma warning (disable:4996)

/*This function is used to delete books(rows) from the original file.
* We open 2 files (one in reading mode and the other in writing)
* where the parameter is the row to be delete, and copy all of the information
* from one file to the other using fgets and fputs, while making sure
* that the chosen row number doesnt match the current.
*/
void delete_book(int delete_line)
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

	bool keep_reading = true;
	int current_line = 4;
	delete_line = delete_line + 5;
	do
	{
		fgets(buffer, 2000, fp1);
		if (feof(fp1))
		{
			keep_reading = false;
		}
		else if (current_line != delete_line)
		{
			fputs(buffer, fp2);
		}
		current_line++;

	} while (keep_reading);
	
	fclose(fp1);
	fclose(fp2);
	remove(filename);
	rename(temp, filename);
}
/*We ask the user to choose a book(row)
* and move to the delete_book function.
*/
void choose_book()
{
	view();
	int delete_line;
	printf("\nWhich line would you like to delete: ");
	scanf("%d", &delete_line);
	delete_book(delete_line);
}

/*Count the number of lines of a file.
* Parameter is filename, and we go through each and every
* single line of this file, until the end (EOF), while
* doing so we increase the value of the count variable
* and return it - 2 (as each file starts with a header and a breakline).
*/
int num_lines()
{
	FILE* fp;
	fp = fopen("konyvek.txt", "r");
	bool keep_reading = true;
	char buffer[2000];
	int count = 3;
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
	return count-2;

}

/*Over here we use the previously mentioned delete and add functions
* If we reach the line chosen by the user, then we delete it and
* request the user to enter the information.
*/
void edit() {
	int replace_line = 0;
	view();
	printf("\nWhich line would you like to edit/replace: ");
	scanf("%d", &replace_line);

	bool keep_reading = true;

	int current_line = 4;
	replace_line = replace_line + 5;
	int n=num_lines();
	while (current_line!=n)
	{
		if (current_line==replace_line)
		{
			replace_line = replace_line - 5;
			delete_book(replace_line);
			add(replace_line);
		}
		current_line++;
	}

	return;
}