template <class Data>
SkipList<Data>::SkipList(int max_level) 
  : current_level_(0), max_height_(max_level), head_(max_level, 0)
{
  Init();		
}

template <class Data>
SkipList<Data>::~SkipList() {
}

template <class Data>
void SkipList<Data>::Insert(const Data& data) {
  SkipNode<Data>* node = &head_;
  for (int i = current_level_; i >= 0; --i) {
    while (node->GetForward(i) != NULL && 
           LessThan(node->GetForward(i)->GetData(),data)) {
      node = node->GetForward(i);
    }
    update_nodes_[i] = node;
  }
  int level = RandomLevel();
  if (level >= max_height_) {
    level = max_height_ - 1;
  }
  if (level > current_level_) {
    for (int i = (current_level_ + 1); i <= level; ++i) {
      update_nodes_[i] = &head_;
    }
    current_level_ = level;
  }
  node = new SkipNode<Data>(level + 1, data);
  for (int i = 0; i <= level; ++i) {
    node->SetForward(i, update_nodes_[i]->GetForward(i));
    update_nodes_[i]->SetForward(i, node);
  }
}

template <class Data>
void	SkipList<Data>::Remove(const Data& data) {
  SkipNode<Data>* node = &head_;
  SkipNode<Data>* tempNode = NULL;
  bool found = false;
  for (int i = current_level_; i >= 0; --i) {
    tempNode = node;
    while (node->GetForward(i) != NULL && 
           LessThanOrEqual(node->GetForward(i)->GetData(), data)) {
      if (node->GetForward(i)->GetData() == data) {
        found = true;
        break;
      }
      node = node->GetForward(i);
    }
    if (!found) {
      node = tempNode;
    }
    update_nodes_[i] = node;
    found = false;
  }
  node = node->GetForward(0);
  if (node == NULL || node->GetData() != data) {
#ifdef DEBUG
    std::cout << "Remove: could not find data" << std::endl;
#endif
    return;
  }
  int node_height = node->GetHeight();
  for (int i = 0; i < node_height; ++i) {
    update_nodes_[i]->SetForward(i, node->GetForward(i));
  }
  delete node;
  if ((node_height - 1) == current_level_) {
    while (current_level_ > 0 && head_.GetForward(current_level_) == NULL) {
      current_level_--;
    }
  }
}

template <class Data>
SkipNode<Data>* SkipList<Data>::Search(const Data& data) {
  SkipNode<Data>* node = &head_;
  for (int i = current_level_; i >= 0; --i) {
    while (node->GetForward(i) != NULL && 
           LessThanOrEqual(node->GetForward(i)->GetData(), data)) {
      if (node->GetForward(i)->GetData() == data) {
        break;
      }
      node = node->GetForward(i);			
    }
  }
  node = node->GetForward(0);
  if (node != NULL && node->GetData() == data) {
    return node;
  } 
  return NULL;
}

template <class Data>
void SkipList<Data>::Display() const {
  const SkipNode<Data> * node = &head_;
  while (node->GetForward(0) != NULL) {
    std::cout << node->GetForward(0)->GetData() << std::endl;
    node = node->GetForward(0);
  }
}

template <class Data>
void SkipList<Data>::SetLessThanFunction(CompareFunction func) {
  LessThan = func;  
}

template <class Data>
void SkipList<Data>::SetLessOrEqualThanFunction(CompareFunction func) {
  LessThanOrEqual = func;  
}

///////////////////////
// private functions //
///////////////////////

template <class Data>
void SkipList<Data>::Init() {
  srand(static_cast<size_t>(time(NULL)));
  update_nodes_.resize(max_height_);
  for (int i = 0; i < max_height_; ++i) {
    head_.SetForward(i, NULL);
    update_nodes_[i] = &head_;
  }
  LessThan = &DefaultLessThan;
  LessThanOrEqual = &DefaultLessThanOrEqual;
}

template <class Data>
bool SkipList<Data>::FlipCoin() const {
  return (rand()%2 == 0);
}

template <class Data>
int SkipList<Data>::RandomLevel() const {
  int level = 0;
  for (level; FlipCoin(); ++level);
  return level;
}

template <class Data>
bool SkipList<Data>::DefaultLessThan(const Data& data1,
                                     const Data& data2) {
  return data1 < data2;
}

template <class Data>
bool SkipList<Data>::DefaultLessThanOrEqual(const Data& data1,
                                            const Data& data2) {
  return data1 <= data2;
}
