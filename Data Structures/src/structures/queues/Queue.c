
// Initialize		O(1)
{
	int Q[100];
	int front = 0;           // ראש התור
	int back = 0;	// סוף התור
	int size = 0	// מספר הערכים בתור
}

bool isEmpty()		// O(1)
{
	return (size == 0);	
}

bool isFull()		// O(1)
{
	return (size == 100)
}

void Enqueue(int x)		// O(1)
{
    if (!isFull()) {
	    Q[back] = x;
	    back++;
	    if (back == 100)
	        back = 0;
    }
    else // טיפול בשגיאה
}

int Dequeue()		// O(1)
{
    if (!isEmpty()  {
	    front++;
	    if (front == 100)
	        front = 0;
	    return Q[front-1];
    }
    else // error handling
}

int Peek()			// O(1)
{
    if (!isEmpty())
	    return Q[front];
    else // error handling
}


---------


// Find the fifth in line
// 1. OK to change the queue

for (i = 0; i<5; i++)
	a = myQ.Dequeue();


// 2. Queue stays the same. There are more than 5 elements in the queue.
	
	for (i = 0; i<4; i++)
	{
		Enqueue(myQ.Dequeue());
	}
	a = myQ.Peek();    // this is the fifth element
	for (i=0; i<size-4; i++)
		Enqueue(myQ.Dequeue());
		
	