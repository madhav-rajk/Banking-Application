#ifndef TRANSFERTRANSACTION_H
#define TRANSFERTRANSACTION_H

#pragma once

#include "Transaction.h"

class TransferTransaction : public Transaction
{
public:
	//constructors for the DepositTransaction class
	TransferTransaction();
	TransferTransaction(istream& inStream);

	//need to call virtual since we are using inheritance for the class
	virtual ~TransferTransaction();

	//setters for the DepositTransaction class
	void setAmount(int amount);

	//getters for the DepositTransaction class
	int getAmount() const;
	int getTypeOfFund() const;
	int getSecondClientId() const;
	int getSecondClientFundType() const;

	//actions for the DepositTransaction class
	string TransactionHistory() const;
	bool IfValid() const;

private:
	//main amount of the account, then ID and fund type of the second account
	//where we will transfer funds
	int amount;
	int secondClientId;
	int secondClientFundType;
};


#endif