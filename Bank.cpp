#include "Bank.h"

//no-arg constructor
Bank::Bank()
{
}

//since both the classes have operator overload for the classes, 
//we can simply use those to set this class's assignment operator
//to set the accounts and transactions equal.
Bank::Bank(const Bank& other)
{
	*this = other;
}

/*
Sets all the accounts and transactions in this class equal to the same 
in the other class. It does so by first emptying all the accounts, then
setting this class's BSTree of accounts to the other. Then, does the same
thing for the queue of transactions, empties everything, then sets it equal
to the content of this class.
*/
Bank& Bank::operator=(const Bank& other)
{
	this->allAccounts.Empty();
	this->allAccounts = other.allAccounts;
	while (!allTransactions.empty())
	{
		Transaction* toDel = allTransactions.front();
		delete toDel;
		allTransactions.pop();
	}
	this->allTransactions = other.allTransactions;
	return *this;
}

//gets rid of all the transactions in the class by taking the item in the 
//front, then deleting it, and then popping it off the queue, in the FIFO
//manner of the queue.
Bank::~Bank()
{
	while (!allTransactions.empty())
	{
		Transaction* toDel = allTransactions.front();
		delete toDel;
		allTransactions.pop();
	}
}

//returns the object of Binary Search Tree representing all accounts.
BinarySearchTree Bank::getAllAccounts() const
{
	return allAccounts;
}

//returns the queue of transactions
queue<Transaction*> Bank::getAllTransactions() const
{
	return allTransactions;
}

/*
reads the text from the string file. Gives the string into the instream; if 
file could not be opened then appropriate error is printed, else we create the
transaction object and give each line into the object and if they are valid then
we put the transaction object into the queue of transactions.
*/
void Bank::readText(string file)
{
	ifstream inputFile;
	this->inputFile = file;
	inputFile.open(this->inputFile);
	if (!inputFile.is_open())
	{
		cerr << "FILE NOT FOUND!" << endl;
	}
	else
	{
		string eachLine;
		while (!inputFile.eof())
		{
			getline(inputFile, eachLine);
			Transaction* transaction;
			transaction = makeTransaction(eachLine);
			if (eachLine == "")
			{
				break;
			}
			if (transaction->IfValid())
			{
				allTransactions.push(transaction);
			}
		}
		inputFile.close();
	}
}

/*
Executes the actual transaction based on the given file and takes the char 
from in stream and checks which type of transaction and makes the appropriate
object based on that type of transaction.
*/
Transaction* Bank::makeTransaction(string file)
{
	stringstream inputFileStream(file);
	Transaction* execTrans = nullptr;
	char fundType;

	inputFileStream >> fundType;
	if (fundType == 'O')
	{
		execTrans = new OpenTransaction(inputFileStream);
		execTrans->setTypeOfTransaction(fundType);
	}
	else if (fundType == 'D')
	{
		execTrans = new DepositTransaction(inputFileStream);
		execTrans->setTypeOfTransaction(fundType);
	}
	else if (fundType == 'W')
	{
		execTrans = new WithdrawTransaction(inputFileStream);
		execTrans->setTypeOfTransaction(fundType);
	}
	else if (fundType == 'T')
	{
		execTrans = new TransferTransaction(inputFileStream);
		execTrans->setTypeOfTransaction(fundType);
	}
	else if (fundType == 'H')
	{
		execTrans = new HistoryTransaction(inputFileStream);
		execTrans->setTypeOfTransaction(fundType);
	}
	return execTrans;
}

//does the actual work of executing the each transaction, where we used the 
//above method to make the transaction, now we actually make changes to the 
//object representing all the transactions.
void Bank::executeText()
{
	while (!allTransactions.empty())
	{
		if (allTransactions.front() != nullptr)
		{
			executeTransaction(allTransactions.front());
		}
		allTransactions.pop();
	}
	cout << "\nProcessing Done.";
}

//shows all the accounts 
void Bank::displayAccounts()
{
	if (!allAccounts.isEmpty())
	{
		cout << " Final Balances" << endl;
		allAccounts.Display();
	}
	else
	{
		cout << "Accounts are Empty." << endl;
	}
}

//takes the type of transaction and based on the type of transaction, calls
//the appropriate method in the class.
bool Bank::executeTransaction(Transaction*& transac)
{
	char fundType = transac->getTypeOfTransaction();
	if (fundType == 'O')
	{
		OpenAccount(transac);
	}
	else if (fundType == 'D')
	{
		Deposit(transac);
	}
	else if (fundType == 'W')
	{
		Withdraw(transac);
	}
	else if (fundType == 'T')
	{
		Transfer(transac);
	}
	else if (fundType == 'H')
	{
		DisplayHistory(transac);
	}
	else
	{
		cerr << "ERROR: Invalid Char Transaction Input" << endl;
		return false;
	}
	return true;
}

/*
Takes the transaction object and makes sure we get the actual account. If the
account is null, then we create a new OpenTransaction object and adds the 
appropriate details for the account and inserts the account into the list of 
accounts in the class.Deletes the object appropriately at the end.
*/
void Bank::OpenAccount(Transaction*& transac)
{
	Account* accountPtr;
	if (transac->getAccountId() < 1000 || transac->getAccountId() > 9999)
	{
		cerr << "ERROR: Invalid Account ID " << transac->getAccountId() << endl;
		return;
	}
	allAccounts.Retrieve(transac->getAccountId(), accountPtr);
	if (accountPtr == nullptr)
	{
		OpenTransaction* openAcct = dynamic_cast<OpenTransaction*>(transac);
		accountPtr = new Account(openAcct->getFirstName(),
			openAcct->getLastName(), openAcct->getAccountId());
		allAccounts.Insert(accountPtr);
	}
	else
	{
		cerr << "ERROR: Account " << transac->getAccountId()
			<< " is already open. Transaction refused." << endl;
	}
	delete transac;
}

/*
Takes the transaction object and makes sure we get the actual account. If the
account is found, then we create a new DepositTransaction object and adds the
appropriate details and makes the deposit for the account. Deletes the object 
appropriately at the end.
*/
void Bank::Deposit(Transaction*& transac)
{
	DepositTransaction* depo = dynamic_cast<DepositTransaction*>(transac);
	if (transac->getAccountId() < 1000 || transac->getAccountId() > 9999)
	{
		cerr << "ERROR: Invalid Account ID " << transac->getAccountId() << endl;
		return;
	}
	Account* accToDepo;
	if (allAccounts.Retrieve(depo->getAccountId(), accToDepo))
	{
		accToDepo->Deposit(transac);
	}
	else
	{
		cerr << "ERROR: Account " << depo->getAccountId() 
			 << " not found. Deposit refused." << endl;
	}
	delete transac;
}

/*
Takes the transaction object and makes sure we get the actual account. If the
account is found, then we create a new WithdrawTransaction object and adds the
appropriate details and if not enough funds, then the account prints an error.
Deletes the object appropriately at the end.
*/
void Bank::Withdraw(Transaction*& transac)
{
	WithdrawTransaction* withdraw = dynamic_cast<WithdrawTransaction*>(transac);
	Account* accToWithdraw;
	if (transac->getAccountId() < 1000 || transac->getAccountId() > 9999)
	{
		cerr << "ERROR: Invalid Account ID " << transac->getAccountId() << endl;
		return;
	}
	if (allAccounts.Retrieve(withdraw->getAccountId(), accToWithdraw))
	{
		bool ifEnoughFunds = accToWithdraw->Withdraw(withdraw->getAmount(), 
										withdraw->getTypeOfFund(), transac);
		if (!ifEnoughFunds)
		{
			cerr << "ERROR: Not enough funds to withdraw " 
				 << withdraw->getAmount() << " from " 
				<< accToWithdraw->getFirstName() + " " + 
				accToWithdraw->getLastName() << +" " + 
				FUNDS[transac->getTypeOfFund()] << endl;
		}
	}
	else
	{
		cerr << "ERROR: Account " << to_string(transac->getAccountId()) 
			 << " not found. Withdraw refused." << endl;
	}
	delete transac;
}

/*
takes the acc to transfer from and the transfer to account, with the transaction 
dynamically cast as a TransferTransaction. Then, we find if the transfer to and 
from account exist. If they do, then we make the appropriate transaction, else
we print that there were not enough funds. If the transfer to account doesn't 
exist, then we print that the particular account doesn't exist.
*/
void Bank::Transfer(Transaction*& transac)
{
	TransferTransaction* transf = dynamic_cast<TransferTransaction*>(transac);
	Account* accToTransFrom;
	Account* ToAccount;

	if (transac->getAccountId() < 1000 || transac->getAccountId() > 9999)
	{
		cerr << "ERROR: Invalid Account ID " << transac->getAccountId() << endl;
		return;
	}

	string accountNumber = to_string(transac->getAccountId());

	bool accExists = allAccounts.Retrieve(transac->getAccountId(), 
						accToTransFrom);
	bool otherAccExists = allAccounts.Retrieve(transf->getSecondClientId(),
							ToAccount);
	if (accExists && otherAccExists)
	{	
		bool ifEnoughFunds = accToTransFrom->Transfer(transac, *ToAccount);
		if (!ifEnoughFunds)
		{
			cerr << "ERROR: Not enough funds to Transfer "
				<< transf->getAmount() << " from "
				<< accToTransFrom->getFirstName() + " " +
				accToTransFrom->getLastName() << + " " +
				FUNDS[transac->getTypeOfFund()] << " to " 
				<< ToAccount->getFirstName() << " " << ToAccount->getLastName()
				<< " " << FUNDS[transf->getSecondClientFundType()] << endl;
		}
	}
	else
	{
		accountNumber = transac->getAccountId() + " and " + 
						transf->getSecondClientId();

		if (!accExists && !otherAccExists)
		{
			string accountNumOne = to_string(transac->getAccountId());
			string accountNumTwo = to_string(transf->getSecondClientId());

			cerr << "ERROR: Account " << accountNumOne << " and " 
				<< accountNumTwo << " not found. Transferral refused." << endl;
		}
		else
		{
			if (accExists && !otherAccExists)
			{
				accountNumber = to_string(transf->getSecondClientId());
			}
			else if (!accExists && otherAccExists)
			{
				accountNumber = to_string(transac->getAccountId());
			}

			cerr << "ERROR: Account " << accountNumber
				<< " not found. Transferral refused." << endl;
		}
	}
	delete transac;
}

//displays the history for the particular account object, where
//we find the particular account from the Tree and display the history 
//by the type of fund.
void Bank::DisplayHistory(Transaction*& transac) const
{
	Account* hist;
	if (allAccounts.Retrieve(transac->getAccountId(), hist))
	{
		if (transac->getTypeOfFund() == -1)
		{
			hist->displayHistory();
		}
		else
		{
			hist->displayHistoryByFund(transac->getTypeOfFund());
		}
	}
	else
	{
		cerr << "ERROR: Account " << transac->getAccountId() 
			<< " not found. History refused." << endl;
	}
	delete transac;
}