#include <stdio.h>
#include "backend.h"

/****************************************
Implement Breadth-First Search on the graph constructed in "backend.c" and
use it in the find_path() below.

You can access functions and data structures constructed in "backend.c" via
"backend.h"
*****************************************/

#define UNDISCOV -10
#define DISCOV 10
#define PROCESSED 100 

int parent[5757] = { -1 };
int queue[5757] = { 0 };
int first = -1;
int last = 0;

void push(int idx) {
    queue[last] = idx;
    last = last + 1;
}

int pop() {
    int r = 0;

    first++;
    return queue[first];
}



void breadth_first_search(char start[5]) {
    int state[5757] = { 0 };
    int i = 0;
    int current = search_index(start);
    int vidx = 0;
    struct node* p = adj_list[current];

    for (i = 0; i < 5757; i++) {
        state[i] = UNDISCOV;
    }

    state[current] = DISCOV;
    push(current);

    while ((last-first)>1) {
        current = pop();
        p = adj_list[current];
        while (p != NULL) {
            vidx = p->index;
            if (state[vidx] == UNDISCOV) {
                state[vidx] = DISCOV;
                parent[vidx] = current;
                push(vidx);
            }
            p = p->next;
        }
        state[current] = PROCESSED;
    }

    return;
}

void find_path(char start[5], char goal[5])
{
    int s = search_index(start);
    int t = search_index(goal);
    int v = 0;
    int i = 0;
    int k = parent[t];
    int p[5757];

    for (i = 0; i < 5757; i++) {
        parent[i] = -1;
    }
    for (i = 0; i < 5757; i++) {
        queue[i] = 0;
    }

    first = -1;
    last = 0;

    if (s < 0) {
        printf("Sorry. ");
        print_five_chars(start);
        printf(" is not in the dicitonary.");
        return;
    }
    else if (t < 0) {
        printf("Sorry. ");
        print_five_chars(goal);
        printf(" is not in the dicitonary.");
        return;
    }

    breadth_first_search(start);
    k = parent[t];

    if (k == -1) {
        printf("Sorry. There is no path from ");
        print_word(s);
        printf(" to ");
        print_word(t);
        printf(".\n");
        return;
    }

    v = t;
    i = 0;

    while (v != s) {
        p[i++] = v;
        v = parent[v];
    }
    p[i] = s;
    k = 0;
    while (i >= 0) {
        printf("          ");
        printf("%d ", k++);
        print_word(p[i--]);
        printf("\n");
    }

}



