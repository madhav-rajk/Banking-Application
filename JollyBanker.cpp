#include <iostream>
#include <string>
#include "Bank.h"

using namespace std;

//takes the file through the argc, argv and then reads it first to 
//make sure file exists, then executes the text and then shows 
//the history of all the accounts.
int main(int argc, char* argv[])
{
	Bank jollyBank;
	jollyBank.readText(argv[1]);
	jollyBank.executeText();
	jollyBank.displayAccounts();

	return 0;
}