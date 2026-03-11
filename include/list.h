#pragma once
#include  <iostream>
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
public:
	ForwardList() : First(nullptr), Size(0) {}
	ForwardList(const vector<T>& V) {
		for (size_t i = V.size(); i > 0; i--) {
			PushFront(v[i - 1]);
		}
	}
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
	void PopFront() noexcept {
		if (IsEmpty()) {
			return;
		}
		Node* pointer = First;
		First = First->next;
		delete pointer;
		Size--;
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
		for (size_t i = 0; i < Size - 1; i++) {
			tmp1 = ToPos(i);
			for (size_t j = i + 1; j < Size; j++) {
				Node* tmp2 = ToPos(j);
				if (tmp1->data > tmp2->data) {
					PushAfter(i, tmp2->data);
					PushAfter(j + 1, tmp1->data);
					EraseAfter(j);
					if (i == 0) {
						PopFront();
					}
					else {
						EraseAfter(i - 1);
					}
				}
			}
		}
	}
};