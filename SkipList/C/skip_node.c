#include <stdio.h>
#include <stdlib.h>
#include "skip_node.h"

/*************************************************************************    
 * Function: sn_Init
 * ------------------
 * Initializes SkipNode with a given height and given data. Dynamically
 * allocated memory for the height of the SkipNode.
 *
 * node: SkipNode to be initalized
 * height: height of the node to be initalized
 * data: data that is the be inputted into the node
 * returns: nothing
 *************************************************************************/
void sn_Init(SkipNode* node, uint8_t height, Data data) {
  int i = 0;
  node->height = height;
  node->data = data;
  node->forward = (SkipNode**)malloc(height*sizeof(SkipNode*));
  for (i; i < height; ++i) {
    node->forward[i] = NULL;
  }
}
