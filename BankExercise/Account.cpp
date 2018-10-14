#include "pch.h"
#include "Account.h"


Account::Account(string accountHolder_, string accountId_) : _accountHolder(accountHolder_), _accountId(accountId_)
{
}


Account::~Account()
{
}

string Account::getAccountHolder() const{
	return _accountHolder;
}
string Account::getAccountId() const {
	return _accountId;
}
double Account::getDeposit() const {
	return _deposit;
}
double Account::getCredit() const {
	return _credit;
}
vector<Transaction> Account::getTransactions() const {
	return _transactions;
}
void Account::setTransactions(vector<Transaction> transactions_) {
	_transactions = transactions_;
}

void Account::setAccountHolder(string accountHolder_) {
	_accountHolder = accountHolder_;
}
void Account::setAccountId(string accountId_){
	_accountId = accountId_;
}
void Account::setDeposit(double deposit_) {
	_deposit = deposit_;
}
void Account::setCredit(double credit_) {
	_credit = credit_;
}

void Account::makeWithdrawTransaction(double eventValue_, string date_) {
	Transaction t(withdraw, eventValue_, date_);
	setDeposit(this->getDeposit() - eventValue_ );
	_transactions.push_back(t);
	t.toString();
}
void Account::makeDepositTransaction(double eventValue_, string date_) {
	Transaction t(deposit, eventValue_, date_);
	setDeposit(this->getDeposit() + eventValue_);
	_transactions.push_back(t);
	t.toString();
}

