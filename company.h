#ifndef _COMPANY_H_
#define _COMPANY_H_

#include "order.h"

template <class T>
T maxValue(const T& first, const T& second)
{
	if(first > second) return first;
	return second;
}

template <class T>
T minValue(const T& first, const T& second)
{
	if(first < second) return first;
	return second;
}

struct Value
{
	Value() : value(0), first(true), def(0) {}

	double get() const
	{ 
		return value;
	}

	double getS() const
	{
		if(first) return def;
		return value;
	}

	void set(double val)
	{
		first = false;
		value = val;
	}

	double def;
	double value;
	bool first;
};

class Company
{
	HEAP<Order> buyOrders;
	HEAP<Order> sellOrders;

	public : 

	Company(string name, string symbol) : buyOrders(1000), sellOrders(1000)
	{
		companyName = name;
		stockSymbol = symbol;

		Lo.value = 999999;
	}

	void queryInformation()
	{
		if(!buyOrders.IsEmpty())
		{
			Hi.set(maxValue(Hi.get(), buyOrders.Peek().sharePrice));
			Lo.set(minValue(Lo.get(), buyOrders.Peek().sharePrice));
			Bid.set(buyOrders.Peek().sharePrice);
			Bid_Size.set(buyOrders.Peek().numShares);
		}
		else
		{
			Bid.set(0);
			Bid_Size.set(0);
		}

		if(!sellOrders.IsEmpty())
		{
			Hi.set(maxValue(Hi.get(), sellOrders.Peek().sharePrice));
			Lo.set(minValue(Lo.get(), sellOrders.Peek().sharePrice));
			Ask.set(sellOrders.Peek().sharePrice);
			Ask_Size.set(sellOrders.Peek().numShares);
		}
		else
		{
			Ask.set(0);
			Ask_Size.set(0);
		}
	}

	bool placeOrder(Order order)
	{
		bool status;
		if(!order.bReversedOrder) 
		{
			 if(status = (buyOrders.Insert(order) != FAILED)) Last.set(order.sharePrice); 
		}
		else
		{		
			if(status = (sellOrders.Insert(order) != FAILED))  Last.set(order.sharePrice);
		}

		return status;
	}

	bool executeOrder(string &reportLog)
	{
		bool status = false;
		if(!buyOrders.IsEmpty() && !sellOrders.IsEmpty())
		{
			reportLog = "";

			Order buyOrder = buyOrders.Peek();
			Order sellOrder = sellOrders.Peek();

			buyOrders.Remove(buyOrders.Peek());
			sellOrders.Remove(sellOrders.Peek());

			int sellOrder_Shares_Sold;
			int buyOrder_Shares_Sold; 

			if(buyOrder.sharePrice == sellOrder.sharePrice)
			{
				if(sellOrder.numShares >= buyOrder.numShares) {
					buyOrder_Shares_Sold = buyOrder.numShares;
					sellOrder_Shares_Sold = buyOrder.numShares;

					sellOrder.numShares -= buyOrder.numShares; 
					buyOrder.numShares = 0;

				}
				else
				{
					buyOrder_Shares_Sold = sellOrder.numShares;
					sellOrder_Shares_Sold = sellOrder.numShares;

					buyOrder.numShares -= sellOrder.numShares;
					sellOrder.numShares = 0;
				}

				if(buyOrder.numShares > 0) buyOrders.Insert(buyOrder);
				if(sellOrder.numShares > 0) sellOrders.Insert(sellOrder);

				buyOrder.numShares = buyOrder_Shares_Sold;
				sellOrder.numShares = sellOrder_Shares_Sold;

				status = true;
				reportLog += sellOrder.toString() + '\n';
				reportLog += buyOrder.toString();

			}
		}

		return status;
	}
	
	string toString()
	{
		stringstream ss;
		ss << stockSymbol << '\n';
		ss << fixed << setprecision(2) << left;
		ss << setw(5) << "Hi: " << setw(8) << Hi.getS() << "Lo: " << setw(9) << Lo.getS() << "Last : " << Last.get() << endl;
		ss << setw(5) << "Bid: " << setw(8) << Bid.getS() << "Bid size:  " << (int)Bid_Size.getS() << endl;
		ss << setw(5) << "Ask: " << setw(8) << Ask.getS() << "Ask size:  " << (int)Ask_Size.getS() << endl;

		return ss.str();
	}

	string companyName;
	string stockSymbol;

	Value Hi, Lo, Last;
	Value Bid, Bid_Size;
	Value Ask, Ask_Size;
};

#endif