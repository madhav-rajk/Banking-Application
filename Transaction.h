#ifndef TRANSACTION_H
#define TRANSACTION_H

#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "Fund.h"

const int ID_LENGTH = 5;

using namespace std;

class Transaction
{
public:
	Transaction();

	//need to call virtual since we are using inheritance to have other
	//child classes
	virtual ~Transaction();

	//setters for the Transaction class
	virtual void setTypeOfTransaction(char transType);
	virtual void setAccountId(int id);
	virtual void setAmount(int amount);
	virtual void setIfValid(bool ifValid);
	virtual void setTypeOfFund(int typeFund);

	//getters for the Transaction class
	virtual char getTypeOfTransaction() const;
	virtual int getAccountId() const;
	virtual int getTypeOfFund() const;

	//actions for the Transaction class
	virtual string TransactionHistory() const;
	virtual bool IfValid() const;

protected:
	//has the type of transaction, the ID, type of fund and if transaction
	//is valid
	char transType;
	int accountId;
	int typeOfFund;
	bool valid;
};

#endif