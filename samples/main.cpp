#include "unordered_map.h"
#include "ordered_map.h"
#include "ordered_map_list.h"
#include "hash_map2.h"

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
		ListTest.Sort();
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
		Monomial<int> Monom3 = Monom1 * Monom2;
		Monom3.Print();
		Polynomial<int> Poly1(Monom3);
		Monomial<int> Monom4(-3, "102");
		Poly1.PushFront(Monom4);
		Poly1.Print();
		cout << '\n';
		ForwardList<Monomial<int>> LIST;
		Monomial<int> Monom5(-3, "102");
		Monomial<int> Monom6(-2, "421");
		LIST.PushFront(Monom5);
		LIST.PushFront(Monom6);
		LIST.Print();
		Polynomial<int> Poly2(LIST);
		Poly2.Print();
		cout << '\n';
		Poly2.Sort();
		Poly2.Print();
		cout << '\n';
		Polynomial<int> Poly3 = Poly1 * Poly2;
		Poly3.Print();
		cout << '\n';
		cout << Poly3.CalculateInPoint(1, 1, 2) << '\n';
		HashMap2<int> a;
		cout << "\n\n";
		cout << "\n\n";
		Poly1 = Poly2;
		a.AddElement(Poly3);
		a.AddElement(Poly1);
		a.AddElement(Poly2);
		a.Print();
		HashMap2<int> b(a);
		cout << "\n\n";
		a.DeleteElement(24);
		a.Print();
		cout << (a == b) << '\n';
		a.Clear();
		a.Print();
	}
	catch (const out_of_range& mes) {
		cerr << mes.what() << '\n';
	}
	catch (const logic_error& mes) {
		cerr << mes.what() << '\n';
	}
	return 0;
}