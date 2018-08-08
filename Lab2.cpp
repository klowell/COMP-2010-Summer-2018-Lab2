/*****************************************************************************************
Project Name: Lab 2
Name: Kristopher Lowell
Date Completed: 8/7/2018
Purpose: To accept names of students along with two of their test scores, then calculate
the averages, which students passed and failed which tests, and then print it all.
*****************************************************************************************/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct student				// Making a structure for the data
{
	string studentName;
	int studentGradeTestA;
	int studentGradeTestB;
};

void sort_by_name(vector <student> &students);
void calculate_averages(vector <student> &students, double *averageA, double *averageB, double* totAverage);
void print_records(vector <student> &students);
void print_averages(double averageA, double averageB, double totAverage);

vector <student> determine_students(vector <student> &students, unsigned test, bool pass);

int main(int argc, char *argv[])
{
	unsigned numOfStudents = 0;
	string strEntry;
	
	student currentStudent;					// A working student variable to ease insertion into vector
	vector <student> allStudents, current;

	double averageA, averageB, totAverage;

	do
	{
		cout << "Enter student #" << numOfStudents + 1 << "'s name: ";		// Accepting inputs for student's name

		while (cin.peek() != '\n')
		{
			cin >> strEntry;
			currentStudent.studentName.append(strEntry);

			if (cin.peek() != '\n')
				currentStudent.studentName.append(" ");
		}

		if (currentStudent.studentName.front() != '-')					// Accepting input for students grade for tests
		{
			do
			{
				cout << "Enter " << currentStudent.studentName << "'s Test A grade: ";
				cin >> currentStudent.studentGradeTestA;
			} while (currentStudent.studentGradeTestA < 0 || currentStudent.studentGradeTestA > 10);

			do
			{
				cout << "Enter " << currentStudent.studentName << "'s Test B grade: ";
				cin >> currentStudent.studentGradeTestB;
			} while (currentStudent.studentGradeTestB < 0 || currentStudent.studentGradeTestB > 10);

			allStudents.push_back(currentStudent);				// Adding current student variable into vector
			numOfStudents++;

			currentStudent.studentName.clear();					// Clearing current name string since append is being used 
			cout << endl;
			cin.ignore(INT_MAX, '\n');
		}
	} while (strEntry.front() != '-');

	sort_by_name(allStudents);
	calculate_averages(allStudents, &averageA, &averageB, &totAverage);

	cout << endl << "All Students:" << endl;					// Printing all the records and averages
	print_records(allStudents);
	print_averages(averageA, averageB, totAverage);

	current = determine_students(allStudents, 1, true);	// Determining and printing which students passed Test A
	cout << endl << "Students That Passed Test A:" << endl;
	print_records(current);

	current = determine_students(allStudents, 1, false); // Determining and printing which students failed Test A
	cout << endl << "Students That Failed Test A:" << endl;
	print_records(current);

	current = determine_students(allStudents, 2, true);	// Determining and printing which students passed Test B
	cout << endl << "Students That Passed Test B:" << endl;
	print_records(current);

	current = determine_students(allStudents, 2, false);	// Determining and printing which students faileded Test B
	cout << endl << "Students That Failed Test B" << endl;
	print_records(current);

	current.clear();		// Clearing both vectors for good measure
	allStudents.clear();
}

void sort_by_name(vector <student> &students)
{
	unsigned minIndex;				// Using selection sort to sort vector by student names
	student temp;

	for (unsigned i = 0; i < students.size() - 1; i++)
	{
		minIndex = i;

		for (unsigned j = i + 1; j < students.size(); j++)
		{
			if (students[j].studentName.compare(students[minIndex].studentName) < 0)
				minIndex = j;
		}

		temp = students[i];							// Swap student variables in vector
		students[i] = students[minIndex];
		students[minIndex] = temp;
	}
}

void calculate_averages(vector <student> &students, double *averageA, double *averageB, double* totAverage)
{
	double subTotalA = 0;
	double subTotalB = 0;

	for (unsigned i = 0; i < students.size(); i++)		// Calculating the subtotals from tests A and B
	{
		subTotalA += students[i].studentGradeTestA;
		subTotalB += students[i].studentGradeTestB;
	}

	double total = subTotalA + subTotalB;

	*averageA = subTotalA / students.size();			// Calculating the averages
	*averageB = subTotalB / students.size();
	*totAverage = total / (2 * students.size());
}

void print_records(vector <student> &students)
{
	cout << endl << "Student Name \t\t Test A Grade \t Test B Grade" << endl;
	cout << endl << "----------------------------------------------------------------------------------------" << endl;
	
	for (unsigned i = 0; i < students.size(); i++)
	{
		cout << students[i].studentName << "\t\t";
		cout << students[i].studentGradeTestA << "\t";
		cout << students[i].studentGradeTestB << endl;
	}
}

void print_averages(double averageA, double averageB, double totAverage)
{
	cout.setf(ios_base::fixed);
	cout.precision(2);

	cout << endl;
	cout << "Test A Average: " << averageA << endl;
	cout << "Test B Average: " << averageB << endl;
	cout << "Total Average: " << totAverage << endl;
}

vector <student> determine_students(vector <student> &students, unsigned test, bool pass)
{
	vector <student> result;
	
	for (unsigned i = 0; i < students.size(); i++)
	{
		if(test == 1)		// Test A
		{
			if (students[i].studentGradeTestA >= 8 && pass == true)			// Fill vector if passing students is wanted
				result.push_back(students[i]);
			else if (students[i].studentGradeTestA < 8 && pass == false)	// Fill vector if failing students is wanted
				result.push_back(students[i]);
		}
		else if (test == 2)		// Test B
		{
			if (students[i].studentGradeTestB >= 8 && pass == true)			// Fill vector if passing students is wanted
				result.push_back(students[i]);
			else if (students[i].studentGradeTestB < 8 && pass == false)	// Fill vector if failing students is wanted
				result.push_back(students[i]);
		}
	}

	return result;
}