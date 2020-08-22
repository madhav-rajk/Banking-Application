#include "Transaction.h"

//sets if valid to true through the no-argument constructor
Transaction::Transaction()
{
	valid = true;
}

//Destructor
Transaction::~Transaction()
{
}

//sets the type of transaction to the given type
void Transaction::setTypeOfTransaction(char transType)
{
	this->transType = transType;
}

//sets the account ID to the given ID
void Transaction::setAccountId(int id)
{
	this->accountId = id;
}

//sets the amount to the given amount
void Transaction::setAmount(int amount)
{

}

//sets the validity to given validity
void Transaction::setIfValid(bool ifValid)
{
	this->valid = ifValid;
}

//sets the type of fund to the given type
void Transaction::setTypeOfFund(int typeFund)
{
	this->typeOfFund = typeFund;
}

//returns the type of transaction for the object
char Transaction::getTypeOfTransaction() const
{
	return transType;
}

//returns the ID for the particular account
int Transaction::getAccountId() const
{
	return accountId;
}

//returns the type of fund for the account
int Transaction::getTypeOfFund() const
{
	return typeOfFund;
}

//prints ID and type of fund for the particular transaction
string Transaction::TransactionHistory() const
{
	stringstream stringToConvert;
	string type;
	stringToConvert << getTypeOfTransaction();
	stringToConvert >> type;
	string history = type + " " + to_string(getAccountId()) + "" +
		to_string(getTypeOfFund());
	return history;
}

//returns if the transaction is valid
bool Transaction::IfValid() const
{
	return valid;
}
