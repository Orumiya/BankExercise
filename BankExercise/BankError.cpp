#include "pch.h"
#include "BankError.h"


BankError::BankError(const string& message_) : _message(message_)
{
}


BankError::~BankError()
{
}

string BankError::getMessage() {
	return _message;
}