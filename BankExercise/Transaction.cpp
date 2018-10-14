#include "pch.h"
#include "Transaction.h"

string EventTypeMap[] = { "interest", "deposit", "withdraw" };

Transaction::Transaction(EventTypes eventType_, double eventValue_, string transactionDate_) : 
	_eventType(eventType_), _eventValue(eventValue_), _transactionDate(transactionDate_)
{
}


Transaction::~Transaction()
{
}


EventTypes Transaction::getEventTypes() const {
	return _eventType;
}
double Transaction::getEventValue() const {
	return _eventValue;
}
void Transaction::setEventTypes(EventTypes eventType_) {
	_eventType = eventType_;
}
void Transaction::setEventValue(double eventValue_) {
	_eventValue = eventValue_;
}

string Transaction::getTransactionDate() const {
	return _transactionDate;
}
void Transaction::setTransactionDate(string transactionDate_) {
	_transactionDate = transactionDate_;
}

string Transaction::toString() {
	return getTransactionDate() + ": "+ to_string(getEventValue()) + " (" + EventTypeMap[getEventTypes()] + ")";
}

