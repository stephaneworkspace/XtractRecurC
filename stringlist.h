#include <stdio.h>   // pulls in declaration for printf
#include <stdlib.h>  // pulls in declaration of malloc, free
#include <string.h>  // pulls in declaration for strcpy, ctrcmp.
typedef struct {
    char **data;
    int size;
    int capacity;
} StringList;

using namespace std;

StringList *new_stringlist()
{
    StringList *sl = malloc(sizeof(StringList));
    sl->size = 0;
    sl->capacity = 1;
    sl->data = malloc(sizeof(char **));
    return sl;
}

void stringlist_add(StringList *sl, char *s)
{
    if (sl->size + 1 > sl->capacity) {
        sl->capacity *= 2;
        sl->data = realloc(sl->data, sizeof(char *) * sl->capacity);
    }
    sl->data[sl->size] = malloc(strlen(s) + 1);
    strcpy(sl->data[sl->size++], s);
}

int stringlist_find(StringList *sl, char *s)
{
    for (int i = 0; i < sl->size; i++) {
        if (strcmp(sl->data[i], s) == 0) return i;
    }
    return -1;
}

void stringlist_rm(StringList *sl, int index)
{
    free(sl->data[index]);
    sl->data[index] = NULL;
    for (int i = index; i < sl->size; i++) {
        printf("moving item %s up\n", sl->data[i + 1]);
        sl->data[i] = sl->data[i + 1];
    }
    sl->data[sl->size--] = NULL;
}

void stringlist_print(StringList *list)
{
    for (int i = 0; i < list->size; i++) {
        printf("%s\n", list->data[i]);
    }
}

