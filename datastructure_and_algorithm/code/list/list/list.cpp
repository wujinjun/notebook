//
//  list.cpp
//  list
//
//  Created by Jinjun on 2020/4/8.
//  Copyright © 2020 Jinjun. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "list.h"

int add_node_to_list(ListNode *list, int val) {
    ListNode *s, *p;
    if(list == NULL) {
        return -1;
    }
    p = list;
    while (p->next) {
        p = p->next;
    };
    s = (ListNode *)malloc(sizeof(ListNode));
    if (s == NULL) {
        return -1;
    }
    s->data = val;
    s->next = p->next;
    p->next = s;
    
    return 0;
}

int lookup_list(ListNode *list, bool is_print) {
    ListNode *p = list;
    if(list == NULL) {
        return -1;
    }
    while(p) {
        if (is_print == true) {
            printf("%d ", p->data);
        }
        p = p->next;
    }
    printf("\n");
    return 0;
}
