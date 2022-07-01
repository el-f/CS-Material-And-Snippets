#include <iostream>
#include <string>
using namespace std;

class Customer
{
private:
	string name;
	int    totalSaving;
    int    creditLineScore;
	bool   hasBadCredit;

public:
    Customer(const string& name, int totalSaving, 
					int creditLineScore, bool badCredit) 
				: name(name), totalSaving(totalSaving), 
				  creditLineScore(creditLineScore), hasBadCredit(badCredit) {}

	const string& getName()    const {return name;}
	int   getTotalSaving()     const {return totalSaving;}
	int   getCreditLineScore() const {return totalSaving;}
	bool  getHasBadCredit()    const {return hasBadCredit;}

	operator const char*() const {return name.c_str();}
}; // Customer

class Bank
{
public:
	static const double LOAN_TO_SAVING_RATIO;

    bool hasSufficientSavings(const Customer& c, int requestedmortgageValue) const
    {
        return
            c.getTotalSaving()/(double)requestedmortgageValue > LOAN_TO_SAVING_RATIO;
    }
}; // Bank

const double Bank::LOAN_TO_SAVING_RATIO = 0.5;

class CreditHistory
{
public:
	static const double MINIMUM_CREDIT_LINE_SCORE;

    bool hasGoodCredit(const Customer& c) const
    {
        return c.getCreditLineScore() >= MINIMUM_CREDIT_LINE_SCORE;
    }
}; // CreditHistory

const double CreditHistory::MINIMUM_CREDIT_LINE_SCORE = 610;

class LoanHistory
{
public:
	static const double MINIMUM_CREDIT_LINE_SCORE;
    
    bool hasNoBadLoans(const Customer& c) const
    {
		return c.getHasBadCredit();
    }

    bool hadBadLoans(const Customer& c) const
    {
		return c.getCreditLineScore() > MINIMUM_CREDIT_LINE_SCORE;
    }
}; // LoanHistory

const double LoanHistory::MINIMUM_CREDIT_LINE_SCORE = 680;

class Mortgage
{
    virtual bool isEligible(const Customer& customer, int requestedmortgageValue) const = 0;
}; // IMortgage

class MortgageFacade : public Mortgage
{
public:
    bool isEligible(const Customer& customer, int requestedmortgageValue) const
    {
		cout << customer << " applies for " << requestedmortgageValue << " loan\n";

        // Check creditworthyness of applicant 
        cout << "Check " << customer << " bank for saving / loan ratio\n";
        if (!bank.hasSufficientSavings(customer, requestedmortgageValue))
        {
            cout << "Bad saving / loan ratio, go to another bank\n";
            return false;
        }
		cout << "--> Pass\n\n";

        cout << "Check " << customer << " credit line";
        if (!credit.hasGoodCredit(customer))
        {
			cout <<	"Poor credit line, go to another bank\n";
            return false;
        }
        cout << "--> Pass\n\n";

        cout << "Check " << customer  << " previous loan recored\n";
        if (loan.hasNoBadLoans(customer))
        {
			cout << "Found bad loan recored, recheck credit line\n";

            if (!loan.hadBadLoans(customer))
            {
                cout << "Found bad loan recored, and credit line is not high enough, go to another bank\n";
                return false;
            }
        }
        cout << "--> Pass\n\n";
        return true;
    }

private:
	Bank bank;
    LoanHistory loan;
    CreditHistory credit;

}; // MortgageFacade

void main()
{
	MortgageFacade mortgage;
    bool isEligable;

    // Evaluate mortgage eligibility for customer 
    Customer c1("gogo", 35000, 550, false);
    isEligable = mortgage.isEligible(c1, 250001);
    cout << c1 << " has been " << (isEligable ? "Approved" : "Rejected") << endl;

    Customer c2("momo", 500000, 620, true);
    isEligable = mortgage.isEligible(c2, 200000);
    cout << c2 << " has been " << (isEligable ? "Approved" : "Rejected") << endl;

    Customer c3("yoyo", 375000, 720, true);
    isEligable = mortgage.isEligible(c3, 200000);
    cout << c3 << " has been " << (isEligable ? "Approved" : "Rejected") << endl;
}
