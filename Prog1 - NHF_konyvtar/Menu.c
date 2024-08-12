#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "konyv.h"
#include "olvasok.h"
#include "debugmalloc.h"
#pragma warning (disable:4996)

/*This is a simple menu used to navigate between
* the different functions, using a do-while loop
* and switch-cases (each case goes to different function).
*/
int main(void)
{
	printf("Welcome to the BME library!\n\n");

	char str[50];
	int option;
	FILE* fp;

	do
	{
		printf("This is the main menu!\n");
		printf("Type:\n1 (To list all books)\n"
			"2 (to add a new book)\n"
			"3 (To find a specific author/book)\n"
			"4 (Delete old book)\n"
			"5 (Edit the information of an old book)\n"	
			"6 (For Readers Functions)\n"
			"9 (Exit)\n\n");

		scanf("%s", &str);
		option = (int)strtol(str, NULL, 10);
		switch (option)
		{
		case 1:
			printf("\n");
			view();
			break;
		case 2:
			printf("\n");
			add(0);
			break;
		case 3:
			printf("\n");
			search();
			break;
		case 4:
			printf("\n");
			choose_book();
			break;
		case 5:
			printf("\n");
			edit();
			break;
		case 6:
			printf("\n");
			reader_info();
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
	if (option == 9)
	{
		printf("Thank you for visiting\n");
	}

	return 0;
}