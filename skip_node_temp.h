template <class Data>
SkipNode<Data>::SkipNode(int height, Data data) 
  :	data_(data), height_(height)
{
  Init();
}

template <class Data>
SkipNode<Data>::~SkipNode() {
}

template <class Data>
Data SkipNode<Data>::GetData() const {
  return data_;
}

template <class Data>
SkipNode<Data>* SkipNode<Data>::GetForward(int index) const {
  if (index >= height_) {
    return NULL;
  }
  return forward_[index];
}

template <class Data>
int SkipNode<Data>::GetHeight() const {
  return height_;
}

template <class Data>
void SkipNode<Data>::SetForward(int index, SkipNode<Data>* node) {
  if (index >= height_) {
    return;
  }
  forward_[index] = node;
}

template <class Data>
void SkipNode<Data>::Init() {
  forward_.resize(height_);
  for (int i = 0; i < height_; ++i) {
    forward_[i] = NULL;
  }
}
