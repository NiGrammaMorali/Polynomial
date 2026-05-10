#pragma once

template<typename TKey, typename TValue>
class AVLTree {
private:
	struct map {
		TKey key;
		TValue value;
	};
	struct node {
		unsigned int height;
		map data;
		node* left;
		node* right;
		node(map k) {
			height = 1;
			data.key = k.key;
			data.value = k.value;
			left = right = nullptr;
		}
	};
	node* root;

	node* findNode(TKey _key, node* _node) {
		if (_node == nullptr || _key == _node->data.key) {
			return _node;
		}
		if (_key < _node->data.key) {
			return findNode(_key, _node->left);
		}
		return findNode(_key, _node->right);
	}
	void deleteNode(node* _node) {
		if (_node != nullptr) {
			deleteNode(_node->left);
			deleteNode(_node->right);
			delete _node;
		}
	}
	unsigned int height(node* _node) {
		return _node ? _node->height : 0;
	}
	int balanceFactor(node* _node) {
		return (height(_node->right) - height(_node->left));
	}
	void fixHeight(node* _node) {
		unsigned int h1 = height(_node->left);
		unsigned int h2 = height(_node->right);
		_node->height = (h1 > h2 ? h1 : h2);
		_node->height++;
	}
	node* rotateRight(node* _node) {
		node* point = _node->left;
		_node->left = point->right;
		point->right = _node;
		fixHeight(_node);
		fixHeight(point);
		return point;
	}
	node* rotateLeft(node* _node) {
		node* point = _node->right;
		_node->right = point->left;
		point->left = _node;
		fixHeight(_node);
		fixHeight(point);
		return point;
	}
	node* balance(node* _node) {
		fixHeight(_node);
		if (balanceFactor(_node) == 2) {
			if (balanceFactor(_node->right) < 0) {
				_node->right = rotateRight(_node->right);
			}
			return rotateLeft(_node);
		}
		if (balanceFactor(_node) == -2) {
			if (balanceFactor(_node->left) > 0) {
				_node->left = rotateLeft(_node->left);
			}
			return rotateRight(_node);
		}
		return _node;
	}
	node* insert(node* _node, map _map) {
		if (_node == nullptr) {
			return new node(_map);
		}
		if (_map.key < _node->data.key) {
			_node->left = insert(_node->left, _map);
		}
		else if (_map.key > _node->data.key) {
			_node->right = insert(_node->right, _map);
		}
		else {
			_node->data.value = _map.value;
		}
		return balance(_node);
	}
	node* findMin(node* _node) {
		return _node->left ? findMin(_node->left) : _node;
	}
	node* removeMin(node* _node) {
		if (_node->left == nullptr) {
			return _node->right;
		}
		_node->left = removeMin(_node->left);
		return balance(_node);
	}
	node* remove(node* _node, TKey k) {
		if (_node == nullptr) {
			return 0;
		}
		if (k < _node->data.key) {
			_node->left = remove(_node->left, k);
		}
		else if (k > _node->data.key) {
			_node->right = remove(_node->right, k);
		}
		else
		{
			node* q = _node->left;
			node* r = _node->right;
			delete _node;
			if (r == nullptr) { 
				return q; 
			}
			node* min = findMin(r);
			min->right = removeMin(r);
			min->left = q;
			return balance(min);
		}
		return balance(_node);
	}
	void printHorizontalTree(node* _node, int space) {
		if (_node == nullptr) {
			return;
		}

		const int COUNT = 5;
		space += COUNT;

		printHorizontalTree(_node->right, space);
		std::cout << '\n';
		for (int i = COUNT; i < space; i++) {
			std::cout << " ";
		}
		std::cout << _node->data.key << "(" << balanceFactor(_node) << ")" << '\n';

		printHorizontalTree(_node->left, space);
	}
	void printInOrder(node* _node) {
		if (_node == nullptr) {
			return;
		}
		printInOrder(_node->left);
		std::cout << "Key: " << _node->data.key
			<< " | Value: " << _node->data.value
			<< " | Height: " << _node->height
			<< " | Balance: " << balanceFactor(_node) << '\n';
		printInOrder(_node->right);
	}
public: 
	AVLTree() : root(nullptr) {}
	~AVLTree() {
		deleteNode(root);
	}
	TValue find(TKey _key) {
		node* point = findNode(_key, root);
		if (point == nullptr) {
			throw std::logic_error("There's no such element");
		}
		return point->data.value;
	}
	void insert(TKey _key, TValue _value) {
		map m;
		m.key = _key;
		m.value = _value;
		root = insert(root, m);
	}
	void remove(TKey _key) {
		root = remove(root, _key);
	}
	void printHorizontal() {
		std::cout << "=== Horizontal Tree ===" << '\n';
		printHorizontalTree(root, 0);
		std::cout << "=======================" << std::endl;
	}
	void printDetailed() {
		std::cout << "=== Tree (in-order) ===" << '\n';
		printInOrder(root);
		std::cout << "=======================" << std::endl;
	}
	TValue getRoot() {
		if (root == nullptr) {
			throw std::logic_error("There's no such element");
		}
		return root->data.value;
	}
};