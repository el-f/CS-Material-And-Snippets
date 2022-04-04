/* Code written by Elad Cohen, Edited and Fixed by Keren Kalif */

#include <iostream>
using namespace std;

#include "shape.h"
#include "square.h"
#include "circle.h"

enum eShapeType { SQUARE = 1, CIRCLE };

int main() {
	Shape** shapes;
	int shapesSize;

	cout << "Please enter num of shapes:" << endl;
	cin >> shapesSize;
	shapes = new Shape * [shapesSize];

	for (int i = 0; i < shapesSize; i++)
	{
			int shapeType;
			float frameWidth;
			char color[30];

			cout << "Shape #" << i + 1 << " - Enter 1 for square or 2 for circle:" << endl;
			cin >> shapeType;

			cout << "Please enter the frameWidth and the color:" << endl;
			cin >> frameWidth >> color;

			switch (shapeType)
			{
			case SQUARE:
			{
				bool validInput = false;
				while (validInput == false)
				{
					try
					{
						float sideLength;

						cout << "Please enter the side length:" << endl;
						cin >> sideLength;
						shapes[i] = new Square(frameWidth, color, sideLength);
						validInput = true;
					}
					catch (SquareException& e)
					{
						e.show();
						cout << "Enter input again...\n";
					}
				}

				break;
			}
			case CIRCLE:
			{
				bool validInput = false;
				while (validInput == false)
				{
					try
					{
						float radius;

						cout << "Please enter the radius:" << endl;
						cin >> radius;

						shapes[i] = new Circle(frameWidth, color, radius);
						validInput = true;
					}
					catch (CircleException& e)
					{
						e.show();
						cout << "Enter input again...\n";
					}
				}
				break;
			}
			default:
				cout << "Invalid choice, try again..\n";
				i--;
				break;
		}
	}

	for (int i = 0; i < shapesSize; i++) {
		cout << *shapes[i];
		cout << endl;

		Square* square = dynamic_cast<Square*>(shapes[i]);
		if (square)
		{
			square->draw();
		}
	}

	for (int i = 0; i < shapesSize; i++)
		delete[]shapes[i];

}

/*int main() {
	Shape **shapes;
	int shapesSize;

	cout << "Please enter the amount of shapes:" << endl;
	cin >> shapesSize;
	shapes = new Shape*[shapesSize];

	for (int i = 0; i < shapesSize; i++)
	{
		try
		{
			int shapeType;
			float frameWidth;
			char color[30];

			cout <<"Shape #"<<i+1<< " - Enter 1 for square or 2 for circle:" << endl;
			cin >> shapeType;

			cout << "Please enter the frameWidth and the color:" << endl;
			cin >> frameWidth >> color;

			switch (shapeType)
			{
			case SQUARE:
			{
				float sideLength;

				cout << "Please enter the side length:" << endl;
				cin >> sideLength;

				shapes[i] = new Square(frameWidth, color, sideLength);

				break;
			}
			case CIRCLE:
			{
				float radius;

				cout << "Please enter the radius:" << endl;
				cin >> radius;

				shapes[i] = new Circle(frameWidth, color, radius);

				break;
			}
			default:
				cout << "Invalid choice, try again..\n";
				i--;
				break;
			}
		}
		catch (CircleException& c)
		{
			c.show();
			i--;
		}
		catch (SquareException& s)
		{
			s.show();
			i--;
		}
		catch (...)
		{
			cout << "please contact support!\n";
			i--;
		}
	}

	for (int i = 0; i < shapesSize; i++) {
		cout << *shapes[i];
		cout << endl;

		Square* square = dynamic_cast<Square*>(shapes[i]);
		if (square)
		{
			square->draw();
		}
	}

	for (int i = 0; i < shapesSize; i++)
		delete[]shapes[i];
}*/