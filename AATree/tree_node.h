#ifndef TREE_NODE_H_
#define TREE_NODE_H_

template<typename T>
struct IsPointer { static const bool value = false; };    
template<typename T>
struct IsPointer<T*> { static const bool value = true; };

using namespace std;

template <class Data>
class TreeNode {
public:
                                  TreeNode(int level);
                                  TreeNode(TreeNode<Data>* left,
                                           TreeNode<Data>* right,
                                           int level);
                                  ~TreeNode();

  Data                            GetData() const;
  TreeNode<Data>*                 GetLeft() const;
  TreeNode<Data>*                 GetRight() const;
  int                             GetLevel() const;

  void                            SetData(const Data& data);
  void                            SetRight(TreeNode<Data>* node);
  void                            SetLeft(TreeNode<Data>* node);

private:

  int                             level_;
  Data                            data_;
  TreeNode<Data>*                 left_;
  TreeNode<Data>*                 right_;
};

#include "tree_node_temp.h"

#endif
