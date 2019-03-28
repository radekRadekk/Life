#ifndef LIFE_LIST_H
#define LIFE_LIST_H

typedef struct _list {
    unsigned short int value;
    struct _list *next;
} list;

list *createList(unsigned short int num);

void destroyList(list *);

void add(list *, unsigned short int num);

int contains(list *l, unsigned short int num);

#endif //LIFE_LIST_H
