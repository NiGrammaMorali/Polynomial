#pragma once

#include <iostream>
#include "polynomial.h"

template<typename T>
class HashMap2 {
private:
	std::vector<std::pair<int, Polynomial<T>>> table;
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
			if (table[i].second.GetSize() > k) {
				k = table[i].second.GetSize();
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
	HashMap2() = default;
	HashMap2(const HashMap2&) = default;
	HashMap2(HashMap2&&) = default;
	~HashMap2() = default;
	HashMap2& operator=(const HashMap2&) = default;
	HashMap2& operator=(HashMap2&&) = default;
	pair<int, Polynomial<T>>& operator[](size_t pos) {
		return table[pos];
	}
	const pair<int, Polynomial<T>>& operator[](size_t pos) const {
		return table[pos];
	}
	pair<int, Polynomial<T>>& At(int pos) {
		if (pos < 0 || pos >= Size()) {
			throw out_of_range("The index is out of range");
		}
		return table[pos];
	}
	const pair<int, Polynomial<T>>& At(int pos) const {
		if (pos < 0 || pos >= Size()) {
			throw out_of_range("The index is out of range");
		}
		return table[pos];
	}
	bool operator==(const HashMap2& map) const {
		size_t size = Size();
		for (size_t i = 0; i < size; i++) {
			Polynomial<T> pol1 = table[i].second;
			Polynomial<T> pol2 = map[i].second;
			if ((table[i].first != map[i].first) || (pol1 != pol2)) {
				return false;
			}
		}
		return true;
	}
	void AddElement(const Polynomial<T>& poly) {
		size_t j = 1;
		bool Ready;
		for (j; j < 4; j++) {
			Ready = true;
			int hash = Hash(poly, j);
			for (size_t i = 0; i < table.size(); i++) {
				if (table[i].first == hash) {
					Ready = false;
					break;
				}
			}
			if (Ready) {
				std::pair<int, Polynomial<T>> tmp(hash, poly);
				table.push_back(tmp);
				Sort();
				return;
			}
		}
		throw std::logic_error("New hash can't be generated");
	}
	Polynomial<T> FindElement(int tag) {
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
			std::pair<int, Polynomial<T>> tmp(table[i].first, table[i].second);
			cout << tmp.first << "\t| ";
			tmp.second.Print();
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