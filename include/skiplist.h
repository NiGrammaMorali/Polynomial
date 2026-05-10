#pragma once
#include <memory>

template<typename T>
class SkipList {
private:
	struct node {
        T data;
		size_t level;
		std::unique_ptr<node*[]> pointers;
		node(const T& _data, size_t _lvl) : data(_data), level(_lvl), pointers(std::make_unique<node*[]>(_lvl)) {}
	};
	node* prehead;
	size_t size;
	size_t max_level;
	double probability;
	double random(double min, double max)
	{
		double f = (double)rand() / RAND_MAX;
		return min + f * (max - min);
	}
	size_t randomLevel() {
		size_t lvl = 0;
		while (random(0.0, 1.0) < probability && lvl <= max_level) {
			lvl++;
		}
		return lvl;
	}
    node* insert_item(T value)
    {
        if (prehead->pointers[0] == nullptr)
        {
            node* result = new node(value, max_level);
            for (size_t i = 0; i < result->max_level;++i)
                prehead->pointers[i] = result;
            return result;
        }
        std::vector<node*> update(max_level, prehead);
        node* current = prehead;
        for (int i = max_level - 1; i >= 0; --i) {
            while (current->pointers[i] && current->pointers[i]->data < value) {
                current = current->pointers[i];
            }
            update[i] = current;
        }
        size_t new_level = randomLevel();
        node* result = new node(value, new_level);
        for (size_t i = 0; i < new_level; ++i) {
            result->pointers[i] = update[i]->pointers[i];
            update[i]->pointers[i] = result;
        }
        return result;
    }
public:
	SkipList() : first(nullptr), size(0), probability(0.5);
    ~SkipList() {
        node* current = prehead;
        while (current != nullptr) {
            node* next = current->pointers[0];
            delete current;
            current = next;
        }
    }
    void insert(const T& value) {
        node* new_node = insert_item(value);
        if (new_node->data == value) {
            new_node->data = value;
        }
        else {
            size++;
        }
    }
};