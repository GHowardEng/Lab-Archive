// ELEX 4618 Improved Grade System
// Grant Howard 
// A00970152

#include "stdafx.h"
#include "course.h"


using namespace std;

int main()
{
	char cmd;
	string num;
	int index;
	int err = 0;
	
	CCourse Course1;

	cout.setf(ios::fixed);

	do
	{
		Course1.print_menu();	// Display menu after each operation

		cin >> cmd;		// Retreive user command

		if (cmd == 'a' || cmd == 'A')		// Sequence to test command and execute selected function
		{
			Course1.add_student();
		}

		else if (cmd == 'e' || cmd == 'E')
		{
			if (Course1.students.size())		// If entries have been added
			{
				do
				{
					cout << "\nStudent to Edit: ";		// Get student entry to be edited from user 
					cin >> num;
					
					if (num[0] <= '9' && num[0] >= '0')		// Check input value
					{
						index = stoi(num);
						Course1.edit_student(index);
						err = 0;
					}

					else
					{
						cout << "\nPlease enter a positive integer.\n";		// Error message
						err = 1;
					}
				} while (err);
			}
			else
			{
				cout << "\nNo students found. Use (A)dd command.";		// Error message
			}
		}
		
		else if (cmd == 'p' || cmd == 'P')
		{
			Course1.print_grades();
		}

		else if (cmd == 'd' || cmd == 'D')
		{
			Course1.delete_student();
		}

		else if (cmd == 's' || cmd == 'S')
		{
			Course1.save();
		}

		else if (cmd == 'l' || cmd == 'L')
		{
			Course1.load();
		}

	} while (!(cmd == 'q' || cmd == 'Q'));

	return 0;
}


