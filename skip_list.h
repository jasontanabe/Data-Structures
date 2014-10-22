#ifndef SKIP_LIST_H_
#define SKIP_LIST_H_

#include <vector>
#include <time.h>
#include <stdlib.h>
#include "skip_node.h"

using namespace std;
template <class Data>
class SkipList {
public:
																		SkipList(int max_level);
																		~SkipList();

	void															Insert(const Data& data);				
	void															Remove(const Data& data);
	SkipNode<Data>*										Search(const Data& data);
	void															Display() const;
private:
	void															Init();

	int																RandomLevel() const;
	bool															FlipCoin() const;

	SkipNode<Data>										head_;
	vector<SkipNode<Data>*>						update_nodes_;
	int																current_level_;
	int																max_height_;
};

#include "skip_list_temp.h"

#endif