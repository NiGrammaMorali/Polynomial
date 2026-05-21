#pragma once
#include <vector>

template<typename T>
class SkipList {
private:
	struct node {
        T data;
		size_t level;
		std::vector<node*> next;
		node(const T& _data, size_t _lvl) : data(_data), level(_lvl), next(_lvl + 1) {}
	};
	node* head;
	size_t size;
	size_t max_level;
	const double probability = 0.5;
	double random(double min, double max)
	{
		double f = (double)rand() / RAND_MAX;
		return min + f * (max - min);
	}
	size_t randomLevel() {
		size_t lvl = 0;
		while (random(0.0, 1.0) < probability && lvl < max_level) {
			lvl++;
		}
		return lvl;
	}
public:
    SkipList() : size(0), max_level(0) {
        head = new node(T{}, 0);
    }
    SkipList(size_t _max) : size(0), max_level(_max) {
        head = new node(T{}, max_level);
    }
    ~SkipList() {
        node* curr = head->next[0];
        while (curr) {
            node* nxt = curr->next[0];
            delete curr;
            curr = nxt;
        }
        delete head;
    }
    void insertElement(const T& value) {
        std::vector<node*> update(max_level + 1, head);
        node* curr = head;
        for (int i = max_level; i >= 0; i--) {
            while (curr->next[i] && curr->next[i]->data < value) {
                curr = curr->next[i];
            }
            update[i] = curr;
        }
        if (curr->next[0] && curr->next[0]->data == value) {
            return;
        }
        size_t new_level = randomLevel();
        node* new_node = new node(value, new_level);
        for (size_t i = 0; i <= new_level; i++) {
            new_node->next[i] = update[i]->next[i];
            update[i]->next[i] = new_node;
        }
        size++;
    }
    bool searchElement(const T& value) {
        std::vector<node*> update(max_level + 1, head);
        node* curr = head;
        for (int i = max_level; i >= 0; i--) {
            while (curr->next[i] && curr->next[i]->data < value) {
                curr = curr->next[i];
            }
        }
        curr = curr->next[0];
        if (curr && curr->data == value) {
            return true;
        }
        return false;
    }
    void deleteElement(const T& value) {
        node* curr = head;
        std::vector<node*> update(max_level + 1, head);
        for (int i = max_level; i >= 0; i--) {
            while (curr->next[i] && curr->next[i]->data < value) {
                curr = curr->next[i];
            }
            update[i] = curr;
        }
        curr = curr->next[0];
        if (curr != nullptr && curr->data == value) {
            for (size_t i = 0; i <= curr->level; i++) {
                if (update[i]->next[i] == curr) {
                    update[i]->next[i] = curr->next[i];
                }
            }
            size--;
        }
    }
    void print()
    {
        cout << "\n*****Skip List*****" << "\n";
        for (int i = 0; i <= max_level; i++)
        {
            node* _node = head->next[i];
            cout << "Level " << i << ": ";
            while (_node != NULL)
            {
                cout << _node->data << " ";
                _node = _node->next[i];
            }
            cout << "\n";
        }
    }
    size_t getSize() {
        return size;
    }
};
