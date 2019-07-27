#include "labgui.h"

bool bTypeOfOrder;

Fl_Box *text1;
Fl_Box *text2;

Fl_Button *buyOrderButton;
Fl_Button *sellOrderButton;
Fl_Button *executeOrderButton;

Fl_Button *requestQuoteButton;
Fl_Button *addCompanyButton;

void placeBuyOrder(Fl_Widget*, void*)
{
	bTypeOfOrder = false;
	create_order();
}
void placeSellOrder(Fl_Widget*, void*) 
{
	bTypeOfOrder = true;
	create_order();
}

void executeOrder(Fl_Widget*, void*)
{
	int i;
	for(i = 0; i < (int)companies.size(); i++)
	{
		if(companies[i].executeOrder(transactionLog))
		{
			fl_choice("A transaction has taken place!", "Yes", 0, 0);
			create_transaction();
			return;
		}
	}

	fl_choice("There is no transaction taken place.", "Yes", 0, 0);
}

void requestQuote(Fl_Widget*, void*)
{
	static string Company_Quote;

	string companyName = editBox->value();
	string stockSymbol = editBox2->value();

	int i;
	for(i = 0; i < (int)companies.size(); i++)
	{
		if(companyName.size())
		{
			if(stringLower(companyName) == stringLower(companies[i].companyName))
			{
				if(stockSymbol != companies[i].stockSymbol)
				{
					fl_choice("Invalid stock symbol for the comapny.", "Ok", 0, 0);
					return;
				}
				Company_Quote = companies[i].toString();
				text1->label(Company_Quote.c_str());
				return;
			}
		}
		else
		{
			if(stockSymbol == companies[i].stockSymbol)
			{
				Company_Quote = companies[i].toString();
				text1->label(Company_Quote.c_str());
				return;
			}			
		}
	}

	fl_choice("Cannot find the company specified.", "Ok", 0, 0);
}

void addCompany(Fl_Widget*, void*)
{
	string companyName = editBox->value();
	string stockSymbol = editBox2->value();

	if(fl_choice("Are you sure you want to add a new company?", "No", "Yes", 0) != 1) return;

	if(companyName.size() <= 2)
	{
		fl_choice("The company name must be at least 2 characters long.", "Ok", 0, 0);
		return;	
	}

	if(stockSymbol.size() < 4 || stockSymbol.size() > 5)
	{
		fl_choice("The stock symbol must be 4 or 5 chaaracters long.", "Ok", 0, 0);
		return;	
	}

	int i;
	for(i = 0; i < (int)companies.size(); i++)
	{
		if(stringLower(companyName) == stringLower(companies[i].companyName))
		{
			fl_choice("The company name has been already taken.", "Ok", 0, 0);
			return;
		}

		if(stockSymbol == companies[i].stockSymbol)
		{
			fl_choice("The stock symbol has been already taken.", "Ok", 0, 0);
			return;
		}
	}

	companies.push_back(Company(companyName, stockSymbol));
	fl_choice("The new company has been added successfully!", "Ok", 0, 0);
}


void create_home()
{
	if(win)
	{
		delete win;
		win = NULL;
	}
	win = new Fl_Window(550, 500);
	win->label("Home Exchange");

	int i;
	for(i = 0; i < (int)companies.size(); i++)
	{
		companies[i].queryInformation();
	}

	static string First_Company;

	First_Company = companies[0].toString();

	text1 = new Fl_Box(-520, -30, 535, 200, First_Company.c_str());

	text1->align(FL_ALIGN_RIGHT);

	editBox = new Fl_Input(125, 280, 180, 30, "Company Name: ");
	editBox2 = new Fl_Input(125, 320, 180, 30, "Stock Symbol: ");

	editBox->value("Intel");
	editBox2->value("INTC");

	sellOrderButton = new Fl_Button(350, 45, 150, 30, "Place Sell Order");
	buyOrderButton = new Fl_Button(350, 90, 150, 30, "Place Buy Order");
	executeOrderButton = new Fl_Button(350, 135, 150, 30, "Execute Order");

	requestQuoteButton = new Fl_Button(350, 280, 150, 30, "Request Quote");
	addCompanyButton = new Fl_Button(350, 320, 150, 30, "Add Company");

	buyOrderButton->callback(placeBuyOrder);
	sellOrderButton->callback(placeSellOrder);
	executeOrderButton->callback(executeOrder);

	requestQuoteButton->callback(requestQuote);
	addCompanyButton->callback(addCompany);

	win->show();
}

