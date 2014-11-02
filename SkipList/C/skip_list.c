#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "skip_node.h"
#include "skip_list.h"

/*************************************************************************    
 * Function: sl_Init
 * ------------------
 * initializes the skip list. Sets the head nodes height and initializes all
 * forward nodes to NULL. Also initializes the size and current level. Seeds
 * the rand function
 *
 * list: input skip list to be init
 * returns: nothing
 *************************************************************************/
void sl_Init(SkipList* list) {
  srand((size_t)time(NULL));
#ifdef POINTER
  sn_Init(&(list->head), MAX_LIST_HEIGHT, NULL);
#else
  Data data;
  sn_Init(&(list->head), MAX_LIST_HEIGHT, data);
#endif
  list->size = 0;
  list->current_level = 0;
  list->LessThan = sl_DefaultLessThan;  
  list->LessThanOrEqual = sl_DefaultLessThanOrEqual;  
}
/*************************************************************************    
 * Function: sl_Insert
 * ------------------
 * Inserts data into the list in sorted order. This is done by first finding 
 * update nodes. Update nodes are the skip nodes that are right before the place 
 * we should place the new node. This is done so we can initialize the new 
 * nodes forward values to the update nodes next values. Then we can set the 
 * update nodes next values to the new node.
 *
 * list: input skip list
 * data: data to be used for the new skip node
 * returns: nothing
 *************************************************************************/
void sl_Insert(SkipList* list, Data data) {
  SkipNode* node = &(list->head);
  int16_t i = list->current_level;
  uint8_t level = sl_RandomLevel();
  for (i; i >= 0; --i) {
    while (node->forward[i] != NULL && list->LessThan(node->forward[i]->data, 
           data)) {
      node = node->forward[i];
    }
    list->update_nodes[i] = node;
  }
  node = node->forward[0];
  if (level > list->current_level) {
    for (i = list->current_level + 1; i <= level; ++i) {
      list->update_nodes[i] = &(list->head);
    }
    list->current_level = level;
  }
  node = sl_CreateNode(level + 1, data);
  for (i = 0; i <= level; ++i) {
    node->forward[i] = list->update_nodes[i]->forward[i];
    list->update_nodes[i]->forward[i] = node;
  }
  list->size++;
}
/*************************************************************************    
 * Function: sl_Remove
 * ------------------
 * Find and remove a node from the skip list. Process is similar to inserting.
 * We first create the update nodes. This is done so we can initalize the 
 * previous nodes forward values to the node we are deleting next values.
 *
 * list: input skip list
 * data: key value to find the correct skip node
 * returns: true if we delete the node and false if we can't find it
 *
 * NOTE: the method for finding the right node accounts for duplicate data. If
 * the data is the same, then we need to look for the exact node (pointers need
 * to be pointing to the same value).
 *************************************************************************/
uint8_t sl_Remove(SkipList* list, Data data) {
  SkipNode* node = &(list->head);
  SkipNode* temp_node = NULL;
  uint8_t found = 0;
  int8_t i = list->current_level;
  uint8_t node_height = 0;
  for (i; i >= 0; --i) {
    temp_node = node;
    while (node->forward[i] != NULL && 
           list->LessThanOrEqual(node->forward[i]->data, data)) {
      if (node->forward[i]->data == data) {
        found = TRUE;
        break;
      }
      node = node->forward[i];
    }
    if (!found) {
      node = temp_node;
    }
    list->update_nodes[i] = node;
    found = FALSE;
  }
  node = node->forward[0];
  if (node == NULL || node->data != data) {
    return FALSE;
  }
  node_height = node->height;
  for (i = 0; i < node_height; ++i) {
    list->update_nodes[i]->forward[i] = node->forward[i];
  }
  free(node);
  list->size--;
  if ((node_height - 1) == list->current_level) {
    while (list->current_level > 0 && 
           list->head.forward[list->current_level] == NULL) {
      list->current_level--;
    }
  }
  return TRUE;
}
/*************************************************************************    
 * Function: sl_IsElement
 * ------------------
 * Checks to see if there is a node in the skip list with the given data.
 *
 * list: input skip list
 * data: key value to find the correct skip node
 * returns: true if we can find the node and false if not
 *************************************************************************/
uint8_t sl_IsElement(SkipList* list, Data data) {
  return (sl_Search(list, data) != NULL);
}
/*************************************************************************    
 * Function: sl_IsEmpty
 * ------------------
 * Check if list is epty
 *
 * list: input skip list
 * returns: true if empty, false otherwise
 *************************************************************************/
uint8_t sl_IsEmpty(const SkipList* list) {
  return list->size == 0;
}
/*************************************************************************    
 * Function: sl_Search
 * ------------------
 * Look for a node with the given data
 *
 * list: input skip list
 * data: data to find correct node
 * returns: the node if found, NULL otherwise
 *************************************************************************/
SkipNode* sl_Search(SkipList* list, Data data){ 
  SkipNode* node = &(list->head);
  int8_t i = list->current_level;
  for (i; i >= 0; --i) {
    while (node->forward[i] != NULL && 
           list->LessThanOrEqual(node->forward[i]->data, data)) {
      if (node->forward[i]->data == data) {
        break;
      } 
      node = node->forward[i];
    }
  }
  node = node->forward[0];
  if (node != NULL && node->data == data) {
    return node;
  }
  return NULL;
}
/*************************************************************************    
 * Function: sl_Pop
 * ------------------
 * Get the data of the first element in the list and delete the node.
 *
 * list: input skip list
 * returns: data of the first node, NULL if the list is empty
 *************************************************************************/
Data sl_Pop(SkipList* list) {
  SkipNode* node = list->head.forward[0];
  Data data = node->data;
  int8_t i = 0;
  if (sl_IsEmpty(list)) {
    printf("empty list\n");
#ifdef POINTER
    return NULL;
#else
    Data data;
    return data;
#endif 
  }
  for (i; i < node->height; ++i) {
    list->head.forward[i] = node->forward[i];
  }
  free(node);
  list->size--;
  return data;
}
/*************************************************************************    
 * Function: sl_Front
 * ------------------
 * Get the data of the first element in the list.
 *
 * list: input skip list
 * returns: data of the first node, NULL if the list is empty
 *************************************************************************/
Data sl_Front(const SkipList* list) {
  SkipNode* node = list->head.forward[0];
  if (sl_IsEmpty(list)) {
    printf("empty list\n");
#ifdef POINTER
    return NULL;
#else
    Data data;
    return data;
#endif
  }
  return node->data;
}
/*************************************************************************    
 * Function: sl_Clear
 * ------------------
 * Deletes all the nodes in the list. Sets the heads forward values to NULL and
 * initializes the current_level back to 0.
 *
 * list: input skip list
 * returns: nothing
 *************************************************************************/
void sl_Clear(SkipList* list) {
  SkipNode* node = list->head.forward[0];
  SkipNode* prev = node;
  int8_t i = 0;
  for (i; i <= list->current_level; ++i) {
    list->head.forward[i] = NULL;
  }
  while (node != NULL) {
    node = node->forward[0];
    free(prev);
    prev = node;
  }
  list->size = 0;
  list->current_level = 0;
}
/*************************************************************************    
 * Function: sl_Display
 * ------------------
 * Prints out all the nodes in the list, uses the MapNode display function
 *
 * list: input skip list
 * returns: nothing
 *************************************************************************/
void sl_Display(const SkipList* list) {
  const SkipNode* node = &(list->head);
  while (node->forward[0] != NULL) {
//    Display(node->forward[0]->data);
#ifdef POINTER
    printf("%d\n", *(node->forward[0]->data));
#else
    printf("%d\n", (node->forward[0]->data));
#endif
    node = node->forward[0];
  }
}

/* private functions */
/*************************************************************************    
 * Function: sl_CreateNode
 * ------------------
 * Used to create and initialize a new skip node.
 *
 * height: height of the newly created node
 * data: data of the newly created node
 * returns: a pointer to the new node
 *************************************************************************/
SkipNode* sl_CreateNode(uint8_t height, Data data) {
  SkipNode* node = (SkipNode*)malloc(sizeof(SkipNode));
  sn_Init(node, height, data);
  return node;
}
/**************************************************************************    
 * Function: sl_FlipCoin
 * ------------------
 * Simulates flipping a coin. Used for randomizing the height of the nodes
 *
 * returns: a random 0 or 1
 *************************************************************************/
uint8_t sl_FlipCoin() {
  return (rand()%2 == 0);
}
/*************************************************************************    
 * Function: sl_RandomLevel
 * ------------------
 * Flips a coin and randomly gets a given level. Makes sure that the level is
 * not greater than the max height - 1.
 *
 * returns: level of newly created node
 * 
 * NOTE: you should add one if you want to get a height.
 *************************************************************************/
uint8_t sl_RandomLevel() {
  uint8_t level = 0;
  for (level; sl_FlipCoin(); ++level);
  if (level > MAX_LIST_HEIGHT - 1) {
    return MAX_LIST_HEIGHT - 1;
  }
  return level;
}

uint8_t sl_DefaultLessThan(Data one, Data two) {
  return one < two;
}

uint8_t sl_DefaultLessThanOrEqual(Data one, Data two) {
  return one <= two;
}
