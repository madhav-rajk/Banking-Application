#ifndef BANK_H
#define BANK_H

#include "BinarySearchTree.h"
#include "Transaction.h"
#include <queue>
#include <string>
#include <fstream>
#pragma once

using namespace std;

class Bank
{
public:
	//constructor
	Bank();

	//copy constructor
	Bank(const Bank& other);

	~Bank();

	//getters for the class
	BinarySearchTree getAllAccounts() const;
	queue<Transaction*> getAllTransactions() const;

	//actions for the class
	void readText(string file);
	void executeText();
	void displayAccounts();

	//assignment operator overload
	Bank& operator=(const Bank& other);

private:
	//represents if the input file is valid to execute
	bool isValidFile;
	string inputFile;

	BinarySearchTree allAccounts;
	queue<Transaction*> allTransactions;

	//methods to make all the different types of transactions
	Transaction* makeTransaction(string file);
	bool executeTransaction(Transaction*& transac);
	void OpenAccount(Transaction*& transac);
	void Deposit(Transaction*& transac);
	void Withdraw(Transaction*& transac);
	void Transfer(Transaction*& transac);
	void DisplayHistory(Transaction*& transac) const;

};


#endif

