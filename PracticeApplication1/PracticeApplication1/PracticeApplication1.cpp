// PracticeApplication1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
using namespace std;



int main()
{
	int num1;
	int num2;
	int average;
	int *result;
	char repeat;

	result = &average;

	printf("Average Calculator by Grant Howard");
	do
	{
	cout << "\n\nEnter first number: ";

	cin >> num1;

	cout << "\nEnter second number: ";

	cin >> num2;

	*result = (num1 + num2) / 2;

	cout << "\nThe average is " << average;

	cout << "\n\nRun again? (y/n): ";

	cin >> repeat;
	} while (repeat == 'y');
	
    return 0;
}

