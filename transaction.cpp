#include "labgui.h"

Fl_Button *buttonReturn;
Fl_Multiline_Output *outputLog;

string transactionLog;

void returnHome(Fl_Widget*, void*)
{
	create_home();
}

void create_transaction()
{
	if(win)
	{
		delete win;
		win = NULL;
	}

	win = new Fl_Window(550, 500);
	win->label("Transaction Log");

	text1 = new Fl_Box(0, 5, 550, 30, "The two orders have been executed.");

	outputLog = new Fl_Multiline_Output(10, 35, 530, 410);
	outputLog->value(transactionLog.c_str());

	buttonReturn = new Fl_Button(200, 455, 100, 30, "Return");
	buttonReturn->callback(returnHome);

	win->show();
}
