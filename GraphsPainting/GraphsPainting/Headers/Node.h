#ifndef Node_H
#define Node_H

#include <list>

template <typename T>
struct Node {
	int level;
	const Node *parent;
	std::list <Node *> sons;
	typedef typename std::list <Node *>::iterator sons_iterator;
	T value;
	Node(T val, const Node *parent, int level = 0) {
		value = val;
		this->parent = parent;
		this->level = level;
	}
	~Node() {
		for (sons_iterator it = sons.begin(); it != sons.end(); it++)
			delete (*it);
	}
	std::string to_string() {
		std::string ans = "";
		for (sons_iterator it = sons.begin(); it != sons.end(); it++)
			ans += (*it)->to_string() + " ";
		return std::to_string(value) + " " + ans;
	}
};

#endif /* Node_H */