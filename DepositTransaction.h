#ifndef DEPOSITTRANSACTION_H
#define DEPOSITTRANSACTION_H

#pragma once

#include "Transaction.h"


class DepositTransaction : public Transaction
{
public:
	//constructors for the DepositTransaction class
	DepositTransaction();
	DepositTransaction(istream& inStream);

	//need to call virtual since we are using inheritance for the class
	virtual ~DepositTransaction();

	//setters for the DepositTransaction class
	void setAmount(int amount);

	//getters for the DepositTransaction class
	int getAmount() const;

	//actions for the DepositTransaction class
	string TransactionHistory() const;
	bool IfValid() const;

private:
	int amount;
};


#endif