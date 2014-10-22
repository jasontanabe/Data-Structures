#include <iostream>
#include <time.h>
#include <stdlib.h>
#include "skip_node.h"
#include "skip_list.h"

int main() {
	SkipList<int> list(15);
	srand(static_cast<size_t>(time(NULL)));
	for (int i = 0; i < 100; ++i) {
		list.Insert(rand()%100);
	}
	for (int i = 0; i < 10; ++i) {
		list.Remove(rand()%100);
	}

	SkipNode<int>* node = list.Search(30);
	std::cout << "Searching for value 30:" << std::endl;
	if (node != NULL) {
		std::cout << "node found: " << node->GetData() << std::endl;
	} else {
		std::cout << "node not found " << std::endl;
	}
	std::cout << "Searching for value 50:" << std::endl;
	node = list.Search(50);
	if (node != NULL) {
		std::cout << "node found: " << node->GetData() << std::endl;
	} else {
		std::cout << "node not found " << std::endl;
	}
	list.Display();
	return 0;
}
