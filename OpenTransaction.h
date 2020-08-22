#ifndef OPENTRANSACTION_H
#define OPENTRANSACTION_H

#pragma once

#include "Transaction.h"

//uses inheritance in order to use the methods from the Transaction class in 
//this class and use the variables from that class instead of making new ones
//here. 
class OpenTransaction : public Transaction
{
public:
	//Constructors for the OpenTransaction class
	OpenTransaction();
	OpenTransaction(istream& inStream);

	//need to call virtual since we are using inheritance for the class
	virtual ~OpenTransaction();

	//getters for the OpenTransaction class
	string getFirstName() const;
	string getLastName() const;

	//actions for the OpenTransaction class
	bool IfValid() const;

private:
	string firstName;
	string lastName;
};

#endif