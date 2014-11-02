#ifndef SKIP_LIST_H_
#define SKIP_LIST_H_

#include "skip_node.h"

/**************************************************
SKIPLISTS:
SkipList is a data structure that has sorted insertion,
arbitrary deletion, and search of average O(logn). Worst
case is O(n) (this is almost never happen because heights
are chosen at random). SkipList is an improvement on 
the standard linked list. Nodes now have a random height and
point to the next node of the height. This allows for the user
to jump around to find certain nodes. Implementation for
this data structure is relatively easy for the speed. Also, no
recursion is used.

If you want to use pointers for the Data, then you need
to specify how they pointers are compared. If you do this,
then you can comapre the dereferenced pointers, etc.

Also, don't forget to change the value of the Data if you're
using something different
***************************************************/

#define MAX_LIST_HEIGHT       10
#define TRUE                  1
#define FALSE                 0

#define POINTER

typedef uint8_t (*CompareFunction)(Data one, Data two);

typedef struct SkipList {
  SkipNode            head;
  // update_nodes are needed to adjust links after inserting/deleting
  SkipNode*           update_nodes[MAX_LIST_HEIGHT];
  // current level represents the height of the largest node in the list. 
  // The value should be an index and not a height.
  uint8_t             current_level;
  uint16_t            size;

  CompareFunction     LessThan;
  CompareFunction     LessThanOrEqual;
} SkipList;

// public functions //
void                  sl_Init(SkipList* list);
void                  sl_Insert(SkipList* list, Data data);
uint8_t               sl_Remove(SkipList* list, Data data);
uint8_t               sl_IsElement(SkipList* list, Data data);
uint8_t               sl_IsEmpty(const SkipList* list);
SkipNode*             sl_Search(SkipList* list, Data data);
Data                  sl_Pop(SkipList* list);
Data                  sl_Front(const SkipList* list);
void                  sl_Clear(SkipList* list);
void                  sl_Display(const SkipList* list);

// private functions //
static SkipNode*      sl_CreateNode(uint8_t height, Data data);
static uint8_t        sl_FlipCoin();
static uint8_t        sl_RandomLevel();
static uint8_t        sl_DefaultLessThan(Data one, Data two);     
static uint8_t        sl_DefaultLessThanOrEqual(Data one, Data two);     

#endif
