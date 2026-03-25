#pragma once
#include "list.h"
#include "monomial.h"
#include <algorithm>

template<typename T>
class Polynomial {
private:
	ForwardList<Monomial<T>> List;
	bool NullPoly;
	bool CheckForNull() {
		for (size_t i = 0; i < List.size(); i++) {
			if (!(List[i].NullCoef())) {
				return false;
			}
		}
		return true;
	}
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
		NullPoly = CheckForNull();
		if (!(NullPoly)) {
		}
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
				this->NullPoly = false;
				return *this;
			}
		}
		NullPoly = true;
		return *this;
	}
	Monomial<T>& At(size_t position) {
		return List[position];
	}
	const Monomial<T>& At(size_t position) const {
		return List[position];
	}
	Monomial<T>& operator[](size_t position) {
		return List[position];
	}
	const Monomial<T>& operator[](size_t position) const {
		return List[position];
	}
	bool IsEmpty() noexcept {
		return List.IsEmpty();
	}
	bool IsNull() noexcept {
		return NullPoly;
	}
	bool operator==(const Polynomial& pol) {
		if (GetSize() != pol.GetSize()) {
			return false;
		}
		for (size_t i = 0; i < GetSize(); i++) {
			bool iteration_result = false;
			for (size_t j = 0; j < GetSize(); j++) {
				Monomial<T> m = pol[j];
				vector<char> deg_num1, deg_num2;
				string deg1 = List[i].GetDegree();
				string deg2 = m.GetDegree();
				for (size_t j = 0; j < 3; j++) {
					deg_num1.push_back(deg1[i]);
					deg_num2.push_back(deg2[i]);
				}
				const size_t cof = m.GetCoefficient();
				if ((deg_num1 == deg_num2) && (List[i].GetCoefficient() == cof)) {
					iteration_result = true;
				}
			}
			if (!(iteration_result)) {
				return false;
			}
		}
		return true;
	}
	bool operator!=(const Polynomial& pol) {
		return !(*this == pol);
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
		result.NullPoly = CheckForNull();
		return result;
	}
	Polynomial operator-(const Polynomial& pol) {
		Polynomial result;
		Monomial<T> tmp;
		bool found;
		ForwardList<Monomial<T>> tmp_list = pol.List;
		vector<size_t> indexes;
		for (size_t i = 0; i < this->List.size(); i++) {
			found = false;
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
		result.NullPoly = CheckForNull();
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
		tmp_list.Sort();
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
		result.NullPoly = CheckForNull();
		return result;
	}

	void PushFront(const Monomial<int>& mon) {
		for (size_t i = 0; i < GetSize(); i++) {
			string deg = List[i].GetDegree();
			if (mon.DegreeCheck(deg)) {
				List[i] = mon;
				return;
			}
		}
		List.PushFront(mon);
	}
	void PrintAsList() {
		List.Print();
	}
	void Print() {
		if (NullPoly == true) {
			cout << "0";
			return;
		}
		size_t SIZE = List.size();
		Monomial<T> tmp = List[0];
		string deg = tmp.GetDegree();
		cout << tmp.GetCoefficient() << "x^(" << deg[0] << ")y^(" << deg[1] << ")z^(" << deg[2] << ')';
		for (size_t i = 1; i < SIZE; i++) {
			tmp = List[i];
			deg = tmp.GetDegree();
			if (tmp.GetCoefficient() > 0) {
				cout << '+';
			}
			else if (tmp.GetCoefficient() == 0) {
				continue;
			}
			cout << tmp.GetCoefficient() << "x^(" << deg[0] << ")y^(" << deg[1] << ")z^(" << deg[2] << ')';
		}
	}
	void Sort() {
		List.Sort();
	}
	const size_t GetSize() const {
		size_t res = List.size();
		return res;
	}
	T CalculateInPoint(T x, T y, T z) {
		T result = NULL;
		size_t SIZE = List.size();
		T coords[3] = {x, y, z};
		for (size_t i = 0; i < SIZE; i++) {
			Monomial<T> tmp = List[i];
			string deg = tmp.GetDegree();
			size_t k = 0;
			T tmp_result = 1;
			for (auto c : deg) {
				tmp_result *= pow(coords[k], c - 48);
				k++;
			}
			tmp_result *= tmp.GetCoefficient();
			result += tmp_result;
		}
		return result;
	}
	size_t GetSize() {
		return List.size();
	}
};