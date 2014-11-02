#ifndef SKIP_NODE_H_
#define SKIP_NODE_H_

/*************************************************************
SKIPNODE:
SkipNode is the struct that is used for nodes in the skip list.
Each node consists of the data, an array of nodes to all of the
next nodes in the list of the same height, and the height of the
node. 
**************************************************************/
#define POINTER

// define the type of data you want
#ifdef POINTER
typedef int* Data;
#else
typedef int Data;
#endif

typedef struct SkipNodeT {
  Data                        data;
  struct SkipNodeT**          forward;
  uint8_t                     height;
} SkipNode;

void                          sn_Init(SkipNode* node, uint8_t height, 
                                      Data data);
#endif
