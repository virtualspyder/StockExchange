#ifndef _ORDER_H_
#define _ORDER_H_

extern double orderCommision; // Default is $19.95

struct Order
{
	Order()
	{
		sharePrice = 0;
		numShares = 0;
		bReversedOrder = false;
	}

	Order(string accountHolder, string stockName, double pricePerShare, int numberOfShares, bool bOrderType)
	{
		accountName = accountHolder;
		stockSymbol = stockName;
		sharePrice = pricePerShare;
		numShares = numberOfShares;
		bReversedOrder = bOrderType;
	}

	double sharePrice;
	int numShares;
	string accountName;
	string stockSymbol;

	// Ideal for sorting and reverse-sorting, false (ascending order) - true (descending order)
	// Actually it indicates if an order is a Sell order or a Buy order
	// false : A Buy Order
	// true : A Sell Order
	bool bReversedOrder; 

	string toString()
	{
		stringstream ss;
		ss << fixed << setprecision(2);

		ss << accountName << ":" << endl;
		if(!bReversedOrder)
		{
			ss << "You bought " << numShares << " of  " << stockSymbol << " at $" << sharePrice << "." << endl;
			ss << "Commision $" << orderCommision << "." << endl;
			ss << "Total due $" << ((numShares * sharePrice) + orderCommision) << "." << endl;			
		}
		else
		{
			ss << "You sold " << numShares << " of  " << stockSymbol << " at $" << sharePrice << "." << endl;
			ss << "Commision $" << orderCommision << "." << endl;
			ss << "Total proceeds $" << ((numShares * sharePrice) - orderCommision) << "." << endl;
		}

		return ss.str();
	}

	bool operator == (const Order& order) const {
		return (sharePrice == order.sharePrice);
	}

	bool operator >= (const Order& order) const {
		if(!bReversedOrder) return sharePrice >= order.sharePrice;
		return sharePrice <= order.sharePrice;
	}

	bool operator <= (const Order& order) const {
		if(!bReversedOrder) return sharePrice <= order.sharePrice;
		return sharePrice >= order.sharePrice;
	}

	bool operator > (const Order& order) const {
		if(!bReversedOrder) return sharePrice > order.sharePrice;
		return sharePrice < order.sharePrice;
	}

	bool operator < (const Order& order) const {
		if(!bReversedOrder) return sharePrice < order.sharePrice;
		return sharePrice > order.sharePrice;
	}
};

#endif