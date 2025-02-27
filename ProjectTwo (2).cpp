// CS 300
// Laurel Horwath
// 02/23/2025



#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

//Initialize objects and variables
struct Course {
	string courseNumber;
	string courseName;
	vector<string> coursePrereqs;
};
vector<Course> courses;

void loadDataStructure() {
	string fileName;

	fileName = "Course_Names.txt";
	
	//To open file
	ifstream infile;
	infile.open(fileName);

	//To insert data into courses
	if (infile.is_open()) {
		string line;

		//Use while loop to read line by line
		while (getline(infile, line)) {
			vector<string> tokens;
			string token;
			stringstream ss(line);

			while (getline(ss, token, ',')) {
				tokens.push_back(token);
			}

			//Create new course
			//Add data to new course from file
			Course newCourse = Course();
			newCourse.courseNumber = tokens[0];
			newCourse.courseName = tokens[1];

			//If prerequisites exist, add to the course
			if (tokens.size() > 2) {
				for (int i = 2; i < tokens.size(); i++) {
					newCourse.coursePrereqs.push_back(tokens[i]);
				
				}
			}
			//Add new course to course list
			courses.push_back(newCourse);
		}

		cout << "Loaded sucessfully" << endl;
	}
	else {
		cout << "Error: File not found" << endl;
	}

	infile.close();
}

//Print course list
void PrintCourseList() {
	if (courses.size() > 0) {

		//To sort courses alphanumerically
		for (int i = 0; i < courses.size() - 1; i++) {
			for (int j = 0; j < courses.size() - i - 1; j++) {
				if (courses[j].courseNumber > courses[j + 1].courseNumber) {
					swap(courses[j + 1], courses[j]);
				}
			}
		}

		//Loop to print course name and number
		cout << "Sample schedule: " << endl;
		cout << endl;

		for (int i = 0; i < courses.size(); i++) {
			cout << courses[i].courseNumber << ", ";
			cout << courses[i].courseName << endl;

		}
		
	}
}

//Print course 
void PrintCourse() {
	//validate loaded data
	if (courses.size() > 0) {
		string courseInput;
		bool courseFound = false;

		cout << "Please select a course" << endl;
		cin >> courseInput;

		//convert lowercase to uppercase
		transform(courseInput.begin(), courseInput.end(), courseInput.begin(), ::toupper);

		//loop to find course that was input
		for (int i = 0; i < courses.size(); i++) {
			if (courses[i].courseNumber == courseInput) {
				courseFound = true;

				//To print the course found
				cout << endl;
				cout << "Here is a sample schedule" << endl;
				cout << endl;
				cout << courses[i].courseNumber << ", ";
				cout << courses[i].courseName << endl;
				cout << "Prerequisites: ";
				if (courses[i].coursePrereqs.size() > 0) {
					int prereqSize = courses[i].coursePrereqs.size();

					//loop through prerequisites
					for (int j = 0; j < prereqSize - 1; j++) {
						cout << courses[i].coursePrereqs[j] << ", ";
					}
					cout << courses[i].coursePrereqs[prereqSize - 1];
					cout << endl;
				}
				else {
					cout << "None" << endl;
				}
			}
		}
		//Input validation for course
		if (courseFound == false) {
			cout << "Error, no course found" << endl;
		}
	}
	else {
		cout << "Error, load data structure first." << endl;
	}
}

//main
int main() {
	bool quit = false;

	cout << endl;
	cout << "Welcome to the course planner." << endl;

	do {
		string input;

		//To print menu
		cout << endl;
		cout << "1. Load Data Structure" << endl;
		cout << "2. Print Course List" << endl;
		cout << "3. Print Course" << endl;
		cout << "9. Exit" << endl;
		cout << endl;
		cout << "What would you like to do?";
		cin >> input;
		cout << endl;

		//input validation
		while ((input != "1") && (input != "2") && (input != "3") && (input != "9")) {
			cout << input << " is not a valid option." << endl;

			cout << endl;
			cout << "1. Load Data Structure" << endl;
			cout << "2. Print Course List" << endl;
			cout << "3. Print Course" << endl;
			cout << "9. Exit" << endl;
			cout << endl;
			cout << "What would you like to do?";
			cin >> input;
			cout << endl;
		}
		if (input == "1") {
			LoadDataStructure();
		}
		if (input == "2") {
			PrintCourseList();
		}
		if (input == "3") {
			PrintCourse();
		}
		if (input == "9") {
			cout << endl;
			cout << "Thank you for using the course planner!" << endl;
			exit(quit);
		}
	} while (!quit);
	
	return 0;
}