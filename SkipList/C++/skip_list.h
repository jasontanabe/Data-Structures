#ifndef SKIP_LIST_H_
#define SKIP_LIST_H_

#include <vector>
#include <time.h>
#include <stdlib.h>
#include "skip_node.h"

// current implementation allows for any height and just hopes the
// random height comes out something reasonable

using namespace std;

template <class Data>
class SkipList {
public:
  typedef bool (*CompareFunction)(const Data& data1, const Data& data2);

                                    SkipList(int max_level);
                                    ~SkipList();

  void                              Insert(const Data& data);				
  void                              Remove(const Data& data);
  SkipNode<Data>*                   Search(const Data& data);
  void                              Display() const;

  // change the way the values are compared by using function pointers
  // if you don't set it, it'll use the default ones
  void                              SetLessThanFunction(CompareFunction func);
  void                              SetLessOrEqualThanFunction(CompareFunction 
                                                               func);
private:
  void                              Init();

  int                               RandomLevel() const;
  bool                              FlipCoin() const;

  // default functions needed for "<" and "<="
  static bool                       DefaultLessThanOrEqual(const Data& data1,
                                                           const Data& data2);
  static bool                       DefaultLessThan(const Data& data1,
                                                    const Data& data2);


  SkipNode<Data>                    head_;
  vector<SkipNode<Data>*>           update_nodes_;
  int                               current_level_;
  int                               max_height_;

  // using function pointers to specify how data is compared
  // this is needed if you want to compare pointers in a different way (for
  // example if you need to dereference it)
  CompareFunction                   LessThan;
  CompareFunction                   LessThanOrEqual;
    
};

#include "skip_list_temp.h"

#endif
