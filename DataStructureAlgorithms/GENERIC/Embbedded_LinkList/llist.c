#include <stdlib.h>
#include <stdbool.h>
#include "llist.h"



/* Function Definitions */


HLLIST create_llist(void)
{
    HLLIST hllist;
    if((hllist = (HLLIST)malloc(sizeof(LLIST))) == NULL)
        return NULL; // Memory allocation failed
    hllist->head.next = &hllist->head; // Initialize head's next to point to itself
    hllist->head.prev = &hllist->head; // Initialize head's prev to point to itself
    hllist->count = 0; // Initialize count to zero
    return hllist;     // Return the created linked list handle
}


NODE* insert_next(HLLIST hllist, NODE* node, NODE* new_node)
{
    if(hllist == NULL || node == NULL || new_node == NULL)
        return NULL; // Invalid parameters 
    new_node->next = node->next; // Set new_node's next to node's next
    new_node->prev = node; // Set new_node's prev to node
    node->next->prev = new_node; // Set the next node's prev to new_node
    node->next = new_node; // Set node's next to new_node
    ++hllist->count; // Increment the count of the linked list
    return new_node; // Return the newly inserted node

}
NODE* insert_prev(HLLIST hllist, NODE* node, NODE* new_node)
{
    if(hllist == NULL || node == NULL || new_node == NULL)
        return NULL; // Invalid parameters
    new_node->prev = node->prev; // Set new_node's prev to node's prev
    new_node->next = node; // Set new_node's next to node
    node->prev->next = new_node; // Set the previous node's next to new_node
    node->prev = new_node; // Set node's prev to new_node
    ++hllist->count; // Increment the count of the linked list
    return new_node; // Return the newly inserted node
}
NODE* remove_node(HLLIST hllist, NODE* node)
{
    if(hllist == NULL || node == NULL || node == &hllist->head)
        return NULL; // Invalid parameters or trying to remove head
    node->prev->next = node->next; // Set the previous node's next to the next node
    node->next->prev = node->prev; // Set the next node's prev to the previous node
    --hllist->count; // Decrement the count of the linked list
    return node; // Return the removed node
}
NODE* add_tail(HLLIST hllist, NODE *new_node)
{
    if(hllist == NULL || new_node == NULL)
        return NULL; // Invalid parameters
    return insert_prev(hllist, &hllist->head, new_node); // Insert new_node before the head
}
NODE* add_head(HLLIST hllist, NODE *new_node)
{
    if(hllist == NULL || new_node == NULL)
        return NULL; // Invalid parameters
    return insert_next(hllist, &hllist->head, new_node); // Insert new_node after the head
}
NODE* getp_item(HLLIST hllist, size_t index)
{
    if(hllist == NULL || index >= hllist->count)
        return NULL; // Invalid parameters or index out of bounds
    NODE *node = hllist->head.next; // Start from the head's next node
    for(size_t i = 0; i < index; ++i)
        node = node->next; // Traverse to the desired index
    return node; // Return the node at the specified index
}
bool walk_llist(HLLIST hllist, bool (*proc)(NODE *))
{
    if(hllist == NULL || proc == NULL)
        return false; // Invalid parameters
    NODE *node;
    FOR_EACH(hllist, node)
        if(!proc(node)) // Call the processing function on each node
            return false; // If processing returns false, stop walking
    return true; // Successfully walked through the list
}
bool walk_llist_rev(HLLIST hllist, bool (*proc)(NODE *))
{
    if(hllist == NULL || proc == NULL)
        return false; // Invalid parameters
    NODE *node;
    FOR_EACH_REV(hllist, node)
        if(!proc(node)) // Call the processing function on each node in reverse order
            return false; // If processing returns false, stop walking
    return true; // Successfully walked through the list in reverse
}
void clear_llist(HLLIST hllist)
{
    if(hllist == NULL)
        return; // Invalid parameter
    NODE *node, *next_node;
    FOR_EACH(hllist, node) {
        next_node = node->next; // Store the next node
        remove_node(hllist, node); // Remove the current node
    }
    hllist->count = 0; // Reset the count to zero
}
void destroy_llist(HLLIST hllist)
{
    if(hllist == NULL)
        return; // Invalid parameter
    clear_llist(hllist); // Clear the linked list
    free(hllist); // Free the memory allocated for the linked list structure
}

