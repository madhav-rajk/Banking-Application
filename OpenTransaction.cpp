#include "OpenTransaction.h"

//no-argument constructor
OpenTransaction::OpenTransaction()
{
}

/*
sets the first, last name, and ID from taking the string through the instream.
Makes sure if the length of the ID is not accurate then prints an error, else 
if ok, then sets the ID and sets validity to true.
*/
OpenTransaction::OpenTransaction(istream& inStream)
{
	inStream >> lastName;
	inStream >> firstName;
	string id;
	inStream >> id;
	int length = id.length();
	if (length != 4)
	{
		setIfValid(false);
		cerr << "ERROR: Invalid Account Input" << endl;
	}
	else
	{
		accountId = stoi(id);
		setIfValid(true);
	}

}

//Destructor
OpenTransaction::~OpenTransaction()
{
}

//returns the first name
string OpenTransaction::getFirstName() const
{
	return firstName;
}

//returns the last name
string OpenTransaction::getLastName() const
{
	return lastName;
}

//returns if the transaction is valid
bool OpenTransaction::IfValid() const
{
	return valid;
}
