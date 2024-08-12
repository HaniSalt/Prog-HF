#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "debugmalloc.h"
#include "olvasok.h"
//#include "./olvasok.h"
#pragma warning (disable:4996)


/*This function is used to read each line of a file letter by letter.
* Its parameter is the filename we want to read, and we go through
* every letter until EOF.
*/
void read_file(char*filename)
{
	FILE* fp;
	fp = fopen(filename, "r");
	if (fp == NULL) {
		perror("Unable to open file");
		return;
	}
	char ch;
	ch = fgetc(fp);
	while (ch != EOF)
	{
		printf("%c", ch);
		ch = fgetc(fp);
	}
	fclose(fp);
}

/*We ask the user to enter information of the reader
* and store it in a defined type reader variable
* and print it all in the olvasok file.
*/
void create() {
	reader* r;
	r = (reader*)malloc(sizeof(reader));
	FILE* fp = fopen("olvasok.txt", "a");
	if (fp == NULL)
	{
		printf("Error file missing\n");
		exit(-1);
	}

	printf("Enter a studnet ID (1-1000): ");
	scanf("%s", &r->ID);
	/*for (int i = 0; i < 100; i++)
	{

		if (r->ID < 1 || r->ID>1000)
		{
			printf("Invalid input!\nTry again:\n");
			scanf("%s", &r->ID);
		}
		else
		{
			break;
		}
	}*/
	printf("Enter a name: ");
	scanf("%s %s", &r->name.last_name, &r->name.first_name);
	printf("Enter age: ");
	scanf("%d", &r->age);
	fprintf(fp, "\n%s - %s %s - %d", r->ID, r->name.last_name, r->name.first_name, r->age);
	free(r);
	fclose(fp);
}

/*This is a simple menu used to navigate between
* the different functions, using a do-while loop
* and switch-cases.
*/
void reader_info()
{
	char str[50];
	int option;
	printf("Please choose in what way you want to search:\n");
	do
	{
		printf("Type:\n1 (Display all readers)\n"
			"2 (Rented books)\n"
			"3 (Add new reader)\n"
			"4 (Rent a book)\n"
			"9 (Exit)\n\n");

		scanf("%s", &str);
		option = (int)strtol(str, NULL, 10);
		switch (option)
		{
		case 1:
			printf("\n");
			read_file("olvasok.txt");
			break;
		case 2:
			printf("\n");
			read_file("rented_books.txt");
			break;
		case 3:
			printf("\n");
			create();
			break;
		case 4:
			printf("\n");
			rent();
			break;
		default:
			if (option != 9)
			{
				printf("Invalid input!");
				break;
			}
		}
		printf("\n\n");
	} while (option != 9);
}