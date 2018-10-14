#include "pch.h" 
#include "Bank.h"
#include "BankError.h"

using namespace std;

Bank::Bank(string filename_)
{
	readFile(filename_);
}


Bank::~Bank()
{
}

string Bank::getDate() const {
	return _date;
}
double Bank::getSpotRate() const {
	return _spotRate;
}
vector<Account> Bank::getAccounts() const {
	return _accounts;
}

void Bank::setDate(string date_) {
	_date = date_;
}
void Bank::setSpotRate(double spotRate_) {
	_spotRate = spotRate_;
}
void Bank::setAccounts(vector<Account> accounts_) {
	_accounts = accounts_;
}

ostream& operator<<(ostream& os_, const Bank& bank_) {
	string accountString = "";
	for (size_t i = 0; i < bank_._accounts.size(); i++)
	{
		accountString += bank_._accounts[i].getAccountHolder() + " (" + bank_._accounts[i].getAccountId() + ") : " + to_string(bank_._accounts[i].getDeposit()) + "\n";
		for (size_t j = 0; j < bank_._accounts[i].getTransactions().size(); j++)
		{
			accountString += bank_._accounts[i].getTransactions()[j].toString() + "\n";
		}
	}

	os_ << accountString;
	return os_;
}

string Bank::toString() {

	return "semmi";
}

void Bank::readFile(string filepath_) {
	ifstream inputFile;
	inputFile.open(filepath_);
	string line;
	while (!inputFile.eof()) {
		getline(inputFile, line);
		string sep1 = ",";
		string sep2 = ":";
		int pos1 = line.find(sep1);
		int pos2 = line.find(sep2);

		if (pos1 == string::npos && pos2 == string::npos) {
			if (getDate() != "") {
				dailyProcess();
				this->setDate(line);
			}
			else {
				this->setDate(line);
			}	
		}
		else if (pos2 != string::npos && pos1 == string::npos) {
			string rate = line.substr(pos2 + 1);
			this->setSpotRate(stod(rate));
		}
		else {
			vector<string> lineData = processLineData(line);
			if (line.find("new account") != string::npos) {
				createAccount(lineData);
			}
			else if (line.find("withdraw") != string::npos) {
				createWithdrawData(lineData, this->getDate());
			}
			else if (line.find("deposit") != string::npos) {
				createDepositData(lineData, this->getDate());
			}
		}
	}
	if (getDate() != "") {
		dailyProcess();
	}

	inputFile.close();
}


void Bank::createAccount(vector<string> accountDataString_) {
	try {
		if (findAccount(accountDataString_[2]) > -1) {
			string message = accountDataString_[2] + " already exists! \n";
			throw BankError(message);
		}

		Account a(accountDataString_[1], accountDataString_[2]);
		a.setDeposit(0);
		a.makeDepositTransaction(stod(accountDataString_[3]), this->getDate());
		if (accountDataString_.size() == 5) {
			a.setCredit(stod(accountDataString_[4]));
		}
		else {
			a.setCredit(0);
		}
		_accounts.push_back(a);
	}
	catch (BankError e) {
		cout << e.getMessage();
	}	
}

int Bank::findAccount(string accountId_) {
	if (_accounts.size() == 0) {
		return -1;
	}
	
	int i = 0;
	while (i < _accounts.size() && accountId_ != _accounts[i].getAccountId()) {
		i++;
	}
	if (i < _accounts.size()) {
		return i;
	}
	else {
		return -1;
	}
}

void Bank::createDepositData(vector<string> transactionDataString_, string date_){
	
	int index = findAccount(transactionDataString_[0]);
	_accounts[index].makeDepositTransaction(stod(transactionDataString_[2]), date_);
}

void Bank::createWithdrawData(vector<string> transactionDataString_, string date_) {
	int index = findAccount(transactionDataString_[0]);
	_accounts[index].makeWithdrawTransaction(stod(transactionDataString_[2]), date_);
}
vector<string> Bank::processLineData(string line_) {
	string sep = ",";
	vector<string> lineData;
	while (line_.find(sep) != string::npos) {
		int pos = line_.find(sep);
		lineData.push_back(line_.substr(0, pos));
		line_ = line_.substr(pos + 1);
	}
	lineData.push_back(line_);
	return lineData;
}

void Bank::calculateInterestTransaction() {
	for (size_t i = 0; i < _accounts.size(); i++)
	{
		if (_accounts[i].getDeposit() > 0) {
			double eventValue_ = exp(getSpotRate() / 365);
			Transaction t(interest, eventValue_, getDate());
			vector<Transaction> tr_v = _accounts[i].getTransactions();
			tr_v.push_back(t);
			_accounts[i].setTransactions(tr_v);
			_accounts[i].setDeposit(_accounts[i].getDeposit() + eventValue_);
		
		}
		else {
			double eventValue_ = exp(4*getSpotRate() / 365);
			Transaction t(interest, -eventValue_, getDate());
			vector<Transaction> tr_v = _accounts[i].getTransactions();
			tr_v.push_back(t);
			_accounts[i].setTransactions(tr_v);
			_accounts[i].setDeposit(_accounts[i].getDeposit() - eventValue_);
		
		}
	}
	
}

void Bank::checkAccounts() {
	for (size_t i = 0; i < _accounts.size(); i++)
	{
		if (_accounts[i].getDeposit() < -_accounts[i].getCredit()) {
			_accounts.erase(_accounts.begin() + i);
			//throw BankError(_accounts[i].getAccountId + " has been erased! ");
		}
	}
}
void Bank::dailyProcess() {
	calculateInterestTransaction();
	/*
	try {
		checkAccounts();
	}
	catch (BankError e) {
		cout << e.getMessage();
	}
	*/
}