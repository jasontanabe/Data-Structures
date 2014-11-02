#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "skip_list.h"
#include "skip_node.h"

// define POINTER in all files if you want to use a pointer
#define POINTER

#ifdef POINTER
uint8_t LessThan(Data one, Data two) {
  return *one < *two;
}
uint8_t LessThanOrEqual(Data one, Data two) {
  return *one <= *two;
}
#endif

int main() {
  SkipList list;
  sl_Init(&list);
#ifdef POINTER
  list.LessThan = &LessThan;
  list.LessThanOrEqual = &LessThanOrEqual;
#endif
  int values[50];
  int i = 0;
  srand(time(NULL));
  for (i = 0; i < 50; i++) {
    values[i] = rand() % 100;
#ifdef POINTER
    sl_Insert(&list, &values[i]);
#else
    sl_Insert(&list, values[i]);
#endif
  }
  sl_Display(&list);

  return 0;
}

