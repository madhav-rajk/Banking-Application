#include "DepositTransaction.h"

//no-arg constructor
DepositTransaction::DepositTransaction()
{

}

/*
Sets the ID to the given instream values given to us, and sets the length
to the length of the ID, and make sure the length is correct. If the ID
is valid, then make the type of fund the last char in the given ID. Then,
also resize to just the ID size. Takes the amount through the instream and 
set if valid to true.
*/
DepositTransaction::DepositTransaction(istream& inStream)
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

//destructor
DepositTransaction::~DepositTransaction()
{
}

//sets the current amount to the given amount
void DepositTransaction::setAmount(int amount)
{
	this->amount = amount;
}

//returns the amount of the current transaction
int DepositTransaction::getAmount() const
{
	return amount;
}

//returns the history of the transaction, where we take the same method name
//from the Transaction class and we add onto it the amount for the deposit 
//objects.
string DepositTransaction::TransactionHistory() const
{
	string history = Transaction::TransactionHistory();
	history += (" " + to_string(getAmount()));
	return history;
}

//returns if the transaction is valid.
bool DepositTransaction::IfValid() const
{
	return valid;
}
