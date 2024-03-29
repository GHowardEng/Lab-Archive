// ELEX 4618 Grade System
// Grant Howard 
// A00970152

#include "stdafx.h"
#include <iostream>
#include <iomanip>
using namespace std;

void print_menu(void);
void add_student(void);
void edit_student(int index);
void print_grades(void);
float calculate_final(float lab, float quiz, float midterm, float finalExam);

struct grades		// structure containing grade components
{
	char studentNumber[9];
	float lab;
	float quiz;
	float midterm;
	float finalExam;
	float finalGrade;
};

grades students[100];		// Grade array to store student information

int number_of_students = 0;

int main()
{
	char cmd;
	int num;

	cout.setf(ios::fixed);

	do
	{
		print_menu();	// Display menu after each operation

		cin >> cmd;		// Retreive user command

		if (cmd == 'a' || cmd == 'A')		// Sequence to test command and execute selected function
		{
			add_student();
		}

		else if (cmd == 'e' || cmd == 'E')
		{
			cout << "\nStudent to Edit: ";		// Get student entry to be edited from user 
			cin >> num;			
			edit_student(num);
		}

		else if (cmd == 'p' || cmd == 'P')
		{
			print_grades();
		}
	} while (!(cmd == 'q' || cmd == 'Q'));

    return 0;
}

/////////////////////////////////////////////////////////
// print_menu function displays menu on console
/////////////////////////////////////////////////////////
void print_menu(void)
{
	cout << "\n\n****************************************";
	cout << "\n\nELEX 4618 Grade System, by Grant Howard";
	cout << "\n\n****************************************";
	cout << "\n\n(A)dd Student";
	cout << "\n\n(E)dit Student";
	cout << "\n\n(P)rint Grades";
	cout << "\n\n(Q)uit";
	cout << "\n\nCommand> ";
}

/////////////////////////////////////////////////////////
// add_student function adds student information to list
/////////////////////////////////////////////////////////
void add_student(void)
{
	number_of_students += 1;	// Increment number of students

	cout << "\nAdding Student\n";

	edit_student(number_of_students);
}

/////////////////////////////////////////////////////////
// edit_student function allows information of student in list to be changed
/////////////////////////////////////////////////////////
void edit_student(int index)
{
	if (index > number_of_students || index <= 0)	// If index out of range
	{
		cout << "\nStudent not found.";		// Error message
	}

	else
	{
		index -= 1;		// Decrement for zero indexing

		cout << "\nStudent Number: ";	// Get student information from user
		cin >> students[index].studentNumber;

		cout << "Lab Grade: ";
		cin >> students[index].lab;

		cout << "Quiz Grade: ";
		cin >> students[index].quiz;

		cout << "Midterm Grade: ";
		cin >> students[index].midterm;

		cout << "Final Exam Grade: ";
		cin >> students[index].finalExam;

		// Calculate final grade
		students[index].finalGrade = calculate_final(students[index].lab, students[index].quiz, students[index].midterm, students[index].finalExam);
	}
}

/////////////////////////////////////////////////////////
// print_grades function prints formatted table with all student information
/////////////////////////////////////////////////////////
void print_grades(void)
{
	static int index;
	
	if (number_of_students == 0)		// If no students stored
	{
		cout << "\nNo students found. Use (A)dd command.";		// Error message
	}

	else
	{
		cout << left << setw(6) << "\n#";		// Print formatted table header
		cout << setw(14) << "Student";
		cout << setw(10) << "Lab"; 
		cout << setw(10) << "Quiz"; 
		cout << setw(12) << "Midterm";
		cout << setw(14) << "Final Exam";
		cout << setw(12) << "Final Grade";

		for (index = 0; index < number_of_students; index++)		// Print formatted information of each student
		{
			cout << setprecision(1) << "\n" << setw(5) << index + 1;
			cout << setw(14) << students[index].studentNumber;
			cout << setw(10) << students[index].lab;
			cout << setw(10) << students[index].quiz;
			cout << setw(12) << students[index].midterm; 
			cout << setw(14) << students[index].finalExam; 
			cout << setw(12) << students[index].finalGrade;
		}
	}
}

/////////////////////////////////////////////////////////
// calcFinal function returns weighted final grade
/////////////////////////////////////////////////////////
float calculate_final(float lab, float quiz, float midterm, float finalExam)
{
	return (lab * 0.4 + quiz * 0.1 + midterm * 0.2 + finalExam * 0.3);
}


