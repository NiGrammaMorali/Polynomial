#pragma once
#include <iostream>
#include <vector>

using namespace std;

template <typename T>
class ForwardList {
private:
	struct Node {
		Node* next;
		T data;
		Node(const T& val, Node* node) : data(val), next(node) {}
	};

	Node* First;
	size_t Size;

	Node* ToPos(size_t position) {
		if (position >= Size) {
			throw out_of_range("The index is out of range");
		}
		Node* ind = First;
		for (size_t i = 0; i < position; i++) {
			ind = ind->next;
		}
		return ind;
	}
	const Node* ToPos(size_t position) const {
		if (position >= Size) {
			throw out_of_range("The index is out of range");
		}
		Node* ind = First;
		for (size_t i = 0; i < position; i++) {
			ind = ind->next;
		}
		return ind;
	}
public:
	ForwardList() : First(nullptr), Size(0) {}
	ForwardList(const ForwardList& L) : First(L.First), Size(L.Size) {
		if (L.First == nullptr) return;
		Node* New = First = new Node{ *L.First };
		for (; New->next != nullptr; New = New->next) {
			New->next = new Node{ *New->next };
		}
	}
	ForwardList(ForwardList&& L) noexcept : First(L.First) {
		L.First = nullptr;
		swap(*this, L);
	}
	~ForwardList() {
		Node* pointer;
		while (First != nullptr) {
			pointer = First;
			First = First->next;
			delete pointer;
		}
	}
	ForwardList& operator=(const ForwardList& L) {
		if (this != &L) {
			ForwardList tmp(L);
			swap(*this, tmp);
		}
		return *this;
	}
	ForwardList& operator=(ForwardList&& L) noexcept {
		swap(*this, L);
		return *this;
	}
	T& Front() noexcept {
		return First->data;
	}
	void PushFront(const T& val) {
		Node* node = new Node{ val, First };
		First = node;
		Size++;
	}
	void PopFront() {
		if (this->IsEmpty()) {
			throw out_of_range("The list is empty");
			return;
		}
		Node* pointer = First;
		First = First->next;
		delete pointer;
		Size--;
	}
	const T& At(size_t position) const {
		const Node* pointer = ToPos(position);
		return pointer->data;
	}
	T& At(size_t position) {
		Node* pointer = ToPos(position);
		return pointer->data;
	}
	const T& operator[](size_t position) const {
		const Node* pointer = ToPos(position);
		return pointer->data;
	}
	T& operator[](size_t position) {
		Node* pointer = ToPos(position);
		return pointer->data;
	}
	void PushAfter(size_t position, const T& value) {
		Node* pointer = ToPos(position);
		Node* NewNode = new Node{ value, pointer->next };
		pointer->next = NewNode;
		Size++;
	}
	void EraseAfter(size_t position) {
		if (IsEmpty()) {
			throw out_of_range("The list is empty");
		}
		if (position >= Size - 1) {
			throw out_of_range("There's no value after that position");
		}
		if (Size > 1) {
			Node* pointer = ToPos(position);
			Node* toDelete = pointer->next;
			pointer->next = toDelete->next;
			delete toDelete;
			Size--;
		}
	}
	size_t size() const noexcept {
		return Size;
	}
	bool IsEmpty() const noexcept {
		return (Size == 0);
	}
	bool operator==(const ForwardList& L) const {
		if (this->size() != L.size()) {
			return false;
		}
		for (size_t i = 0; i < size(); i++) {
			if (At(i) != L[i]) {
				return false;
			}
		}
		return true;
	}
	bool operator!=(const ForwardList& L) const {
		return !(*this == L);
	}
	void Print() {
		if (IsEmpty()) {
			cout << "Empty\n";
			return;
		}
		Node* pointer = First;
		size_t i = 0;
		for (i; i < Size - 1; i++) {
			cout << "#" << i << ": " << pointer->data << "; ";
			pointer = pointer->next;
		}
		cout << "#" << i << ": " << pointer->data << ".\n";
	}
	friend void swap(ForwardList<T>& l, ForwardList<T>& r) {
		swap(l.Size, r.Size);
		swap(l.First, r.First);
	}
	void Sort() {
		Node* tmp1;
		Node* tmp_gen;
		size_t pos = 0;
		for (size_t i = 0; i < Size - 1; i++) {
			tmp1 = ToPos(i);
			tmp_gen = tmp1;
			for (size_t j = i; j < Size; j++) {
				Node* tmp2 = ToPos(j);
				if (tmp_gen->data > tmp2->data) {
					tmp_gen = tmp2;
					pos = j;
				}
			}
			if (tmp1->data > tmp_gen->data) {
				PushAfter(i, tmp_gen->data);
				PushAfter(pos + 1, tmp1->data);
				EraseAfter(pos);
				if (i == 0) {
					PopFront();
				}
				else {
					EraseAfter(i - 1);
				}
			}
		}
	}
	void Clear() {
		size_t size = this->size();
		for (size_t i = size - 1; i > 0; i--) {
			EraseAfter(i - 1);
		}
		PopFront();
	}
};