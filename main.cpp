#include "labgui.h"

vector<Company> companies;

Fl_Window *win = NULL;

double orderCommision = 19.95;

int main()
{
	companies.push_back(Company("Microsoft", "MSFT"));
	companies.push_back(Company("Intel", "INTC"));

	/*
	HEAP<Order> h1(1000);
	HEAP<Order> h2(1000);
	h1.Insert(Order("This", "MSFT", 63.00, 150, false));
	h1.Insert(Order("This", "MSFT", 35.00, 150, false));
	h1.Insert(Order("Bill M.", "MSFT", 84.37, 2000, false));
	h1.Insert(Order("This", "MSFT", 44.00, 150, false));
	h1.Insert(Order("This", "MSFT", 53.00, 150, false));

	h2.Insert(Order("That", "MSFT", 263.00, 150, true));
	h2.Insert(Order("That", "MSFT", 235.00, 150, true));
	h2.Insert(Order("Sharon K.", "MSFT", 84.37, 2000, true));
	h2.Insert(Order("That", "MSFT", 244.00, 150, true));
	h2.Insert(Order("That", "MSFT", 253.00, 150, true));

	cout << h1.Peek().toString();

	while(!h1.IsEmpty())
	{
		cout << "Best Bid : $" << h1.Peek().sharePrice << endl;
		h1.Remove(h1.Peek());
	}

	cout << endl;
	cout << h2.Peek().toString();

	while(!h2.IsEmpty())
	{
		cout << "Best Ask : $" << h2.Peek().sharePrice << endl;
		h2.Remove(h2.Peek());
	}

	*/

	create_home();
	return Fl::run();
}