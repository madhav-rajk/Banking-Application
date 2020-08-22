#ifndef WITHDRAWTRANSACTION_H
#define WITHDRAWTRANSACTION_H

#pragma once

#include "Transaction.h"

class WithdrawTransaction : public Transaction
{
public:
	//constructors for the DepositTransaction class
	WithdrawTransaction();
	WithdrawTransaction(istream& inStream);

	//need to call virtual since we are using inheritance for the class
	virtual ~WithdrawTransaction();

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