template <class Data>
TreeNode<Data>::TreeNode(int level) 
  : right_(NULL), left_(NULL), level_(level)
{
}

template <class Data>
TreeNode<Data>::TreeNode(TreeNode<Data>* left, 
                         TreeNode<Data>* right, int level) 
  : right_(right), left_(left), level_(level)
{
}

template <class Data>
TreeNode<Data>::~TreeNode() {
}

template <class Data>
Data TreeNode<Data>::GetData() const {
  return data_;
}

template <class Data>
TreeNode<Data>* TreeNode<Data>::GetLeft() const {
  return left_;
}

template <class Data>
TreeNode<Data>* TreeNode<Data>::GetRight() const {
  return right_;
}

template <class Data>
int TreeNode<Data>::GetLevel() const {
  return level_;
}

template <class Data>
void TreeNode<Data>::SetData(const Data& data) {
  data_ = data;
}

template <class Data>
void TreeNode<Data>::SetRight(TreeNode<Data>* node) {
  right_ = node;
}

template <class Data>
void TreeNode<Data>::SetLeft(TreeNode<Data>* node) {
  left_ = node;
}
