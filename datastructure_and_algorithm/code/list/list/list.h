//
//  list.h
//  list
//
//  Created by Jinjun on 2020/4/7.
//  Copyright © 2020 Jinjun. All rights reserved.
//

#ifndef list_h
#define list_h

struct double_list {
    int data;
    double_list *next;
    double_list *prev;
};

struct ListNode {
    int data;
    ListNode *next;
};

int add_node_to_list(ListNode *list, int val);

int lookup_list(ListNode *list, bool is_print);

#endif /* list_h */
