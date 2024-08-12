#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
//#include "konyv2.h"
#include "debugmalloc.h"
#pragma warning (disable:4996)

#ifndef konyv1
#define konyv1
/* Structure used for storing date information */
typedef struct date {

	int ev, honap, nap;

}date;

int num_lines();

char* dinamikus_tomb();

void foglal(char*** ptomb, int szeles);

void view(void);

void add(int which_line);

void delete_book(int delete_line);

void choose_book();

void edit();

void search(void);

#endif
