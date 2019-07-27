#include "labgui.h"

Fl_Input *editBox;
Fl_Input *editBox2;
Fl_Input *editBox3;
Fl_Input *editBox4;

Fl_Button *buttonPlaceOrder;
Fl_Button *buttonCancel;

string stringLower(string s){
	for(size_t i = 0; i < s.size(); i++) s[i] = tolower(s[i]);
	return s;
}

bool verifyName(string accountHolder)
{
	if(accountHolder.size() <= 2)
	{
		fl_choice("Account name should be at least 3 characters long.", "Yes", 0, 0);
		return false;
	}
	return true;
}

bool verifyCompany(string &companyName, Company *&theCompany)
{
	int i;
	bool success = false;
	for(i = 0; i < (int)companies.size(); i++)
	{
		if(stringLower(companyName) == stringLower(companies[i].companyName))
		{
			theCompany = &companies[i];
			companyName = companies[i].stockSymbol;	
			success = true;
		}
	}

	if(success == false)
	{
		fl_choice("Company not recognized. Please enter an existing company.", "Yes", 0, 0);
		return false;	
	}

	return true;
}

bool verifySharePrice(string pricePerShare, double &sharePrice)
{
	sharePrice = 0;
	stringstream ss;
	char moneySign = ' ';

	ss << pricePerShare;
	ss >> moneySign;

	if(moneySign != '$')
	{
		fl_choice("Please include money sign for the price when you submit order.", "Yes", 0, 0);	
		return false;
	}

	ss >> sharePrice;
	if(!ss)
	{
		fl_choice("Please enter a valid price.", "Yes", 0, 0);	
		return false;
	}

	if(sharePrice <= 0)
	{
		fl_choice("Please enter a price greater than $0.00.", "Yes", 0, 0);	
		return false;	
	}

	return true;
}

bool verifyNumShares(string numberOfShares, int &numShares)
{
	numShares = 0;
	stringstream ss;

	ss << numberOfShares;
	ss >> numShares;

	if(!ss)
	{
		fl_choice("Please enter a valid number of shares.", "Yes", 0, 0);	
		return false;
	}

	if(numShares <= 0)
	{
		fl_choice("Number of shares must be greater than 0.", "Yes", 0, 0);	
		return false;	
	}

	if(numShares % 100 != 0)
	{
		fl_choice("Number of shares must be the multiplies of 100.", "Yes", 0, 0);	
		return false;	
	}

	return true;
}

void placeOrder(Fl_Widget*, void*)
{
	if(fl_choice("Are you sure you want to place order?", "No", "Yes", 0) == 1)
	{
		Company *theCompany;
		double sharePrice;
		int numShares;

		string accountHolder = editBox->value();
		string companyName = editBox2->value();
		string pricePerShare = editBox3->value();
		string numberOfShares = editBox4->value();

		if(!verifyName(accountHolder)) return;
		if(!verifyCompany(companyName, theCompany)) return;
		if(!verifySharePrice(pricePerShare, sharePrice)) return;
		if(!verifyNumShares(numberOfShares, numShares)) return;

		string stockName = companyName;
		bool status = theCompany->placeOrder(Order(accountHolder, stockName, sharePrice, numShares, bTypeOfOrder));

		if(status)
		{
			fl_choice("The order has been placed successfully.", "Yes", 0, 0);		
		}
		else
		{
			fl_choice("Some error has occured when proccessing your request. Please try again later.", "Yes", 0, 0);	
		}

		create_home();
	}
}

void cancelOrder(Fl_Widget*, void*)
{
	if(fl_choice("Are you sure you want to cancel the order?", "No", "Yes", 0) == 1)
	{
		create_home();
	}
}


void create_order()
{
	if(win)
	{
		delete win;
		win = NULL;
	}

	win = new Fl_Window(550, 500);
	if(!bTypeOfOrder) 
	{
		win->label("Place Order (Buy Order)");
	}
	else
	{
		win->label("Place Order (Sell Order)");	
	}

	text1 = new Fl_Box(0, 5, 550, 30, "Please enter required information : ");

	editBox = new Fl_Input(140, 40, 394, 30, "Account Name: ");
	editBox2 = new Fl_Input(140, 80, 394, 30, "Company name: ");
	editBox3 = new Fl_Input(140, 120, 394, 30, "Price per Share: ");
	editBox4 = new Fl_Input(140, 160, 394, 30, "Number of Shares: ");

	editBox2->value("Microsoft");
	editBox3->value("$0.00");
	editBox4->value("100");

	buttonPlaceOrder = new Fl_Button(50, 220, 150, 30, "Place Order");
	buttonCancel = new Fl_Button(335, 220, 150, 30, "Cancel");

	buttonPlaceOrder->callback(placeOrder);
	buttonCancel->callback(cancelOrder);

	win->show();
}