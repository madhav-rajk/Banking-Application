#include "Account.h"

/*
initializes all the variables of the account to 0, and empty string for name
*/
Account::Account()
{
	firstName = "";
	lastName = "";
	id = 0;
	typeOfFund = 0;
	balance = 0;
}

/*
Constructor takes the first and last name, along with the ID, and 
sets the balance and if fund is active to be of the appropriate size of an 
account, then having a loop that sets the value of the balance to 0 and 
the active status to false since no activity happened to the particular funds.
*/
Account::Account(string firstName, string lastName, int id)
{
	setName(firstName, lastName);
	setId(id);
	balanceOfFunds.resize(FUND_SIZE);
	hisAllTransactions.resize(FUND_SIZE);
	isActive.resize(FUND_SIZE);
	for (int i = 0; i < FUND_SIZE; i++)
	{
		balanceOfFunds[i] = 0;
		isActive[i] = false;
	}
	balance = 0;
}

//Destructor
Account::~Account()
{
}

//sets the first and last name to the given name
void Account::setName(string firstName, string lastName)
{
	this->firstName = firstName;
	this->lastName = lastName;
}

//sets the ID to the given ID
void Account::setId(int id)
{
	this->id = id;
}

//returns the first name of the account
string Account::getFirstName() const
{
	return firstName;
}

//returns the last name of the account
string Account::getLastName() const
{
	return lastName;
}

//returns the ID of the account
int Account::getId() const
{
	return id;
}

/*
Represents a deposit that is made into the account. The transfer amount is 
taken and the DepositTransaction class's object is used to get the amount and 
type of fund. then we check if the amount is less than 0, then we do nothing, 
else we add onto our current account balance the deposit amount and update the 
history of the transaction to be true, so the record will be printed.
*/
bool Account::Deposit(Transaction*& depositAmt)
{
	DepositTransaction* depoAmt = dynamic_cast<DepositTransaction*>(depositAmt);
	int asset = depoAmt->getAmount();
	int typeOfFund = depoAmt->getTypeOfFund();
	if (asset < 0)
	{
		return false;
	}
	else
	{
		balance += asset;
		balanceOfFunds[typeOfFund] += asset;
		hisAllTransactions[typeOfFund].updateHistory(depositAmt, true);
		isActive[typeOfFund] = true;
	}

}

/*
represents withdrawing from the account. take the amount, type of fund and the 
actual amount to withdraw, as parameter. If the given amount is bigger than 
current balance of the account, then update the history with failed 
transaction, else if the amount is less than the balance at the particular 
type of fund then we do the appropriate reduction for the withdraw. If the 
type of fund is 0, 1, 2, 3 then we go to the withdraw helper method, since 
we need to split the amount between funds if needed.
*/
bool Account::Withdraw(int amount, int typeOfFund, Transaction*& withdrawAmt)
{
	if (amount > balance)
	{
		hisAllTransactions[typeOfFund].updateHistory(withdrawAmt, false);
		isActive[typeOfFund] = true;
		return false;
	}
	else if (amount <= balanceOfFunds[typeOfFund])
	{
		balance -= amount;
		balanceOfFunds[typeOfFund] -= amount;
		hisAllTransactions[typeOfFund].updateHistory(withdrawAmt, true);
		isActive[typeOfFund] = true;
		return true;
	}
	else if (typeOfFund == MoneyMarket)
	{
		if (withdrawPrivMethod(MoneyMarket, PrimeMoneyMarket, amount, withdrawAmt))
		{
			return true;
		}
	}
	else if (typeOfFund == PrimeMoneyMarket)
	{
		if (withdrawPrivMethod(PrimeMoneyMarket, MoneyMarket, amount, withdrawAmt))
		{
			return true;
		}
	}
	else if (typeOfFund == LongTermBond)
	{
		if (withdrawPrivMethod(LongTermBond, ShortTermBond, amount, withdrawAmt))
		{
			return true;
		}
	}
	else if (typeOfFund == ShortTermBond)
	{
		if (withdrawPrivMethod(ShortTermBond, LongTermBond, amount, withdrawAmt))
		{
			return true;
		}
	}
	else
	{
		hisAllTransactions[typeOfFund].updateHistory(withdrawAmt, false);
		return false;
	}

}

/*
combines the balance of the first and second fund index, which could be 
0,1,2,3 since those are the linked funds. Makes sure the combined amount
is more than the amount to withdraw and if so, then makes the appropriate
withdraw and updates the history of both the fund indexes.
*/
bool Account::withdrawPrivMethod(int fundOne, int fundTwo, int amount, 
								Transaction*& transac)
{
	int combinedBalan = balanceOfFunds[fundOne] + balanceOfFunds[fundTwo];
	if (combinedBalan >= amount)
	{
		transac->setAmount(balanceOfFunds[fundOne]);
		hisAllTransactions[fundOne].updateHistory(transac, true);
		int leftOver = amount - balanceOfFunds[fundOne];
		balanceOfFunds[fundOne] = 0;
		balanceOfFunds[fundTwo] -= leftOver;
		balance -= amount;
		transac->setAmount(leftOver);
		transac->setTypeOfFund(fundTwo);
		hisAllTransactions[fundTwo].updateHistory(transac, true);
		isActive[fundOne] = true;
		isActive[fundTwo] = true;
		return true;
	}

	hisAllTransactions[fundOne].updateHistory(transac, false);

	return false;
}

/*
Represents the transfer from the current account to the account given to 
transfer the amount to. Uses the TransferTransaction object, which is dynamic 
cast, to make sure to avoid any errors with compilation. Then, takes the type 
of fund for both the current account and the account to transfer to. Then,
if the amount is valid, then checks if the withdraw is made, then the history
is update accordingly and the changes are made to the balance of the fund. 
If not, then update the history with transfer amount to false for that fund.
*/
bool Account::Transfer(Transaction*& transferAmt, Account& accountToTransferTo)
{
	TransferTransaction* transferAmount = dynamic_cast<TransferTransaction*> (transferAmt);
	int typeOfFund = transferAmount->getTypeOfFund();
	int transFund = transferAmount->getSecondClientFundType();
	int amount = transferAmount->getAmount();

	if (amount < 0)
	{
		return false;
	}
	else
	{
		if (Withdraw(amount, typeOfFund, transferAmt))
		{
			accountToTransferTo.balance += amount;
			accountToTransferTo.balanceOfFunds[transFund] += amount;
			transferAmt->setAmount(amount);
			accountToTransferTo.hisAllTransactions[transFund].updateHistory(transferAmt, true);
			isActive[transFund] = true;
			return true;
		}
		else
		{
			accountToTransferTo.hisAllTransactions[transFund].updateHistory(transferAmt, false);
			isActive[transFund] = true;
		}
	}
	return false;
}

/*
displays history in the appropriate format.
*/
void Account::displayHistory() const
{
	cout << "Transaction History for " << firstName << " " << lastName
									   << " by fund." << endl;
	for (int i = 0; i < FUND_SIZE; i++)
	{
		if (isActive[i] != false)
		{
			cout << FUNDS[i] << ": $" << balanceOfFunds[i] << endl;
			cout << hisAllTransactions[i];
		}
	}
}

/*
displays the history by the particular funds that are active, for the account
*/
void Account::displayHistoryByFund(int typeOfFund)
{
	cout << "Transaction History for " << firstName << " " << lastName
		<< " " << FUNDS[typeOfFund] << ": $" << balanceOfFunds[typeOfFund] 
		<< endl;
	cout << hisAllTransactions[typeOfFund];
}

/*
comparison operators below for accounts, comparing order of ID
*/

bool Account::operator<(const Account& other) const
{
	return (this->id < other.id);
}

bool Account::operator<=(const Account& other) const
{
	return (this->id <= other.id);
}

bool Account::operator>(const Account& other) const
{
	return (this->id > other.id);
}

bool Account::operator>=(const Account& other) const
{
	return (this->id >= other.id);
}

bool Account::operator==(const Account& other) const
{
	return (this->id == other.id);
}

bool Account::operator!=(const Account& other) const
{
	return (this->id != other.id);
}

/*
Prints all the funds and the balance in each fund for the particular account
*/
ostream& operator<<(ostream& outStream, const Account& other)
{
	outStream << other.getFirstName() << " " << other.getLastName()
			  << " Account ID: " << other.getId() << endl;
	for (int i = 0; i < FUND_SIZE; i++)
	{
		outStream << "    " << FUNDS[i] << ": $" << other.balanceOfFunds[i] 
					<< endl;
	}
	return outStream;
}
