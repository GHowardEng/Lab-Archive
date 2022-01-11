#pragma once

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>
#include "student.h"

using namespace std;


class CCourse
{
public:
	vector<CStudent> students;

	void print_menu(void);

	void add_student(void);

	void edit_student(unsigned int index);

	void delete_student(void);

	void print_grades(void);

	void load(void);

	void save(void);
	
	int check_input(string input);

	float calculate_final(float lab, float quiz, float midterm, float finalExam);
};
