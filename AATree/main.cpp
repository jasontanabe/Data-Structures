#include <iostream>
#include "tree_node.h"

int main() {
  TreeNode<int> left(1);  
  left.SetData(10);
  TreeNode<int> right(1);  
  right.SetData(20);
  TreeNode<int> parent(&left, &right, 2);
  parent.SetData(30);
  std::cout << "Parent data is: ";
  std::cout << parent.GetData() << std::endl;
  std::cout << "Left data: ";
  std::cout << parent.GetLeft()->GetData() << std::endl;
  std::cout << "right data: ";
  std::cout << parent.GetRight()->GetData() << std::endl;

  return 0;
}
