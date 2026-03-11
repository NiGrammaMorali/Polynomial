#pragma once
#include "list.h"
#include "monomial.h"
#include <algorithm>

template<typename T>
class Polynomial {
private:
	ForwardList<Monomial<T>> List;
	bool NullPoly;
public:
	Polynomial() : NullPoly(true) {}
	Polynomial(const Monomial<T>& mon) {
		List.PushFront(mon);
		if (mon.NullCoef()) {
			NullPoly = true;
		}
		else {
			NullPoly = false;
		}
	}
	Polynomial(const ForwardList<Monomial<T>>& l) {
		List = l;
		for (size_t i = 0; i < List.size(); i++) {
			if (!(List[i].NullCoef())) {
				NullPoly = true;
				return;
			}
		}
		NullPoly = false;
	}
	Polynomial& operator=(const Polynomial& pol) {
		if (*this != pol) {
			this->List = pol.List;
			this->NullPoly = pol.NullPoly;
		}
		return *this;
	}
	Polynomial& operator=(const ForwardList<Monomial<int>>& l) {
		this->List = l;
		for (size_t i = 0; i < List.size(); i++) {
			if (!(this->List[i].NullCoef())) {
				this->NullPoly = true;
				return *this;
			}
		}
		NullPoly = false;
		return *this;
	}
	Monomial<T>& operator[](size_t position) {
		return List[position];
	}
	Polynomial operator+(const Polynomial& pol) {
		Polynomial result;
		Monomial<T> tmp;
		ForwardList<Monomial<T>> tmp_list = pol.List;
		vector<size_t> indexes;
		bool found = false;
		for (size_t i = 0; i < this->List.size(); i++) {
			for (size_t j = 0; j < pol.List.size(); j++) {
				if (List[i].GetDegree() == tmp_list[j].GetDegree()) {
					tmp = List[i] + tmp_list[j];
					result.PushFront(tmp);
					found = true;
					indexes.push_back(j);
					break;
				}
			}
			if (!(found)) {
				result.PushFront(this->List[i]);
			}
			found = false;
		}
		sort(indexes.begin(), indexes.end(), greater<int>());
		for (auto x : indexes) {
			if (x == 0 && tmp_list.size() == 1) {
				tmp_list.PopFront();
			}
			else {
				tmp_list.EraseAfter(x - 1);
			}
		}
		for (size_t i = 0; i < tmp_list.size(); i++) {
			result.PushFront(tmp_list[i]);
		}
		return result;
	}
	Polynomial operator-(const Polynomial& pol) {
		Polynomial result;
		Monomial<T> tmp;
		ForwardList<Monomial<T>> tmp_list = pol.List;
		vector<size_t> indexes;
		bool found = false;
		for (size_t i = 0; i < this->List.size(); i++) {
			for (size_t j = 0; j < pol.List.size(); j++) {
				if (List[i].GetDegree() == tmp_list[j].GetDegree()) {
					tmp = List[i] - tmp_list[j];
					result.PushFront(tmp);
					found = true;
					indexes.push_back(j);
					break;
				}
			}
			if (!(found)) {
				result.PushFront(List[i]);
			}
			found = false;
		}
		sort(indexes.begin(), indexes.end(), greater<int>());
		for (auto x : indexes) {
			if (x == 0 && tmp_list.size() == 1) {
				tmp_list.PopFront();
			}
			else {
				tmp_list.EraseAfter(x - 1);
			}
		}
		for (size_t i = 0; i < tmp_list.size(); i++) {
			tmp_list[i] *= -1;
			result.PushFront(tmp_list[i]);
		}
		return result;
	}
	Polynomial operator*(const Polynomial& pol) {
		ForwardList<Monomial<T>> tmp_result;
		Polynomial result;
		Monomial<T> tmp;
		ForwardList<Monomial<T>> tmp_list = pol.List;
		for (size_t i = 0; i < this->List.size(); i++) {
			for (size_t j = 0; j < tmp_list.size(); j++) {
				tmp = List[i] * tmp_list[j];
				result.PushFront(tmp);
			}
		}
		tmp_list = result.List;
		for (size_t i = 0; i < tmp_list.size(); i++) {
			tmp = tmp_list[i];
			for (size_t j = i + 1; j < tmp_list.size(); j++) {
				if (tmp_list[i].GetDegree() == tmp_list[j].GetDegree()) {
					tmp = tmp + tmp_list[j];
					tmp_list.PushAfter(i, tmp);
					tmp_list.EraseAfter(j);
					if (i == 0) {
						tmp_list.PopFront();
					}
					else {
						tmp_list.EraseAfter(i-1);
					}
					j--;
				}
			}
		}
		result = tmp_list;
		return result;
	}
	void PushFront(const Monomial<int>& mon) {
		List.PushFront(mon);
	}
	void Print() {
		List.Print();
	}
	void Sort() {
		List.Sort();
	}
};