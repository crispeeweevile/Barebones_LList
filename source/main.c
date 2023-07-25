#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include "linkedsys.h"
#include "general_utils.h"

int main() {
    srand(time(NULL));
    int countar = 0;
    //while (countar != 1) {
        printf("workin\n");
        struct Node *err;
        struct Node **derr;
        // new_list & new_data test
        struct Node *myll = new_list(new_data(1, 3, 2));
        if (myll==METHOD_FAILED) return 1;
        for (int i=0; i < 100; ++i) {
            // insert and goto_next test
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

        // goto_first test
        goto_first(&myll);
        int index = 0;
        do {
            struct Data *cData = (*myll).nData;
            printf("Index: %d, Money: %d, Items: %d, Debt: %d\n", index, (*cData).Money, (*cData).Items, (*cData).Debt);
            derr = goto_next(&myll);
            if (derr==METHOD_FAILED) {
                printf("goto_next has failed. loopn: %d\n", index+1);
                break;
            }
            index++;
        } while ((*myll).next!=NULL);
        printf("made it to lin47\n");

        // goto_last & goto_prev test
        goto_last(&myll);
        index = 0;
        do {
            derr = goto_prev(&myll);
            if (derr==METHOD_FAILED) {
                printf("goto_prev has failed. loopn: %d\n", index+1);
                break;
            }
        } while ((*myll).prev!=NULL);
        printf("made it to lin59\n");
        {
            // test removing an item and freeing it.
            struct Data *tmp;
            struct Node *remd = remove_item(&myll, &tmp);
            free_node(&remd, false);
            printf("oh you want no data too?\n");
            free_data(&tmp);
        }
        printf("made it to lin69\n");
        // free_list, free_node, and free_data test
        free_list(&myll, true);
        printf("made it to lin70\n");
        //millisleep(10000);
    //}

    printf("E");
    return 0;
}
