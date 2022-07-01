#include <iostream>
using namespace std;

class Account 
{
public:
    // Abstract Methods
    virtual void start() const = 0;
    virtual void allow() const = 0;
    virtual void end() const = 0;
    virtual int maxLimit() const = 0;

    // Template Method
    void withdraw(int mortgageValue) const 
	{
        start();
        int limit = maxLimit();
        if (mortgageValue < limit) 
			allow();
        else 
			cout << "Not allowed" << endl;
        end();
    }
}; // Account

class AccountNormal : public Account 
{
public:
	virtual void start()   const {cout << "AccountNormal::start ..." << endl;}
    virtual void allow()   const {cout << "AccountNormal""allow ..." << endl;}
	virtual void end()     const {cout << "AccountNormal::end ..." << endl;}
    virtual int maxLimit() const  {return 1000;}
}; // AccountNormal

class AccountPower : public Account 
{
public:
	virtual void start()   const {cout << "AccountPower::start ..." << endl;}
	virtual void allow()   const {cout << "AccountPower::allow ..." << endl;}
	virtual void end()     const {cout << "AccountPower::end ..." << endl;}
    virtual int maxLimit() const {return 5000;}
}; // AccountPower

int main() 
{
    AccountPower power;
    power.withdraw(1500);
	cout << "--------------------------\n";
    AccountNormal normal;
    normal.withdraw(1500);
}