#ifndef SKIP_NODE_H_
#define SKIP_NODE_H_

#include <vector>

// stand-alone helper struct
template<typename T>
struct IsPointer { static const bool value = false; };    
template<typename T>
struct IsPointer<T*> { static const bool value = true; };

using namespace std;

template <class Data>
class SkipNode {
public:
																	SkipNode(int height, Data data);
																	~SkipNode();

	SkipNode<Data>*									GetForward(int index) const;
	Data														GetData() const;
	int															GetHeight() const;

	void														SetForward(int index, SkipNode<Data>* node);
private:
	void														Init();

	Data														data_;
	vector<SkipNode<Data>*>					forward_;
	int															height_;
};

#include "skip_node_temp.h"

#endif