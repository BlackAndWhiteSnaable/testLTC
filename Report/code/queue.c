#include "defs.h"

/// Add element to queue
void push_queue(Queue **head, Nodes *new_node)
{
  // Allocate new queue element struct in memory
  Queue *tmp;
  tmp = (Queue *)malloc(sizeof(Queue))

  // queue is empty, insert new Queue element as head
  if (!*head) {
    *head = tmp; // Point head to the new queue element
    (*head)->next = NULL;

  // First element in queue has higher movecost than the new element
  // So insert new element as first element, and update next pointer
  } else if((*head)->node->movecost > new_node->movecost) {
  tmp->next = *head;
  *head = tmp;

  // Insert new element before element with higher movecost value
  } else {
    Queue *cur;
    cur = *head;
    while
    (cur->next != NULL &&
     cur->next->node->movecost <= new_node->movecost) {
    cur = cur->next; // Next node
  }
    tmp->next = cur->next;    // set next pointer to current head
    cur->next = tmp;          // set head queue element to new element
  }
  // Store pointer to node in the new queue element
  tmp->node = new_node;
//  print_queue(head);
}

/// Print number of elements in queue and their values
void print_queue(Queue *head) {
    if(!head)
    {
        printf("[WARN]\tPrint what? Queue is empty\n");
    }
    else
    {
        Queue *cur; // pointer to node currently being traversed
        int i=1; // count queue element position

        for (cur = head; cur != NULL; cur = cur->next)
        {
            printf(
              "[INFO]\t%d. Queue element is
              node[%d][%d] with movecost: %d\n",
			        i,
              cur->node->position.x,
              cur->node->position.y,
              cur->node->movecost
            );
            i++;
        }
    }
    printf("\n");
}

/// Remove one element from head of queue
Nodes *pop(Queue **head)
{
    if (!*head) {
        printf("[WARN]\tNothing to pop, queue is empty\n");

        return NULL;
    } else {
        Nodes *node;
        node = (*head)->node;

        Queue *tmp;               // tmp pointer to struct
        tmp = (*head)->next;      // set pointer to 2nd element
        free(*head);              // free memory for 1st element
        *head = tmp;              // set 2nd element to 1st element

        return node;
    }
}
