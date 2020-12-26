#include <stdlib.h>
#include <stdio.h>
#include "studentBinary.h"
#include "studentText.h"

#define TEXT_FILE "StudentsT.txt"
#define BIN_FILE "StudentsB.bin"

//#define TEXT_TO_BIN

void TextToBin();
void BinToText();

void main()
{
#ifdef TEXT_TO_BIN
	TextToBin();
#else
	BinToText();
#endif
	
	
	system("pause");
}

void TextToBin()
{
	Student* arr;
	int count;

	arr = readStudentArrFromTextFile(TEXT_FILE, &count);

	showStudentArr(arr, count);

	writeStudentArrToBFile(BIN_FILE, arr, count);
//	addStudentToEndOfBFile(BIN_FILE);

	freeStudentArr(arr, count);

}

void BinToText()
{
	Student* arr;
	int count;

	arr = readStudentArrFromBFile(BIN_FILE, &count);

	showStudentArr(arr, count);

	writeStudentArrToTextFile(TEXT_FILE, arr, count);
//	addStudentToEndOfTextFile(TEXT_FILE);

	freeStudentArr(arr, count);
}