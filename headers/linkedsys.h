#pragma once
#include <stdbool.h>
#define METHOD_FAILED NULL
#define FFAILURE -1
#define FSUCCESS 0

typedef int error;
struct Data {
    int Money;
    int Items;
    int Debt;
};

struct Node {
    //int index;
    struct Data *nData;
    struct Node *next;
    struct Node *prev;
};

struct Data *new_data(int _money, int _items, int _debt);
error free_data(struct Data **data);

struct Node *new_list(struct Data *data);
error free_node(struct Node **llnode, bool _free_data);
error free_list(struct Node **llnode, bool _free_data);
struct Node **goto_first(struct Node **llnode);
struct Node **goto_last(struct Node **llnode);
struct Node **goto_next(struct Node **llnode);
struct Node **goto_prev(struct Node **llnode);
struct Node *insert_item(struct Node **llnode, struct Data *data);
struct Node *remove_item(struct Node **llnode, struct Data **data);
