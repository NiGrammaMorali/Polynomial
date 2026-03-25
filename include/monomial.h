#pragma once
#include <iostream>

template<typename T>
class Monomial {
private:
	std::string degree;
	T coefficient;
public:
	Monomial() : coefficient(0), degree("000") {}
	Monomial(T val, const std::string& deg) : coefficient(val), degree(deg) {}
	Monomial(const Monomial& mon) : coefficient(mon.coefficient), degree(mon.degree) {}
	Monomial& operator=(const Monomial& mon) {
		if (*this != mon) {
			this->degree = mon.degree;
			this->coefficient = mon.coefficient;
		}
		return *this;
	}
	bool operator==(const Monomial& mon) noexcept {
		return ((this->coefficient == mon.coefficient) && (this->degree == mon.degree));
	}
	bool operator!=(const Monomial& mon) {
		return !(*this == mon);
	}
	bool DegreeCheck(const std::string& deg) const {
		return (this->degree == deg);
	}
	bool NullCoef() const {
		return(this->coefficient == 0);
	}
	std::string& GetDegree() {
		return degree;
	}
	T& GetCoefficient() {
		return coefficient;
	}
	Monomial operator+(const Monomial& mon) {
		if (!(DegreeCheck(mon.degree))) {
			throw std::logic_error("Monomials have different degrees");
		}
		Monomial result;
		result.degree = this->degree;
		result.coefficient = this->coefficient + mon.coefficient;
		return result;
	}
	Monomial operator-(const Monomial& mon) {
		if (!(DegreeCheck(mon.degree))) {
			throw std::logic_error("Monomials have different degrees");
		}
		Monomial result;
		result.degree = this->degree;
		result.coefficient = this->coefficient - mon.coefficient;
		return result;
	}
	Monomial operator*(const Monomial& mon) {
		for (size_t i = 0; i < 3; i++) {
			if ((this->degree[i] + mon.degree[i] - 96) > 9) {
				throw std::logic_error("Too big resulting degree");
			}
		}
		Monomial result;

		result.degree = "000";
		for (size_t i = 0; i < 3; i++) {
			result.degree[i] = (this->degree[i] + mon.degree[i] - 48);
		}
		result.coefficient = this->coefficient * mon.coefficient;
		return result;
	}
	Monomial& operator*=(T val) {
		this->coefficient *= val;
		return *this;
	}
	bool operator>(const Monomial& val) {
		return (this->degree > val.degree);
	}
	void Print() {
		cout << coefficient << ' ' << degree << '\n';
	}
	friend std::ostream& operator<<(std::ostream& ostr, const Monomial& mon) {
		ostr << mon.coefficient << ' ' << mon.degree;
		return ostr;
	}
};