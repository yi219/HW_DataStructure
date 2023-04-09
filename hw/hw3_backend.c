#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "backend.h"
#include "memory.h"

void print_name(struct record *);
void print_number(struct record *);
void print_data(char *, int);

// comparison function for records
int compare(char key[3], struct record *);

// data
struct record * data = NULL; // Initially NULL.


void init()
{
  init_pool();
}


void add(char *name, char *number)
{
    struct record* p=new_node();
    int i = 0;

    if (p == NULL) {
        printf("Can't add.  The address book is full!\n");
        return;
    }
    else {
        for (i = 0; i < 3; i++) {
            p->name[i] = name[i];
        }
        for (i = 0; i < 4; i++) {
            p->number[i] = number[i];
        }
        p->next = data;
        data = p;
        return;
    }
  //printf("add() was not implemented.\n");
  // Error Message for overflow:
  // printf("Can't add.  The address book is full!\n");
}


void search(char name[3])  
{
  struct record *r=data;
  int result;

  while(r!=NULL && (result=compare(name,r))!=0)
    r=r->next;
  if(r==NULL)
    printf("Couldn't find the name.\n");
  else {
    print_name(r);
    printf(" : ");
    print_number(r);
    printf(" was found.\n");
  }
}


void delete(char name[3])
{
    struct record* p = data;
    struct record* q = data->next;
    int result;

    if (p == NULL)
    {
        printf("Couldn't find the name.\n");
        return;
    }
    else if ((result = compare(name, p)) == 0)
    {
        data = p->next;
        free_node(p);
        printf("The name was deleted.\n");
        return;
    }
    else
    {
        while (p != NULL && (result = compare(name, p)) != 0)
        {
            if (q != NULL && (result = compare(name, q)) != 0)
            {
                p = q;
                q = q->next;
            }
            else if (q == NULL)
            {
                printf("Couldn't find the name.\n");
                return;
            }
            else
            {
                p->next = q->next;
                free_node(q);
                printf("The name was deleted.\n");
                return;
            }
        }
    } 
  //printf("delete() is not implemented.\n");
  // Error Message:
  // printf("Couldn't find the name.\n");
}


/* Just a wrapper of strncmp(), except for the case r is NULL. 
Regard strncmp(a,b) as a-b.
Negative value if key is less than r.
​0​ if key and r are equal.
Positive value if key is greater than r. */
int compare(char key[3], struct record *r)
{
    return strncmp(key, r->name, 3);
}

    
// Prints ith name.
void print_name(struct record *r)
{
  print_data(r->name, 3);
}

// Prints ith number.
void print_number(struct record *r)
{
  print_data(r->number, 4);
}

void print_data(char * s, int n)
{
  int i;
  for (i=0; i<n; i++)
    putchar(s[i]);
}

void print_list()
{
    struct record* r = data;
    int i = 0;

    if (r == NULL)
        printf("The list is empty.\n");
    else {
        while (r != NULL) {
            for (i = 0; i < 3; i++) {
                printf("%c", r->name[i]);
            }
            printf(" : ");
            for (i = 0; i < 4; i++) {
                printf("%c", r->number[i]);
            }
            printf("\n");
            r = r->next;
        }
    }
  //printf("print_list() was not implemented.\n");
}

