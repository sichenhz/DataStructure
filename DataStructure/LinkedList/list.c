//
//  list.c
//  DataStructure
//
//  Created by Jason on 1/6/19.
//  Copyright © 2019 UTAS. All rights reserved.
//

#include "list.h"
#include <stdlib.h>

List new_list() {
    List temp;
    temp.head = NULL;
    return temp;
}

void insert_at_front(List *self, int data) {
    ListNodePtr new_node = malloc(sizeof *new_node);
    new_node->data = data;
    new_node->next = self->head;
    self->head = new_node;
}

void insert_in_order(List *self, int data) {
    ListNodePtr current = self->head;
    ListNodePtr prev = NULL;
    
    ListNodePtr new_node = malloc(sizeof *new_node);
    new_node->data = data;
    new_node->next = NULL;
    
    while (current != NULL && current->data < data) {
        prev = current;
        current = current->next;
    }
    
    if (current == self->head) { // at front
        new_node->next = current;
        self->head = new_node;
    } else {                     // middle
        new_node->next = current;
        prev->next = new_node;
    }
}

void reverse_list(List *self) {
    
    ListNodePtr previous = NULL;
    ListNodePtr current = self->head;
    
    while (current != NULL) {
        
        ListNodePtr next = current->next;
        
        if (next == NULL) {
            self->head = current; // To change the head from the front to the end
        }
        
        next = previous; // Key: Reverse each pointer
        
        // These two lines are to prepare the next loop
        previous = current;
        current = next;
    }
}

List zip(List *l1, List *l2) { // zip two lists together
    
    List new_list;
    new_list.head = NULL;

    ListNodePtr current_l1 = l1->head;
    ListNodePtr current_l2 = l2->head;

    while (current_l1 != NULL && current_l2 != NULL) {
        if (new_list.head == NULL) {
            new_list.head = current_l1;
        }
        
        ListNodePtr temp_l1 = current_l1;
        ListNodePtr temp_l2 = current_l2;
        
        current_l1 = current_l1->next;
        current_l2 = current_l2->next;
        
        temp_l1->next = temp_l2;
        temp_l2->next = current_l1;        
    }
    
    return new_list;
}

List unzip(List *self) {
    
    List new_list;
    new_list.head = NULL;
    
    ListNodePtr preview = NULL;
    ListNodePtr current = self->head;
    
    while (current != NULL) {
        
        if (preview) {
            preview->next = current->next;
            
            if (new_list.head == NULL) {
                new_list.head = current;
            }
        }
        
        preview = current;
        current = current->next;
    }
    
    return new_list;
}

int median(List *self) {

    ListNodePtr median = self->head;
    ListNodePtr current = self->head;
    
    while (current != NULL && current->next != NULL && current->next->next != NULL) {
        median = median->next;
        current = current->next->next;
    }
        
    return median->data;
}

void print_list(List *self) {
    ListNodePtr current = self->head;
    while (current != NULL) {
        printf("%d", current->data);
        current = current->next;
        if (current != NULL) {
            printf("->");
        }
    }
    printf("\n");
}

void delete_list(List *self, int data) {
    ListNodePtr current = self->head;
    ListNodePtr prev = NULL;
    
    while (current != NULL) {
        if (current->data == data) {
            if (prev == NULL) {          // front of list
                self->head = current->next;
                free(current);
                current = self->head;
            } else {                    // middle of list
                prev->next = current->next;
                free(current);
                current = prev->next;
            }
        } else {
            prev = current;
            current = current->next;
        }
    }
}

void destroy_list(List *self) {
    ListNodePtr current = self->head;
    while (current != NULL) {
        ListNodePtr to_free = current;
        current = current->next;
        free(to_free);
    }
    self->head = NULL;
}
