#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include "linkedsys.h"
#include "general_utils.h"

int main() {
    srand(time(NULL));
    struct Node *err;
    struct Node **derr;
    while (1) {
        struct Node *myll = new_list(new_data(1, 3, 2));
        if (myll==METHOD_FAILED) return 1;
        for (int i=0; i < 100; ++i) {
            err = insert_item(&myll, new_data(rand(),rand(),rand()));
            if (err==METHOD_FAILED) {
                printf("insert_item has failed. loopn: %d", i);
                free_list(&myll, true);
                exit(1);
            }
            derr = goto_next(&myll);
            if (derr==METHOD_FAILED) {
                printf("goto_next has failed. loopn: %d", i);
                free_list(&myll, true);
                exit(1);
            }
        }

        goto_first(&myll);
        int index = 0;
        do {
            struct Data *cData = (*myll).nData;
            printf("Index: %d, Money: %d, Items: %d, Debt: %d\n", index, (*cData).Money, (*cData).Items, (*cData).Debt);
            derr = goto_next(&myll);
            if (derr==METHOD_FAILED) {
                printf("goto_next has failed. loopn: %d", index+1);
                break;
            }
            index++;
        } while ((*myll).next!=NULL);
        
        

        free_list(&myll, true);
        millisleep(10000);
    }
    return 0;
}
