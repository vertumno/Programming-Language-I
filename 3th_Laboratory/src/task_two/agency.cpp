/**
 * @file	agency.cpp
 * @brief	Implementing functions described in agency.h 		    
 * @author	Lucas Gomes Dantas (dantaslucas@ufrn.edu.br)
 * @since	20/10/2017
 * @date	21/10/2017
 */

#include "task_two/agency.h"

Agency::Agency() {}
Agency::Agency(string number) : agency_number(number) { /* empty */ }
Agency::~Agency() {}

string Agency::getNumber() { return agency_number; }

void Agency::createAccount() 
{
	string number;
	double overdraft;
	int stat;
	
	cout << endl << "Enter the account number (you can write it with dots and hyphens): " << endl;
	cin >> number;
	
	cout << endl << "Enter the limit for overdraft: " << endl;
	cin >> overdraft;
	
	cout << endl << "You are creating an special or a common account?" << endl;
	cout << "Special = 0, Common = 1 " << endl;
	cin >> stat;
	while(stat > 1 or stat < 0)
	{
		cout << endl << "Invalid option. Please try again: " << endl;
		cin >> stat;
	}
	Status s = stat == 0 ? Status::special : Status::common;	

	auto new_account = make_shared<Checking_Account>(agency_number, number, s, overdraft);

	for(auto i = accounts.begin(); i != accounts.end(); ++i)
	{
		if(**i == *new_account) 
		{ 
			cout << endl << "Could not create account. Same number already used in this agency." << endl;
			return;
		}
	}
	accounts.push_back(new_account);
	cout << endl << "Account successfully created!" << endl;
}

vector<shared_ptr<Checking_Account>>::iterator Agency::findAccount(string const number)
{
	for (auto i = accounts.begin(); i != accounts.end(); ++i)
	{
		if ( (**i).getNumber().compare(number) == 0 )
			return i;
	}
	vector<shared_ptr<Checking_Account>>::iterator i(accounts.end());
	return i;	
}

void Agency::deleteAccount(string const number)
{
	char c;
	auto account = findAccount(number);
	if(account != accounts.end())
	{
		cout << "Account found. This is an irreversible action. You trully want to do this? (y/n)" << endl;
		cin >> c;
		while(c != 'y' and c != 'n')
		{
			cout << "Invalid option. Please try again: " << endl;
			cin >> c;
		}
		if(c == 'n') { cout << "Okay, you chose to cancel. " << endl; return; }
		else { cout << "Okay, deleting account." << endl; accounts.erase(account); return; }
	}
	cout << endl << "No account with the provided number was found in this agency." << endl;		
}

void Agency::checkBalance(string const number)
{
	auto account = findAccount(number);
	if(account != accounts.end())
	{
		cout << endl << "Your current balance is R$" << (**account).getBalance() << endl;
		return;
	}
	cout << endl << "No account with the provided number was found in this agency." << endl;	
}

void Agency::checkAvailableLimit(string const number)
{
	auto account = findAccount(number);
	if(account != accounts.end())
	{
		cout << endl << "Initial limit: R$" << (**account).getLimit() << endl;	
		cout << "Available limit: R$" << (**account).getAvailableLimit() << endl;
		return;
	}
	cout << endl << "No account with the provided number was found in this agency." << endl;	
}

void Agency::cashOut(string const number, double const money)
{
	auto account = findAccount(number);
	if(account != accounts.end())
	{
		double cash = (**account).getBalance() - money;
		if(cash < 0.00 and (cash + (**account).getAvailableLimit()) >= 0.00 )
		{
			(**account).setBalance(cash);
			(**account).setAvailableLimit( cash + (**account).getAvailableLimit() );
			cout << endl << "Cash out performed with success." << endl;
			(**account).addTransaction( new Transaction("Cash out", money, Style::debit) );
		}
		else if (cash < 0.00 and (cash + (**account).getAvailableLimit()) < 0.00 )
		{
			cout << endl << "You don't have enough money to perform this action." << endl;
		}	
		else
		{
			(**account).setBalance(cash);
			cout << endl << "Cash out performed with success." << endl;
			(**account).addTransaction( new Transaction("Cash out", money, Style::debit) );
		}
		return;		
	}
	cout << endl << "No account with the provided number was found in this agency." << endl;	
}

void Agency::cashIn(string const number, double const money)
{
	auto a = findAccount(number);
	if(a != accounts.end())
	{
		(**a).setBalance( (**a).getBalance() + money );
		(**a).addTransaction( new Transaction("Cash in", money, Style::credit) );
		if( (**a).getAvailableLimit() < (**a).getLimit() )
			(**a).setAvailableLimit((**a).getBalance() >= 0 ? (**a).getLimit() : (**a).getBalance());
		return;
	}
	cout << endl << "No account with the provided number was found in this agency." << endl;	
}

void Agency::transference(string const number, string const other, double money)
{
	auto account_one = findAccount(number);
	auto account_two = findAccount(other);
	if( account_one != accounts.end() and account_two != accounts.end() )
	{
		cashOut(number, money);
		cashIn(other, money);
		return;
	}
	cout << endl << "At least one of the provided accounts was not found in this agency." << endl;	
}

void Agency::printBankStatement(string const number)
{
	auto account = findAccount(number);
	if( account != accounts.end() )
	{
		cout << endl << "TRANSACTIONS MADE WITH THIS ACCOUNT" << endl;
		cout << (**account) << endl;
		return;
	}
	cout << endl << "No account with the provided number was found in this agency." << endl;	
}