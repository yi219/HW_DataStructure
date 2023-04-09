#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "backend-bst.h"     

#define POOL_SIZE 10

// record structure
struct record {
  char name[3];
  char number[4];
  struct record * left;
  struct record * right;
};

void print_name(struct record *);
void print_number(struct record *);

// pool of memory
static struct record pool[POOL_SIZE]; // static because pool is strictly private
struct record * top=pool;  // a pointer variable for pool stack top.

// comparison function for records
int compare(char key[3], struct record *);

// data
struct record * data = NULL; // Initially NULL.


void init_pool() // Initialize the pool; Use right instead of next!!!
{
  int i;
  struct record *r=pool;
  struct record *s;

  pool[POOL_SIZE-1].right=NULL;  

  for(i=1;i<POOL_SIZE;i++) {  
    s=r++;
    s->right=r;
  }
}

// Get a node from the pool. Returns NULL if pool is empty. 
// When calling new_node(), make sure to check if it is NULL. 
struct record * new_node()  
{
  struct record *r;
  
  if(top==NULL) 
    return NULL;
    
  r=top;
  top=r->right;  // Again, right instead of next.
  return r;
}

// Push a node to the pool.
void free_node(struct record *r)
{
  r->right=top;  // Again, right instead of next.
  top=r;
}


/***********************
Address Book by binary search tree
**************************/

void search(char name[3])  
{
  struct record *r; // Pointer to record being compared.
                    //data or left/right field of a node.
  int result;
  r=data;

  while (r!=NULL) {
    if ((result=compare(name,r))<0)
      r=r->left;
    else if (result==0) {
      print_name(r);
      printf(" : ");
      print_number(r);
      printf(" was found.\n");
      return;
    }
    else // case >0
      r=r->right;
  }
  printf("Couldn't find the name.\n");
}


void add(char *name, char *number)
{
    struct record* r = new_node();
    struct record* p = data;
    struct record* q;
    int i;

    if (r == NULL) {
        printf("Can't add.  The pool is empty!\n");
        return;
    }
    else {
        for (i = 0; i < 3; i++)
            r->name[i] = name[i];
        for (i = 0; i < 4; i++)
            r->number[i] = number[i];
        r->left = NULL;
        r->right = NULL;

        if (p == NULL) {
            data = r;
            printf("The name was successfully added!\n");
            return;
        }
        else {
            while (p != NULL) {
                if (compare(name, p) <= 0) {
                    q = p;
                    p = p->left;
                    if (p == NULL) {
                        q->left = r;
                        printf("The name was successfully added!\n");
                        return;
                    }
                }
                else {
                    q = p;
                    p = p->right;
                    if (p == NULL) {
                        q->right = r;
                        printf("The name was successfully added!\n");
                        return;
                    }
                }
            }
        }
    }   
}


// The most complicated.
void delete(char name[3])
{
    struct record* p = data;
    struct record* q;
    struct record* r;
    struct record* s;
    int i;


    if (data == NULL) return;
    while (p != NULL) {
        if (compare(name, p) < 0) {
            q = p;
            p = p->left;
        }
        else if (compare(name, p) > 0) {
            q = p;
            p = p->right;
        }
        else if (compare(name, p) == 0) {
            if (p == data) {
                if (p->left == NULL && p->right == NULL) {
                    data = NULL;
                    free_node(p);
                    printf("The name was deleted.\n");
                    return;
                }
                else if (p->right == NULL) {
                    data = p->left;
                    free_node(p);
                    printf("The name was deleted.\n");
                    return;
                }
                else if (p->left == NULL) {
                    data = p->right;
                    free_node(p);
                    printf("The name was deleted.\n");
                    return;
                }
                else {
                    r = p->right;
                    s = p;
                    if (r->left == NULL) {
                        r->left = p->left;
                        data = r;
                        free_node(p);
                        printf("The name was deleted.\n");
                        return;
                    }
                    while (r->left != NULL) {
                        s = r;
                        r = r->left;
                    }
                    for (i = 0; i < 3; i++)
                        p->name[i] = r->name[i];
                    for (i = 0; i < 4; i++)
                        p->number[i] = r->number[i];
                    s->left = r->right;
                    free_node(r);
                    printf("The name was deleted.\n");
                    return;
                }
            }
            else {
                if (p->left == NULL && p->right == NULL) {
                    if (q->left == p) {
                        q->left = NULL;
                        free_node(p);
                        printf("The name was deleted.\n");
                        return;
                    }
                    else if (q->right == p) {
                        q->right = NULL;
                       	free_node(p);
                        printf("The name was deleted.\n");
                        return;
                    }
                }
                else if (p->right == NULL) {
                    if (q->left == p) {
                        q->left = p->left;
                        free_node(p);
                        printf("The name was deleted.\n");
                        return;
                    }
                    else if (q->right == p) {
                        q->right = p->left;
                        free_node(p);
                        printf("The name was deleted.\n");
                        return;
                    }
                }
                else if (p->left == NULL) {
                    if (q->left == p) {
                        q->left = p->right;
                        free_node(p);
                        printf("The name was deleted.\n");
                        return;
                    }
                    else if (q->right == p) {
                        q->right = p->right;
                        free_node(p);
                        printf("The name was deleted.\n");
                        return;
                    }
                }
                else {
                    r = p->right;
                    s = p;
                    if (r->left == NULL) {
                        for (i = 0; i < 3; i++)
                            p->name[i] = r->name[i];
                        for (i = 0; i < 4; i++)
                            p->number[i] = r->number[i];
                        p->right = r->right;
                        free_node(r);
                        printf("The name was deleted.\n");
                        return;
                    }
                    while (r->left != NULL) {
                        s = r;
                        r = r->left;
                    }
                    for (i = 0; i < 3; i++)
                        p->name[i] = r->name[i];
                    for (i = 0; i < 4; i++)
                        p->number[i] = r->number[i];
                    s->left = r->right;
                    free_node(r);
                    printf("The name was deleted.\n");
                    return;
                }
            }
        }
    }
    printf("Couldn't find the name.\n");
    return;

  // Messages to print
  //  printf("The name was deleted.\n");  
  //  printf("Couldn't find the name.\n");
}


/* Just a wrapper of strncmp().
Regard strncmp(a,b) as a-b.
Negative value if key is less than r.
​0​ if key and r are equal.
Positive value if key is greater than r. */
int compare(char key[3], struct record *r)
{
    return strncmp(key, r->name, 3);
}


void print_data(char * s, int n)
{
  int i;
  for (i=0; i<n; i++)
    putchar(s[i]);
}

void print_name(struct record *r)
{
  print_data(r->name, 3);
}

void print_number(struct record *r)
{
  print_data(r->number, 4);
}

void print_inorder(struct record *t)
{
    if (t == NULL) return;
    else {
        print_inorder(t->left);
        print_name(t);
        printf(" : ");
        print_number(t);
        printf("\n");
        print_inorder(t->right);
        return;
    }    
}

void print_list()  
{
  print_inorder(data);
}


// returns the height of the BST.
int height(struct record *t)
{
    int max;

    if (t == NULL)
        return -1;
    else {
        if (height(t->left) >= height(t->right))
            max = height(t->left);
        else max = height(t->right);
        return (1 + max);
    }
  // dummy return.  Should return a valid height.
}

void print_height()  
{
  printf("The Address Book BST's height is %d.\n", height(data));
}
