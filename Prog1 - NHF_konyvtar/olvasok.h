#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "debugmalloc.h"
#pragma warning (disable:4996)

#ifndef olvasok
#define olvasok
/*This structure is used to store the readers information.
* This includes a 4 character long ID, integer type age,
* the book rented which is used in the rent() function
* and a name structure which has to subtypes: first name and last name.
*/
typedef struct reader {

	struct name
	{
		char first_name[100 + 1];
		char last_name[100 + 1];
	}name;
	int age;
	char ID[4];
	char book_rented[1000];

}reader;

int number_of_lines();

void rent2(reader r);

void rent();

void read_file(void);

void create();

void reader_info();
#endif 
