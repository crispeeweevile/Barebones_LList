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
    if (data == NULL) return FFAILURE;
    if ((*data) == NULL) return FFAILURE;
    free(*data);
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
    if (_free_data) {
        free_data((&(**llnode).nData));
    }
    free(*llnode);
    return FSUCCESS;
}

error free_list(struct Node **llnode, bool _free_data) {
    if (llnode == NULL) return FFAILURE;
    if ((*llnode) == NULL) return FFAILURE;

    goto_first(llnode);
    while ((**llnode).next != NULL) {
        struct Node *next = ((**llnode).next);
        free_node(llnode, _free_data);
        (*llnode) = next;
    }

    if (llnode != NULL) {
        if ((*llnode) != NULL) {
            free_node(llnode, _free_data);
        }
    }

    return FSUCCESS;
}

struct Node **goto_first(struct Node **llnode) {
    if (llnode == NULL) return METHOD_FAILED;
    if ((*llnode) == NULL) return METHOD_FAILED;
    while ((**llnode).prev != NULL) {
        struct Node **err = goto_prev(llnode);
        if (err==NULL) return METHOD_FAILED;
    }
    return llnode;
}

struct Node **goto_last(struct Node **llnode) {
    if (llnode == NULL) return METHOD_FAILED;
    if ((*llnode) == NULL) return METHOD_FAILED;
    while ((**llnode).next != NULL) {
        struct Node **err = goto_next(llnode);
        if (err==NULL) return METHOD_FAILED;
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
