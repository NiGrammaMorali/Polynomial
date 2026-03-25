#pragma once

#include <iostream>
#include "polynomial.h"

template<typename T>
class HashMap {
private:
	vector<pair<int, ForwardList<Polynomial<T>>>> table;
	int Hash(const Polynomial<T>& poly, size_t num) {
		int tmp = 0;
		for (size_t i = 0; i < poly.GetSize(); i++) {
			Monomial<T> mon = poly[i];
			string deg = mon.GetDegree();
			for (auto x : deg) {
				tmp += (x - 48) * (i + 1);
			}
			tmp *= mon.GetCoefficient();
		}
		tmp = abs(tmp);
		tmp = num * (tmp + num);
		tmp = tmp % 100;
		return tmp;
	}
	size_t BiggestPolySize() {
		size_t k = 0;
		for (size_t i = 0; i < table.size(); i++) {
			if (table[i].second[0].GetSize() > k) {
				k = table[i].second[0].GetSize();
			}
		}
		return k;
	}
	void Sort() {
		size_t size = table.size();
		for (size_t i = 0; i < size; i++) {
			int elem1 = table[i].first;
			for (size_t j = i + 1; j < size; j++) {
				int elem2 = table[j].first;
				if (elem1 > elem2) {
					swap(table[i], table[j]);
				}
			}
		}
	}
public:
	HashMap() = default;
	HashMap(const HashMap& map) = default;
	HashMap(HashMap&& map) = default;
	~HashMap() = default;
	HashMap& operator=(const HashMap& map) = default;
	HashMap& operator=(HashMap&& map) = default;
	pair<int, ForwardList<Polynomial<T>>>& operator[](size_t pos) {
		return table[pos];
	}
	const pair<int, ForwardList<Polynomial<T>>>& operator[](size_t pos) const {
		return table[pos];
	}
	pair<int, ForwardList<Polynomial<T>>>& At(int pos) {
		if (pos < 0 || pos >= Size()) {
			throw out_of_range("The index is out of range");
		}
		return table[pos];
	}
	const pair<int, ForwardList<Polynomial<T>>>& At(int pos) const {
		if (pos < 0 || pos >= Size()) {
			throw out_of_range("The index is out of range");
		}
		return table[pos];
	}
	bool operator==(const HashMap& map) const {
		size_t size = Size();
		for (size_t i = 0; i < size; i++) {
			size_t size2 = table[i].second.size();
			for (size_t j = 0; j < size2; j++) {
				Polynomial<T> pol1 = table[i].second[j];
				Polynomial<T> pol2 = map[i].second[j];
				if ((table[i].first != map[i].first) || (pol1 != pol2)) {
					return false;
				}
			}
		}
		return true;
	}
	void AddElement(const Polynomial<T>& poly) {
		size_t j = 1;
		int hash = Hash(poly, j);
		for (size_t i = 0; i < table.size(); i++) {
			if (table[i].first == hash) {
				table[i].second.PushFront(poly);
				cout << "AAA\n" << hash << '\n';
				return;
			}
		}
		ForwardList<Polynomial<T>> tmp_p;
		tmp_p.PushFront(poly);
		std::pair<int, ForwardList<Polynomial<T>>> tmp(hash, tmp_p);
		table.push_back(tmp);
		Sort();
	}
	ForwardList<Polynomial<T>>& FindElement(int tag) {
		if (tag > 99 || tag < 0) {
			throw std::invalid_argument("The argument must be from 0 to 99");
		}
		for (size_t i = 0; i < table.size(); i++) {
			if (table[i].first == tag) {
				return table[i].second;
			}
		}
		throw std::invalid_argument("There's no such entry");
	}
	void DeleteElement(int tag) {
		if (table.size() == 0) {
			throw std::logic_error("The table is empty");
		}
		if (tag > 99 || tag < 0) {
			throw std::invalid_argument("The argument must be from 0 to 99");
		}
		for (size_t i = 0; i < table.size(); i++) {
			if (table[i].first == tag) {
				table.erase(table.begin() + i);
				return;
			}
		}
		throw std::invalid_argument("There's no such entry already");
	}
	void Print() {
		size_t size = table.size();
		if (size == 0) {
			cout << "Empty\n";
			return;
		}
		size_t biggest = BiggestPolySize();
		cout << "Hash\t| Polynomial\n";
		for (size_t i = 0; i < size; i++) {
			cout << "--------|";
			for (size_t j = 0; j < biggest; j++) {
				cout << "------------------------";
			}
			cout << '\n';
			std::pair<int, ForwardList<Polynomial<T>>> tmp(table[i].first, table[i].second);
			cout << tmp.first << "\t| ";
			ForwardList<Polynomial<T>> list = tmp.second;
			size_t size2 = list.size();
			for (size_t j = 0; j < size2; j++) {
				cout << "#" << j << ": ";
				list[j].Print();
				cout << "; ";
			}
			cout << "\n";
		}
	}
	size_t Size() const {
		return table.size();
	}
	void Clear() {
		table.clear();
	}
};