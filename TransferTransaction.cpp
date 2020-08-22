#include "TransferTransaction.h"

//no-argument constructor
TransferTransaction::TransferTransaction()
{
}

/*
Sets the ID to the given instream values given to us, and sets the length
to the length of the ID, and make sure the length is correct. If the ID
is valid, then make the type of fund the last char in the given ID. Then,
also resize to just the ID size. Takes the amount through the instream and
set if valid to true. Also makes the same checks for the second ID.
*/
TransferTransaction::TransferTransaction(istream& inStream)
{
	string id;

	inStream >> id;
	int length = id.length();

	if (length != ID_LENGTH)
	{
		setIfValid(false);
		cerr << "ERROR: Invalid ID Input Length" << endl;
	}
	else
	{
		typeOfFund = id[id.length() - 1] - '0';
		id.resize(id.length() - 1);
		accountId = stoi(id);
		inStream >> amount;

		string secondId;
		inStream >> secondId;
		int secondIdLength = secondId.length();

		if (secondIdLength != ID_LENGTH)
		{
			setIfValid(false);
			cerr << "ERROR: Invalid ID Input Length" << endl;
		}
		else
		{
			secondClientFundType = secondId[secondId.length() - 1] - '0';
			secondId.resize(secondId.length() - 1);
			secondClientId = stoi(secondId);
			setIfValid(true);
		}
	}
}

//Destructor
TransferTransaction::~TransferTransaction()
{
}

//sets the current amount to the given amount
void TransferTransaction::setAmount(int amount)
{
	this->amount = amount;
}

//returns the amount 
int TransferTransaction::getAmount() const
{
	return amount;
}

//returns the type of fund
int TransferTransaction::getTypeOfFund() const
{
	return typeOfFund;
}

//returns the second client's ID
int TransferTransaction::getSecondClientId() const
{
	return secondClientId;
}

//returns the second client's type of fund
int TransferTransaction::getSecondClientFundType() const
{
	return secondClientFundType;
}

//prints the history for the transfer transcation object, where we take the 
//type of transcation, along with the type of fund, amount and ID for the 
//first and second ID.
string TransferTransaction::TransactionHistory() const
{
	stringstream stringToConvert;
	string type;
	stringToConvert << getTypeOfTransaction();
	stringToConvert >> type;
	string history = type + " " + to_string(getAccountId()) + "" +
		to_string(getTypeOfFund()) + " " +
		to_string(getAmount()) + " " +
		to_string(getSecondClientId()) + "" + 
		to_string(getSecondClientFundType());
	return history;
}

//returns if the type of transaction is valid
bool TransferTransaction::IfValid() const
{
	return valid;
}
