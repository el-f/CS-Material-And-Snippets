// Initialize		O(1)
{
	int S[100];
	int top = 0;           // אינדקס של המקום הפנוי הבא
}

bool isEmpty()		O(1)
{
	return (top == 0);	
}

bool isFull()		O(1)
{
	rturn (top == 100)
}

void Push(int x)		O(1)
{
       if (!isFull()) {
	S[top] = x;
	top++;
        }
        else // טיפול בשגיאה
}

int Pop()			O(1)
{
       if (!isEmpty()  {
	top--;
	return S[top];
        }
        else // error handling
}

int Top()			O(1)
{
        if (!isEmpty()
	return S[top-1];
        else // error handling
}


---------


// אתחול
{
	int S[100];
	int top = -1;     // אינדקס של ראש המחסנית
}

bool isEmpty()
{
	return (top == -1);	
}

bool isFull()
{
	rturn (top == 99)
}

void Push(int x)
{
       if (!isFull()) {
	top++;
	S[top] = x;
        }
        else // טיפול בשגיאה
}

int Pop()
{
       if (!isEmpty()  {
	top--;
	return S[top+1];
        }
        else // error handling

}

int Top()
{
        if (!isEmpty()
	return S[top];
        else // error handling
}


