#include <iostream>
using namespace std;

#include <memory.h>
#include <algorithm>
#include <time.h>

class Sorter
{
public:
	virtual void sort(int arr[] , int size) const = 0;
};

class BubbleSortUp : public Sorter
{
public:
	virtual void sort(int arr[] , int size) const override
	{
		for (int i=size-1 ; i >= 0 ; i--)
		{
			for (int j=0 ; j < i ; j++)
			{
				if (arr[j] > arr[j+1])
				{
					int temp = arr[j];
					arr[j] = arr[j+1];
					arr[j+1] = temp;
				}
			}
		}
	}
};

class BubbleSortDown : public Sorter
{
public:
	virtual void sort(int arr[] , int size) const override
	{
		for (int i=size-1 ; i >= 0 ; i--)
		{
			for (int j=0 ; j < i ; j++)
			{
				if (arr[j] < arr[j+1])
				{
					int temp = arr[j];
					arr[j] = arr[j+1];
					arr[j+1] = temp;
				}
			}
		}
	}
};

class STLSort : public Sorter
{
public:
	virtual void sort(int arr[] , int size) const override
	{
		::sort(arr, arr+size);
	}
};

class IntContainer
{
private:
	IntContainer& operator=(const IntContainer&);
	IntContainer(const IntContainer& other);

	Sorter* sortStrategy;
	int *arr;	
	int size;

public:
	IntContainer(int size) : size(size)
	{
		arr = new int[size];

		srand((unsigned int)time(NULL));
		for(int i = 0 ; i < size ; i++)
			arr[i] = rand()%20;

		sortStrategy = new STLSort();
	}

	~IntContainer()
	{
		delete [] arr;
	}

	void setSortStrategy(Sorter* strategy) 
	{
		delete sortStrategy;
		sortStrategy = strategy;
	}

	void sort() {sortStrategy->sort(arr , size);}

	void display() const
	{
		for(int i = 0 ; i < size ; i++)
			cout << arr[i] << " ";
		cout << endl;
	}
};

int main()
{	
	IntContainer numbers(5);
	numbers.display();

	cout << "BubbleUp" << endl;
	numbers.setSortStrategy(new BubbleSortUp);
	numbers.sort();
	numbers.display();

	cout << "BubbleDown" << endl;
	numbers.setSortStrategy(new BubbleSortDown);
	numbers.sort();
	numbers.display();

	cout << "STL" << endl;
	numbers.setSortStrategy(new STLSort);
	numbers.sort();
	numbers.display();	
}
