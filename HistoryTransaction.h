#ifndef HISTORYTRANSACTION_H
#define HISTORYTRANSACTION_H

#pragma once

#include "Transaction.h"


class HistoryTransaction : public Transaction
{
public:
	//constructor
	HistoryTransaction();
	HistoryTransaction(istream& inStream);

	//need to call virtual since we are using inheritance for the class
	virtual ~HistoryTransaction();

	//actions for the HistoryTransaction class
	void updateHistory(Transaction* transToAdd, bool valid);
	bool IfValid() const;

	//function for io stream operator overloading
	friend ostream& operator<<(ostream& outStream,
		const HistoryTransaction& other);

private:
	vector<string> transHistory;
};


#endif