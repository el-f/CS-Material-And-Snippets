#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Visitable;

class Visitor
{
public:
	virtual void visit(Visitable* element) = 0;
};

class Visitable
{
public:
	virtual void accept(Visitor* visitor) = 0;
};


class Employee : public Visitable
{
public:
	Employee(string name , int salary , int holidays) : 
	  name(name) , salary(salary) , leftVacationDays(holidays) 	{}

	virtual void accept(Visitor* visitor) override	{visitor->visit(this);}
	void giveRaise(int money)	{salary += money;}
	void modifyDays(int days)	{leftVacationDays += days;}
	void display() const
	{
		cout << name << " earns " << salary << "$ and has " << leftVacationDays << " vacation days left." << endl;
	}
private:
	int leftVacationDays;
	int salary;
	string name;
};

class IncomeVisitor : public Visitor
{
public:
	IncomeVisitor(int money) : money(money) {}

	virtual void visit(Visitable* element) override
	{
		Employee* emp = (Employee*)element;
		emp->giveRaise(money);
	}
private:
	int money;
};


class VacationVisitor : public Visitor
{
public:
	VacationVisitor(int days) : days(days) {}

	virtual void visit(Visitable* element ) override
	{
		Employee* emp = (Employee*)element;
		emp->modifyDays(days);
	}
private:
	int days;
};


class Department
{
public:

	void add(Employee* pNewEmp)
	{
		employees.push_back(pNewEmp);
	}

	void accept(Visitor* visitor)
	{
		vector<Employee*>::iterator itr    = employees.begin();
		vector<Employee*>::iterator itrEnd = employees.end();
		for ( ; itr != itrEnd ; ++itr)
			(*itr)->accept(visitor);
	}

	void display() const
	{
		vector<Employee*>::const_iterator itr    = employees.begin();
		vector<Employee*>::const_iterator itrEnd = employees.end();
		for ( ; itr != itrEnd ; ++itr)
			(*itr)->display();

		cout << endl << endl;
	}
private:
	vector<Employee*> employees;
};

void main()
{
	Department HR;

	HR.add(new Employee("momo" , 10000 , 14));
	HR.add(new Employee("gogo" , 12000 , 23));
	HR.add(new Employee("yoyo" , 18000 , 10));
	HR.add(new Employee("koko" , 5600 , 9));

	HR.display();

	// here the company went on a 2 days trip 2 Eilat
	HR.accept(new VacationVisitor(-2));
	cout << "After Vacation..." << endl;
	HR.display();

	// here the company was sold to Microsoft
	HR.accept(new IncomeVisitor(2000));
	cout << "After Sale..." << endl;
	HR.display();
}
