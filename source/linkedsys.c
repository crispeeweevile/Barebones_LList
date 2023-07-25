#include "general_utils.h"
#include "linkedsys.h"

struct Data *new_data(int _money, int _items, int _debt) {
    struct Data *nd = safe_malloc(sizeof(struct Data));

    nd->Debt=_debt;
    nd->Items=_items;
    nd->Money=_money;

    return nd;
}

error free_data(struct Data **data) {
    printf("surely you didn't give bad data lol\n");
    if (!data) return FFAILURE;
    printf("surely you didn't give bad data lol (agin?)\n");
    if (!(*data)) return FFAILURE;
    printf("valid data 2 free?\n");
    free(*data);
    printf("fine i guess ill remove ur data\n");
    (*data) = NULL;
    return FSUCCESS;
}


struct Node *new_list(struct Data *data) {
    if (data == NULL) return METHOD_FAILED;
    struct Node *new_head = safe_malloc(sizeof(struct Node));

    //init all the values bc
    new_head->next = NULL;
    new_head->prev = NULL;
    //new_head->index = 0;
    new_head->nData = data;

    return new_head;
}

struct Node *create_item(struct Data *data) {
    // rename of new_list, makes code easier to read
    return new_list(data);
}

error free_node(struct Node **llnode, bool _free_data) {
    if (llnode == NULL) return FFAILURE;
    if ((*llnode) == NULL) return FFAILURE;
    printf("at least you gave valid data. lol\n");
    if (_free_data) {
        printf("death by data free?\n");
        free_data((&(*llnode)->nData));
        printf("no more data\n");
    }
    printf("death by free\n");
    free(*llnode);
    printf("why no wrk?\n");
    //(*llnode) = NULL;
    return FSUCCESS;
}

error free_list(struct Node **llnode, bool _free_data) {
    if (llnode == NULL) return FFAILURE;
    if ((*llnode) == NULL) return FFAILURE;

    printf("the start\n");
    goto_first(&(*llnode));
    struct Node *prevprev;
    while ((**llnode).next != NULL) {
        printf("slugma\n");
        goto_next(&(*llnode));
        printf("here. . .\n");
        struct Node *prev = (**llnode).prev;
        printf("there. . .\n");
        free_node((&prev), _free_data);
        printf("loopindeez\n");
    }

    if (llnode != NULL) {
        if ((*llnode) != NULL) {
            printf("freecur\n");
            free_node((&(*llnode)), _free_data);
        }
    }
    printf("shuldartn\n");
    return FSUCCESS;
}

struct Node **goto_first(struct Node **llnode) {
    if (llnode == NULL) return METHOD_FAILED;
    if ((*llnode) == NULL) return METHOD_FAILED;
    while ((**llnode).prev != NULL) {
        struct Node **err = goto_prev(llnode);
        if (err==NULL) {
            break; 
            return METHOD_FAILED;
        }
    }
    return llnode;
}

struct Node **goto_last(struct Node **llnode) {
    if (llnode == NULL) return METHOD_FAILED;
    if ((*llnode) == NULL) return METHOD_FAILED;
    while ((**llnode).next != NULL) {
        struct Node **err = goto_next(llnode);
        if (err==NULL) {
            break; 
            return METHOD_FAILED;
        }
    }
    return llnode;
}

struct Node **goto_next(struct Node **llnode) {
    if (llnode == NULL) return METHOD_FAILED;
    if ((*llnode) == NULL) return METHOD_FAILED;
    if ((**llnode).next != NULL) (*llnode) = (**llnode).next; else return METHOD_FAILED;
    return llnode;
}

struct Node **goto_prev(struct Node **llnode) {
    if (llnode == NULL) return METHOD_FAILED;
    if ((*llnode) == NULL) return METHOD_FAILED;
    if ((**llnode).prev != NULL) (*llnode) = (**llnode).prev; else return METHOD_FAILED;
    return llnode;
}

struct Node *insert_item(struct Node **llnode, struct Data *data) {
    if (llnode == NULL) return METHOD_FAILED;
    if ((*llnode) == NULL) return METHOD_FAILED;
    if (data == NULL) return METHOD_FAILED;

    struct Node *item_2insert = create_item(data);
    if (item_2insert == NULL) return METHOD_FAILED;
    if ((**llnode).next != NULL) {
        struct Node *next = (**llnode).next;
        (*next).prev = item_2insert;
        (*item_2insert).next = next;
    }
    (**llnode).next = item_2insert;
    (*item_2insert).prev = (*llnode);

    return item_2insert;
}

struct Node *remove_item(struct Node **llnode, struct Data **data) {
    if (llnode == NULL) return METHOD_FAILED;
    if ((*llnode) == NULL) return METHOD_FAILED;
    if (data == NULL) return METHOD_FAILED;

    struct Node **item_2remove = (&(*llnode));
    // goto next so we don't lose the entire linked list
    struct Node **error = goto_next(llnode);
    if (error == METHOD_FAILED) {
        struct Node **error = goto_prev(llnode);
        if (error == METHOD_FAILED) return METHOD_FAILED;
    }
    if ((**item_2remove).next != NULL) {
        struct Node *next = (**llnode).next;
        (*item_2remove)->next = NULL;
        next->prev = NULL;
        if ((**item_2remove).prev != NULL) {
            struct Node *prev = (**llnode).prev;
            (*item_2remove)->prev = NULL;
            prev->next = next;
            next->prev = prev;
        }
    }
    if ((**item_2remove).prev != NULL) {
        struct Node *prev = (**llnode).prev;
        (*item_2remove)->prev = NULL;
        prev->next = NULL;
    }

    return (*item_2remove);
}
