#include <stdlib.h>
#include "list.h"

list *createList(unsigned short int num) {
    list *newList = malloc(sizeof(*newList));
    newList->value = num;
    newList->next = NULL;
    return newList;
}

void destroyList(list *l) {
    while (l != NULL) {
        list *current = l;
        l = l->next;
        free(current);
    }
    free(l);
}

void add(list *l, int unsigned short num) {
    if (l == NULL) {
        l = createList(num);
    } else {
        list *current = l;
        while (current->next != NULL)
            current = current->next;
        current->next = createList(num);
    }
}

// 1 - true, 0 - false
int contains(list *l, int unsigned short num) {
    list *iter = l;
    while (iter->next != NULL) {
        if (iter->value == num)
            return 1;
        iter = iter->next;
    }
    if (iter->value == num)
        return 1;
    return 0;
}
