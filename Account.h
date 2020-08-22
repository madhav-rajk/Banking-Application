#ifndef ACCOUNT_H
#define ACCOUNT_H

#pragma once
#include "Transaction.h"
#include "OpenTransaction.h"
#include "DepositTransaction.h"
#include "WithdrawTransaction.h"
#include "TransferTransaction.h"
#include "HistoryTransaction.h"

#include <vector>
#include <string>
#include <iostream>
#include <queue>

using namespace std;

enum typeOfFunds {
	MoneyMarket, PrimeMoneyMarket, LongTermBond, ShortTermBond,
	IndexFund500, CapitalValueFund, GrowthEquityFund,
	GrowthIndexFund, ValueFund, ValueStockIndex
};

const string FUNDS[10] = { "Money Market", "Prime Money Market",
						   "Long-Term Bond", "Short-Term Bond",
						   "500 Index Fund", "Capital Value Fund",
						   "Growth Equity Fund", "Growth Index Fund",
						   "Value Fund", "Value Stock Index" };

//represents the size of the Fund
const int FUND_SIZE = 10;

class Account
{
public:
	//no-arg constructor and a constructor taking first name, last name and 
	//the id, representing a new account
	Account();
	Account(string firstName, string lastName, int id);

	//destructor
	~Account();

	//setters for the Account class
	void setName(string firstName, string lastName);
	void setId(int id);

	//getters for the Account class
	string getFirstName() const;
	string getLastName() const;
	int getId() const;

	//actions for the Account class
	bool Deposit(Transaction*& depositAmt);
	bool Withdraw(int amount, int typeOfFund, Transaction*& withdrawAmt);
	bool Transfer(Transaction*& transferAmt, Account& accountToTransferTo);
	void displayHistory() const;
	void displayHistoryByFund(int typeOfFund);

	//functions for comparison operator overloading
	bool operator<(const Account& other) const;
	bool operator<=(const Account& other) const;
	bool operator>(const Account& other) const;
	bool operator>=(const Account& other) const;
	bool operator==(const Account& other) const;
	bool operator!=(const Account& other) const;

	//function for io stream operator overloading
	friend ostream& operator<<(ostream& outStream, const Account& other);

private:
	//the 3 variables represent the Account's name and id.
	string firstName;
	string lastName;
	int id;
	int typeOfFund;
	int balance;
	
	//represents the history of all the transactions for particular the account
	vector<HistoryTransaction> hisAllTransactions;
	vector<int> balanceOfFunds;
	//says if each Fund index is active for the account
	vector<bool> isActive;

	//method to withdraw from second fund
	bool withdrawPrivMethod(int fundOne, int fundTwo, int amount, 
							Transaction*& transac);

};

#endif