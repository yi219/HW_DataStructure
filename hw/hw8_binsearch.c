#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define COMMAND_PROMPT ">"

char key[5757][6];

int prompt_name(char* s, char* p)
{
    char* q;
    char c;

    while (1) {
        printf("%s ", s);
        fflush(stdout);
        q = p;
        while (1) {
            c = getchar();
            if (c == EOF)
                exit(0);      // Should let exit() take care of the sudden EOF.
            if (c == '\n')
                break;
            if (q < p + 5)
                *q = c;
            q++;
        }
        if (q == p + 5)
            return 0;   // got a good name //
        else {
          printf("(Please type five lowercase letters and RETURN.)\n");
          return 1;
        }
    }
}

int compare(char name[5], char word[5])
{
    return strncmp(name, word, 5);
}

int search(char name[5])
{
    int l = 0;
    int u = 5756;
    int m;
    int i;

step2: m = (l + u) / 2;
    if (compare(name, key[m]) < 0) {
        u = m - 1;
        if (u < l) {
            //printf("-1\n");
            return -1;
        }
        else
            goto step2;
    }
    else if (compare(name, key[m]) > 0) {
        l = m + 1;
        if (u < l){
            //printf("-1\n");
            return -1;
        }
        else
            goto step2;
    }
    else if (compare(name, key[m]) == 0) {
        return m;
    }
}

int main() {
    FILE* data = fopen("words.dat", "r");

    char name[5];
    int i = 0;
    int j = 0;
    int k = 0;
    char key_n[300];

    for (i = 0; i < 4; i++) {
        fgets(key_n, 300, data);
        for (k = 0; k < 300; k++)
            key_n[k] = '\0';
    }

    for (i = 0; i < 5757;) {
        fgets(key_n, 300, data);
        for (j = 0; j < 5; j++)
            key[i][j] = key_n[j];
        key[i][5]='\0';
        for (k = 0; k < 300; k++)
            key_n[k] = '\0';
        i++;
    }

    fclose(data);

    printf("All the words were successfully read!\n");
    printf("Welcome to Search!\n");

    while (1) {
    restart:
        if (prompt_name(COMMAND_PROMPT, name) != 0)
          goto restart;
        printf("%d\n", search(name));
    }

  return 0;
}