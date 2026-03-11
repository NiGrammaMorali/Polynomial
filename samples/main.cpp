#include "polynomial.h"

int main(void) {
	ForwardList<int> ListTest;
	ListTest.Print();
	Monomial<int> Monom1(3, "320");
	Monomial<int> Monom2(2, "101");
	for (size_t i = 0; i < 5; i++) {
		ListTest.PushFront(i);
	}
	try {
		ListTest.Print();
		ListTest.PushAfter(3, 9);
		ListTest.Print();
		ListTest.EraseAfter(1);
		ListTest.Print();
		ListTest.PopFront();
		ListTest.Print();
		ListTest.PopFront();
		ListTest.Print();
		ListTest.PopFront();
		ListTest.Print();
		ListTest.PopFront();
		ListTest.Print();
		ListTest.PopFront();
		ListTest.Print();
		ListTest.PopFront();
		ListTest.Print();
		Monomial<int> Monom3 = Monom1 * Monom2;
		Monom3.Print();
		Polynomial<int> Poly1(Monom3);
		Monomial<int> Monom4(-3, "102");
		Poly1.PushFront(Monom4);
		Poly1.Print();
		ForwardList<Monomial<int>> LIST;
		Monomial<int> Monom5(-3, "102");
		Monomial<int> Monom6(-2, "421");
		LIST.PushFront(Monom5);
		LIST.PushFront(Monom6);
		LIST.Print();
		Polynomial<int> Poly2(LIST);
		Poly2.Print();
		Poly2.Sort();
		Poly2.Print();
		Polynomial<int> Poly3 = Poly1 * Poly2;
		Poly3.Print();
		//Poly3.Sort();
		//Poly3.Print();
	}
	catch (const out_of_range& mes) {
		cerr << mes.what() << '\n';
	}
	catch (const logic_error& mes) {
		cerr << mes.what() << '\n';
	}
	return 0;
}