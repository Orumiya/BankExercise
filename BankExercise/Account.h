#include <vector>
#include "Transaction.h"

using namespace std;

class Account
{
public:
	Account(string, string);
	//Account(const Account&);
	~Account();

	string getAccountHolder() const;
	string getAccountId() const;
	double getDeposit() const;
	double getCredit() const;

	void setAccountHolder(string);
	void setAccountId(string);
	void setDeposit(double);
	void setCredit(double);

	vector<Transaction> getTransactions() const;
	void setTransactions(vector<Transaction>);
	void makeWithdrawTransaction(double, string);
	void makeDepositTransaction(double, string);

private:
	string _accountHolder;
	string _accountId;
	double _deposit;
	double _credit;
	vector<Transaction> _transactions;

	

};

