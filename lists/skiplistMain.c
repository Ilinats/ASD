#include <stdio.h>
#include "skipList.c"

int main()
{
    SkipList *list = init_list();

    sl_insert(list, 1);
    sl_insert(list, 4);
    sl_insert(list, 3);
    sl_insert(list, -10);
    sl_insert(list, -5);
    sl_insert(list, 137);
    sl_insert(list, 100);
    sl_insert(list, 23);
    sl_insert(list, 5);

    printList(list);

    Node *result = sl_search(list, 127);
    Node *result2 = sl_search(list, 100);

    if (result != NULL)
        printf("\nFound %d\n", result->value);
    else
        printf("Not found\n");
    
    if (result2 != NULL)
        printf("Found %d\n", result2->value);
    else
        printf("Not found\n");

    clear(list);
}