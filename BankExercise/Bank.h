#include "Account.h"
#include <iostream>
#include <fstream>
#include <istream>
using namespace std;

class Bank
{
	
public:
	Bank(string);
	//Bank(const Bank&);
	~Bank();

	string getDate() const;
	double getSpotRate() const;
	vector<Account> getAccounts() const;

	void setDate(string);
	void setSpotRate(double);
	void setAccounts(vector<Account>);
	friend ostream& operator<<(ostream&, const Bank&);

	string toString();
private:
	string _date;
	double _spotRate;

	vector<Account> _accounts;
	void readFile(string);
	void createAccount(vector<string>);
	int findAccount(string);
	void createDepositData(vector<string>, string);
	void createWithdrawData(vector<string>, string);
	vector<string> processLineData(string);
	void calculateInterestTransaction();
	void checkAccounts();
	void dailyProcess();
};

