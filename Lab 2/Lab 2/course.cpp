
#include "stdafx.h"
#include "course.h"
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>
#include <cstddef>

using namespace std;

void CCourse::print_menu(void)
{
	cout << "\n\n****************************************";
	cout << "\n\nELEX 4618 Grade System, by Grant Howard";
	cout << "\n\n****************************************";
	cout << "\n\n(A)dd Student";
	cout << "\n\n(E)dit Student";
	cout << "\n\n(D)elete Student";
	cout << "\n\n(P)rint Grades";
	cout << "\n\n(S)ave";
	cout << "\n\n(L)oad";
	cout << "\n\n(Q)uit";
	cout << "\n\nCommand> ";
}

void CCourse::add_student(void)
{
	CStudent tempStudent;

	cout << "\nAdding Student\n";

	students.push_back(tempStudent);

	edit_student(students.size());
}

void CCourse::edit_student(unsigned int index)
{
	string temp;
	int err = 0;
	unsigned int i;
	int flag = 0;

	

	if (index > students.size() || index <= 0)	// If index out of range
	{
		cout << "\nStudent not found.";		// Error message
	}

	else
	{
		index -= 1;		// Decrement for zero indexing

		do
		{
			cout << "\nStudent Number: ";			// Get student information from user
			cin >> students[index].studentNumber;	// Sequence to error check input
			
			if (students[index].studentNumber[0] == 'A' && students[index].studentNumber[1] == '0' && (students[index].studentNumber[2] == '1' || students[index].studentNumber[2] == '0'))
			{
				err = 0;
			}

			else
			{
				err = 1;
				cout << "\nStudent number must start with A00 or A01\n";
			}
			
			for (i = 3; i < students[index].studentNumber.size(); i++)
			{
				if (students[index].studentNumber[i] > '9' || students[index].studentNumber[i] < '0')
				{		
					flag = 1;
				}
			}

			if (flag)
			{
				flag = 0;
				cout << "\nStudent number can only contain numbers.\n";
				err = 1;
			}

			if (students[index].studentNumber.length() != 9)
			{
				err = 1;
				cout << "\nStudent number must be 9 characters.\n";
			}
		} while (err);

		do
		{
			cout << "Lab Grade: ";
			cin >> temp;

			err = check_input(temp);
		} while (err);

		students[index].lab = stof(temp);


		do
		{
			cout << "Quiz Grade: ";
			cin >> temp;

			err = check_input(temp);
		} while (err);

		students[index].quiz = stof(temp);

		do
		{
			cout << "Midterm Grade: ";
			cin >> temp;

			err = check_input(temp);
		} while (err);

		students[index].midterm = stof(temp);

		do
		{
			cout << "Final Exam Grade: ";
			cin >> temp;

			err = check_input(temp);
		} while (err);

		students[index].finalExam = stof(temp);

		// Calculate final grade
		students[index].finalGrade = calculate_final(students[index].lab, students[index].quiz, students[index].midterm, students[index].finalExam);
	}
}

void CCourse::delete_student(void)
{
	unsigned int index;
	string input;

	if (students.size())		// If entries stored
	{
		cout << "\nSelect student to delete: ";
		cin >> input;

		if (input[0] <= '9' && input[0] >= '0')		// Check input value
		{
			index = stoi(input);

			if (index > students.size() || index <= 0)
			{
				cout << "\nStudent not found.\n";
			}

			else
			{
				index -= 1;		// Decrement index to represent offset from beginning of vector
				students.erase(students.begin() + index);	// Erase selected entry
			}
		}

		else
		{
			cout << "\nPlease enter a positive integer.\n";		// Error message
		}
	}
	else
	{
		cout << "\nNo students found. Use (A)dd or (L)oad.";		// Error message
	}
}

void CCourse::save(void)
{
	ofstream outfile;
	string fileName;
	unsigned int index;
	if (students.size())
	{
		cout << "\nSave to file.\n\n.txt file name: ";
		cin >> fileName;
		if (fileName[fileName.length() - 1] == 't' && fileName[fileName.length() - 2] == 'x' && fileName[fileName.length() - 3] == 't' && fileName[fileName.length() - 4] == '.')
		{
			outfile.open(fileName);
			outfile << students.size() << " ";

			for (index = 0; index < students.size(); index++)
			{
				outfile << students[index].studentNumber << " " << students[index].lab << " " << students[index].quiz << " " << students[index].midterm << " " << students[index].finalExam << " " << students[index].finalGrade << "\n";
			}

			cout << "\nSuccesfully saved " << students.size() << " entries to " << fileName;
			outfile.close();
		}

		else
		{
			cout << "\nfile must have .txt extension.";
		}
	}
	else
	{
		cout << "\nNo students found. Use (A)dd or (L)oad.";		// Error message
	}
}

void CCourse::load(void)
{
	ifstream infile;
	string fileName;
	unsigned int index = 0;
	CStudent tempStudent;
	int num_students;

	cout << "\nLoad from file.\n\n.txt file name: ";
	cin >> fileName;

	if (fileName[fileName.length() - 1] == 't' && fileName[fileName.length() - 2] == 'x' && fileName[fileName.length() - 3] == 't' && fileName[fileName.length() - 4] == '.')
	{
		infile.open(fileName);
		if (infile.is_open())
		{
			students.clear();
			infile >> num_students;
			cout << "\nSuccesfully loaded " << num_students << " entries from " << fileName;
			
			while (num_students > 0)
			{
				students.push_back(tempStudent);
				infile >> students[index].studentNumber >> students[index].lab >> students[index].quiz >> students[index].midterm >> students[index].finalExam >> students[index].finalGrade;

				index++;
				num_students--;
			}
			infile.close();
		}
		else
		{
			cout << "\nFile " << fileName << " not found.";
		}
	}

	else
	{
		cout << "\nFile must have .txt extension.";
	}
}

void CCourse::print_grades(void)
{
	unsigned int index;

	if (students.size() == 0)		// If no students stored
	{
		cout << "\nNo students found. Use (A)dd or (L)oad.";		// Error message
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

		for (index = 0; index < students.size(); index++)		// Print formatted information of each student
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

int CCourse::check_input(string input)
{
	int err = 0;
	float temp;

	// Error checking sequence for each input

	err = input.find_first_not_of("0123456789.") == string::npos;		// Search string for invalid characters

	if (!err)		// find_first_not_of returns zero if text out of range (active low)
	{
		err = 1;	// Invert
		cout << "\nGrade can only contain positive numbers.\n";		// Error message
	}
	else
	{
		err = 0;
		temp = stof(input);		// Convert input string to float

		if (temp > 100 || temp < 0)			// Test for range
		{
			err = 1;
			cout << "\nGrade must be between 0 and 100.\n";
		}
	}

	return err;
}

float CCourse::calculate_final(float lab, float quiz, float midterm, float finalExam)
{
	return (lab * 0.4 + quiz * 0.1 + midterm * 0.2 + finalExam * 0.3);
}