#include <FL/Fl.H>
#include <FL/fl_ask.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Secret_Input.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Multiline_Output.H>
#include <FL/Fl_Text_Editor.H>
#include <FL/Fl_Text_Buffer.H>
#include <FL/Fl_JPEG_Image.H>
#include <FL/Fl_Multiline_Input.H>

#include <iostream>
#include <string>
#include <map>
#include <sstream>
#include <vector>
#include <iomanip>

using std::cout;
using std::endl;
using std::cin;
using std::string;
using std::map;
using std::vector;
using std::stringstream;
using std::istream;
using std::ostream;
using std::left;
using std::setw;
using std::fixed;
using std::setprecision;

#include "HEAP.H"
#include "order.h"
#include "company.h"

extern bool bTypeOfOrder;

extern void create_home();
extern void create_order();
extern void create_transaction();

extern string stringLower(string s);

extern Fl_Window *win;
extern vector<Company> companies;

extern Fl_Box *text1;
extern Fl_Box *text2;
extern Fl_Box *text3;

extern Fl_Button *buyOrderButton;
extern Fl_Button *sellOrderButton;

extern Fl_Button *requestQuoteButton;
extern Fl_Button *addCompanyButton;

extern void placeBuyOrder(Fl_Widget*, void*);
extern void placeSellOrder(Fl_Widget*, void*);
extern void cancelOrder(Fl_Widget*, void*);
extern void executeOrder(Fl_Widget*, void*);
extern void returnHome(Fl_Widget*, void*);
extern void requestQuote(Fl_Widget*, void*);
extern void addCompany(Fl_Widget*, void*);

extern Fl_Input *editBox;
extern Fl_Input *editBox2;
extern Fl_Input *editBox3;
extern Fl_Input *editBox4;

extern Fl_Button *buttonPlaceOrder;
extern Fl_Button *buttonCancel;
extern Fl_Button *executeOrderButton;
extern Fl_Button *buttonReturn;

extern string transactionLog;

extern Fl_Multiline_Output *outputLog;