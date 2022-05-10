#include "circle.h"
#include "square.h"

int main()
{
	int numOfShapes;
	Shape** allShapes;

	cout << "How many shapes? ";
	cin >> numOfShapes;
	allShapes = new Shape*[numOfShapes];

	for (int i = 0; i < numOfShapes ; i++) {
		int choice;

		cout << "\nChoose 1 for Square, 2 for Circle: ";
		cin >> choice;

		switch (choice)
		{
		case 1: // Square
		{  
			char color[20];
			int len, width;

			cout << "Enter square's color: ";
			cin >> color;
			cout << "Enter square's width: ";
			cin >> width;
			cout << "Enter square's len: ";
			cin >> len;

			allShapes[i] = new Square(color, width, len);
			break;
		}
		case 2: // Circle
		{ 
			char color[20];
			int radius, width;

			cout << "Enter square's color: ";
			cin >> color;
			cout << "Enter square's width: ";
			cin >> width;
			cout << "Enter square's radius: ";
			cin >> radius;

			allShapes[i] = new Circle(color, width, radius);
			break;
		}
		default:
			cout << "Invalid choice" << endl;
			i--;
			break;
		}
	}

	
	for (int i = 0; i < numOfShapes ; i++) {
		cout << endl << *allShapes[i] << endl;
		Square* s = dynamic_cast<Square*>(allShapes[i]);
		if (s) {
			s->draw();
		}
	}

	for (int i = 0; i < numOfShapes; i++)
		delete allShapes[i];
	delete[]allShapes;
}