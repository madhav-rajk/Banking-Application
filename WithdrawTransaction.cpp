#include "WithdrawTransaction.h"

//no-argument constructor
WithdrawTransaction::WithdrawTransaction()
{
}

/*
Sets the ID to the given instream values given to us, and sets the length
to the length of the ID, and make sure the length is correct. If the ID
is valid, then make the type of fund the last char in the given ID. Then,
also resize to just the ID size. Takes the amount through the instream and
set if valid to true.
*/
WithdrawTransaction::WithdrawTransaction(istream& inStream)
{
	string id;

	inStream >> id;
	int length = id.length();

	if (length != ID_LENGTH)
	{
		setIfValid(false);
		cerr << "ERROR: Invalid Account Input" << endl;
	}
	else
	{
		typeOfFund = id[id.length() - 1] - '0';
		id.resize(id.length() - 1);
		accountId = stoi(id);
		inStream >> amount;
		setIfValid(true);
	}
}

//Destructor
WithdrawTransaction::~WithdrawTransaction()
{
}

//sets the current amount to the given amount
void WithdrawTransaction::setAmount(int amount)
{
	this->amount = amount;
}

//returns the amount 
int WithdrawTransaction::getAmount() const
{
	return amount;
}

//returns the history of the transaction, where we take the same method name
//from the Transaction class and we add onto it the amount for the withdraw 
//objects.
string WithdrawTransaction::TransactionHistory() const
{
	string history = Transaction::TransactionHistory();
	history += (" " + to_string(getAmount()));
	return history;
}

//returns if the transaction is valid.
bool WithdrawTransaction::IfValid() const
{
	return valid;
}
