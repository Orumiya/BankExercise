#include <string>
using namespace std;

enum EventTypes{ interest, deposit, withdraw};
string EventTypeMap[];

class Transaction
{
public:
	Transaction(EventTypes, double, string);
	~Transaction();
	
	EventTypes getEventTypes() const;
	double getEventValue() const;
	string toString();
	void setEventTypes(EventTypes);
	void setEventValue(double);
	
	string getTransactionDate() const;
	void setTransactionDate(string);
private:
	EventTypes _eventType;
	double _eventValue;
	string _transactionDate;

};

