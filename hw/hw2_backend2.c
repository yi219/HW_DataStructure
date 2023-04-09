#include <stdio.h>
#include <stdlib.h>  // qsort
#include <string.h>  // strncmp
#include "backend2.h"     

#define NUMBER_OF_RECORDS 20

// record structure
struct record {
  char name[3];
  char number[4];
};

// Declaration of the array for the main data
struct record data[NUMBER_OF_RECORDS];

// index of the first empty slot
int k=0;  

// Declaration of functions visible only in this file.
int cmp_record(const void *, const void *);
int search_index(char [3]);
void print_name(int);
void print_number(int);
void print_data(char *, int);


void add(char *name, char *number)
{
  if (k<NUMBER_OF_RECORDS) {
    data[k].name[0]=name[0];
    data[k].name[1]=name[1];
    data[k].name[2]=name[2];
    data[k].number[0]=number[0];
    data[k].number[1]=number[1];
    data[k].number[2]=number[2];
    data[k].number[3]=number[3];
    print_name(k);
    printf(" : ");
    print_number(k);
    printf(" was successfully added!\n");
    k++;
  }
  else
    printf("Can't add.  Address book is full.\n");
}


// Returns the index of the found index.
// Returns -1, if not found.
int search_index(char name[3])  
{
    int i = 0;
    for (i = 0; i < 5; i++)
    {
        if (name[0] == data[i].name[0] && name[1] == data[i].name[1] && name[2] == data[i].name[2])
            return i;
    }

    if (i == 5)
        return -1;
}


void search(char name[3])  
{
  int s_result;

  s_result=search_index(name);
  if (s_result==-1) 
    printf("Couldn't find the name.\n");
  else {
    print_name(s_result);
    printf(" : ");
    print_number(s_result);
    printf(" was found.\n");
  }
}


void delete(char name[3])
{
  // Use search_index()
    int index = search_index(name);
    int a = 0;

    if (index == -1)
    {
        printf("Couldn't find the name. \n");
        return;
    }
    else
    {
        for (a = 0; a < 3; a++)
            data[index].name[a] = '\0';
        for (a = 0; a < 4; a++)
            data[index].number[a] = '\0';
            printf("The name was successfully deleted.\n");

        for (; index < k - 1 ; index++)
        {
            for (a = 0; a < 3; a++)
            {
                data[index].name[a] = data[index+1].name[a];
               data[index+1].name[a] = '\0';
            }
            for (a = 0; a < 4; a++)
            {
                 data[index].number[a] =  data[index+1].number[a];
                 data[index+1].number[a] = '\0';
            }
        }
        k--;
        return;
    }
}


void sort_list()
{
/*   qsort(array, array_size, sizeof(struct record),  */
/* 	(int (*)(const void*, const void*))cmp_record); */

   qsort(data, k, sizeof(data[0]), cmp_record);

  // The message for command 'T'.
  printf("Address Book is sorted now!\n");

}

int cmp_record(const void *r1, const void *r2)
{
  struct record * x = (struct record *) r1;
  struct record * y = (struct record *) r2;
  return strncmp(x->name, y->name, 3);
}


void print_list()
{
  int i;
  for (i=0; i<k; i++) {
    print_name(i);
    printf(" : ");
    print_number(i);
    printf("\n");
  }
}

// Prints ith name.
void print_name(int i)
{
  print_data(data[i].name, 3);
}

// Prints ith number.
void print_number(int i)
{
  print_data(data[i].number, 4);
}

void print_data(char * s, int n)
{
  int i;
  for (i=0; i<n; i++)
    putchar(s[i]);
}

