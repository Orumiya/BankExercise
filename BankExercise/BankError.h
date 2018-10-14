#include <string>
using namespace std;

class BankError
{
public:
	BankError(const string&);
	~BankError();

	string getMessage();

private:
	string _message;
};

