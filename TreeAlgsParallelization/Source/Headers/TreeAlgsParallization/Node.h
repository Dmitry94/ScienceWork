#ifndef NODE_H
#define NODE_H

template <typename T>
struct Node {
	int level;
	const Node *parent;
	T value;
	Node(T val, const Node *parent, int level = 0) {
		value = val;
		this->parent = parent;
		this->level = level;
	}
	~Node() {}
};

#endif /* NODE_H */