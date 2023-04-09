#include <stdio.h>
#include "backend1.h"     

#define NUMBER_OF_RECORDS 5

// External Variables

char data_name[NUMBER_OF_RECORDS][3];  
char data_number[NUMBER_OF_RECORDS][4];  

int k=0;  // index of the first empty slot

void add(char name[3], char number[4])
{
  if (k<NUMBER_OF_RECORDS) {
    data_name[k][0]=name[0];
    data_name[k][1]=name[1];
    data_name[k][2]=name[2];
    data_number[k][0]=number[0];
    data_number[k][1]=number[1];
    data_number[k][2]=number[2];
    data_number[k][3]=number[3];
    print_name(k);
    printf(" : ");
    print_number(k);
    printf(" was successfully added!\n");
    k++;
  }
  else
    printf("Can't add.  Address book is full.\n");
}


// Returns the index of the found record.
// Returns -1, if not found.
int search_index(char name[3])  
{
    int i = 0;
    for (i = 0; i < 5; i++)
    {
        if (name[0] == data_name[i][0] && name[1] == data_name[i][1] && name[2] == data_name[i][2])
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
            data_name[index][a] = '\0';
        for (a = 0; a < 4; a++)
            data_number[index][a] = '\0';
            printf("The name was successfully deleted.\n");

        for (; index < k - 1 ; index++)
        {
            for (a = 0; a < 3; a++)
            {
                data_name[index][a] = data_name[index + 1][a];
                data_name[index + 1][a] = '\0';
            }
            for (a = 0; a < 4; a++)
            {
                data_number[index][a] = data_number[index + 1][a];
                data_number[index + 1][a] = '\0';
            }
        }
        k--;
        return;
    }
}



// Prints ith name.
void print_name(int i)
{
  print_data(data_name[i], 3);
}

// Prints ith number.
void print_number(int i)
{
  print_data(data_number[i], 4);
}


void print_data(char * s, int n)
{
  int i;
  for (i=0; i<n; i++)
    putchar(s[i]);
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
