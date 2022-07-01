#include <iostream>
#include <time.h>
using namespace std;

class Request
{
protected:
	Request() {}

public:
	virtual ~Request() {};
};

class Handler
{
protected:
	Handler* nextHandler;

	Handler(Handler* nextHandler=nullptr) : nextHandler(nextHandler) {}

public:
	void setNextHandler(Handler* nextHandler) { this->nextHandler = nextHandler; }
	virtual void handleRequest(const Request& request) = 0;
};

class TakeMortgageRequest : public Request
{
private:
	int mortgageValue;
	int propertyValue;
	int assessmentValue;
	int nettoSalary;

public:
	TakeMortgageRequest(int propertyValue, int mortgageValue, int nettoSalary)
		: propertyValue(propertyValue), mortgageValue(mortgageValue), nettoSalary(nettoSalary) {}
	~TakeMortgageRequest() {}

	int getMortgageValue()                 const { return mortgageValue; }
	int getPropertyValue()                 const { return propertyValue; }
	int getAssessmentValue()               const { return assessmentValue; }
	int getNettoSalary()                   const { return nettoSalary; }

	void setAssessmentValue(int assessmentValue) { this->assessmentValue = assessmentValue; }
};

class CheckLoanRatioHandler : public Handler
{
	virtual void handleRequest(const Request& request) override
	{
		TakeMortgageRequest& theMortgage = (TakeMortgageRequest&)request;

		double loanRatio = theMortgage.getMortgageValue() / (double)theMortgage.getPropertyValue();
		cout << "In CheckLoanRatioHandler: loanRatio=" << loanRatio << endl;

		if (loanRatio > 0.7)
		{
			cout << "*** Sorry, cannot get mortgage with loan ratio of " << loanRatio << endl;
		}
		else
		{
			if (nextHandler != nullptr)
				nextHandler->handleRequest(request);
			else
				cout << "Mortgage is approved!\n";
		}
	}
};

class CheckReturnsAbilityHandler : public Handler
{
	virtual void handleRequest(const Request& request) override
	{
		TakeMortgageRequest& theMortgage = (TakeMortgageRequest&)request;
		
		int returnedPerMonth = theMortgage.getMortgageValue() / 30 / 12;
		cout << "In CheckReturnsAbilityHandler: returnedPerMonth=" << returnedPerMonth << " and your netto salary is " << theMortgage.getNettoSalary() << endl;
		if (returnedPerMonth > theMortgage.getNettoSalary()/3)
		{
			cout << "*** Sorry, cannot get mortgage which returns more than 1/3 of your salary" << endl;
		}
		else
		{
			if (nextHandler != nullptr)
				nextHandler->handleRequest(request);
			else
				cout << "Mortgage is approved!\n";
		}
	}
};

class CalcPropoeryAssessmentHandler : public Handler
{
	virtual void handleRequest(const Request& request) override
	{
		TakeMortgageRequest& theMortgage = (TakeMortgageRequest&)request;
	
		theMortgage.setAssessmentValue(theMortgage.getPropertyValue() + (rand()%800000-400000));
		cout << "The propery's assessment is " << theMortgage.getAssessmentValue() << endl;
		
		if (nextHandler != nullptr)
			nextHandler->handleRequest(request);
		else
			cout << "Mortgage is approved!\n";
	}
};

int main()
{
	srand((int)time(NULL));

	//configure Chain of Responsibility 
	Handler* h1 = new CheckReturnsAbilityHandler();
	Handler* h2 = new CalcPropoeryAssessmentHandler(); // Note: this can not be the last in the chain
	Handler* h3 = new CheckLoanRatioHandler();
	h1->setNextHandler(h2);
	h2->setNextHandler(h3);

	//calling chain of responsibility 
	cout << "Mortgage request #1:\n";
	h1->handleRequest(TakeMortgageRequest(2725000, 1575000, 10000));

	cout << "\nMortgage request #2:\n";
	h1->handleRequest(TakeMortgageRequest(2725000, 2500000, 30000));

	cout << "\nMortgage request #3:\n";
	h1->handleRequest(TakeMortgageRequest(2725000, 1575000, 20000));


	delete h1;
	delete h2;
	delete h3;
}
