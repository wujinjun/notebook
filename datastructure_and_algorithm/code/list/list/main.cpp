//
//  main.cpp
//  list
//
//  Created by Jinjun on 2020/4/7.
//  Copyright © 2020 Jinjun. All rights reserved.
//

#include <iostream>
#include "list.h"

using namespace std;
class ListOP {
public:
    ListNode* reverse(ListNode *head) {
        if(head == NULL) {
            return NULL;
        }
        ListNode *cur = head;
        ListNode *prev = NULL;
        ListNode *next;
        while(cur != NULL) {
            next = cur->next;
            cur->next = prev;
            prev = cur;
            cur = next;
        }
        return prev;
    }
};

ListNode *make_example_list(int N) {
    ListNode *list;
    list = (ListNode *)malloc(sizeof(ListNode));
    list->data = 0;
    list->next = NULL;

    for (int i = 0; i < N; ++i) {
        add_node_to_list(list, i);
    }
    lookup_list(list, true);
    return list;
}

int main(int argc, const char * argv[]) {
    //test_list();
    ListNode *list = make_example_list(10);
    ListOP op;
    ListNode *out_list;

    out_list = op.reverse(list);
    
    lookup_list(out_list, true);
    
    
    return 0;
}
