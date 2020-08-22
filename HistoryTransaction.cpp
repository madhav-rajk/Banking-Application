#include "HistoryTransaction.h"

//no-arg constructor
HistoryTransaction::HistoryTransaction()
{
}

/*
Sets the ID to the given instream values given to us, and sets the length
to the length of the ID, and make sure the length is correct. If the ID
is valid, then make the type of fund the last char in the given ID. Then,
also resize to just the ID size. Takes the amount through the instream and
set if valid to true. If the ID length is not correct, then set valid as true
else prints an error and sets valid to false.
*/
HistoryTransaction::HistoryTransaction(istream& inStream)
{
	string id;
	inStream >> id;

	if (id.length() == ID_LENGTH)
	{
		typeOfFund = id[id.length() - 1] - '0';
		id.resize(id.length() - 1);
		accountId = stoi(id);
		setIfValid(true);
	}
	else if (id.length() == 4)
	{
		typeOfFund = -1;
		accountId = stoi(id);
		setIfValid(true);
	}
	else
	{
		cerr << "ERROR: Invalid Account Input" << endl;
		setIfValid(false);
	}

}

//Destructor
HistoryTransaction::~HistoryTransaction()
{
}

/*
the history of transaction will be updated by this method, where either only 
the transaction object's history will be printed, or we will print with a 
failed for the history.
*/
void HistoryTransaction::updateHistory(Transaction* transToAdd, bool valid)
{
	if (valid)
	{
		transHistory.push_back(transToAdd->TransactionHistory());
	}
	else
	{
		transHistory.push_back(transToAdd->TransactionHistory() + " (Failed)");
	}
}

//returns if the object is valid
bool HistoryTransaction::IfValid() const
{
	return valid;
}

//prints the particular history of the transaction of the given object. 
ostream& operator<<(ostream& outStream, const HistoryTransaction& other)
{
	for (int i = 0; i < other.transHistory.size(); i++)
	{
		outStream << "  " + other.transHistory[i] << endl;
	}

	return outStream;
}
