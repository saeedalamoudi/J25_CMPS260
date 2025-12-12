#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <limits>

using namespace std;

struct Name {
    string first;
    string last;
};

struct Scores {
    double exam1;
    double exam2;
    double exam3;
    double average;
    char letter;
};

struct Student {
    int id;
    Name name;
    string semester;
    Scores scores;
};

Student gradebook[100];
int studentCount = 0;

bool isIDUnique(int id) {
    for (int i = 0; i < studentCount; i++) {
        if (gradebook[i].id == id) {
            return false;
        }
    }
    return true;
}

int generateID() {
    int id;
    do {
        id = 10000 + rand() % 90000;
    } while (!isIDUnique(id));
    return id;
}

char getLetterGrade(double avg) {
    if (avg >= 90) return 'A';
    if (avg >= 80) return 'B';
    if (avg >= 70) return 'C';
    if (avg >= 60) return 'D';
    return 'F';
}

void addNewStudent() {
    if (studentCount >= 100) {
        cout << "Gradebook is full!\n";
        return;
    }

    string first, last, sem;
    cout << "First name: ";
    cin >> first;
    cout << "Last name: ";
    cin >> last;
    cout << "Semester (e.g., Fall 2025): ";
    cin.ignore();
    getline(cin, sem);

    int newID = generateID();

    gradebook[studentCount].id = newID;
    gradebook[studentCount].name.first = first;
    gradebook[studentCount].name.last = last;
    gradebook[studentCount].semester = sem;
    gradebook[studentCount].scores.exam1 = 0;
    gradebook[studentCount].scores.exam2 = 0;
    gradebook[studentCount].scores.exam3 = 0;
    gradebook[studentCount].scores.average = 0;
    gradebook[studentCount].scores.letter = 'F';

    cout << "Great! " << first << " " << last << " has been added.\n";
    cout << "Assigned Student ID: " << newID << "\n";

    studentCount++;
}

void enterUpdateScores() {
    int id;
    cout << "Enter student ID: ";
    cin >> id;

    int idx = -1;
    for (int i = 0; i < studentCount; i++) {
        if (gradebook[i].id == id) {
            idx = i;
            break;
        }
    }

    if (idx == -1) {
        cout << "Student not found.\n";
        return;
    }

    double e1, e2, e3;
    cout << "Enter Exam 1 (0-100): ";
    cin >> e1;
    cout << "Enter Exam 2 (0-100): ";
    cin >> e2;
    cout << "Enter Exam 3 (0-100): ";
    cin >> e3;

    gradebook[idx].scores.exam1 = e1;
    gradebook[idx].scores.exam2 = e2;
    gradebook[idx].scores.exam3 = e3;
    gradebook[idx].scores.average = (e1 + e2 + e3) / 3.0;
    gradebook[idx].scores.letter = getLetterGrade(gradebook[idx].scores.average);

    cout << "Scores updated for " << gradebook[idx].name.first << " "
        << gradebook[idx].name.last << " (ID: " << id << ").\n";
    cout << "Average: " << fixed << setprecision(2) << gradebook[idx].scores.average << "\n";
    cout << "Letter: " << gradebook[idx].scores.letter << "\n";
}

void displayStudentReport() {
    int id;
    cout << "Enter student ID: ";
    cin >> id;

    int idx = -1;
    for (int i = 0; i < studentCount; i++) {
        if (gradebook[i].id == id) {
            idx = i;
            break;
        }
    }

    if (idx == -1) {
        cout << "Student not found.\n";
        return;
    }

    cout << "------ Student Report ------\n";
    cout << "Name: " << gradebook[idx].name.last << ", " << gradebook[idx].name.first << "\n";
    cout << "ID: " << gradebook[idx].id << "\n";
    cout << "Semester: " << gradebook[idx].semester << "\n";
    cout << "Exam 1: " << gradebook[idx].scores.exam1 << "\n";
    cout << "Exam 2: " << gradebook[idx].scores.exam2 << "\n";
    cout << "Exam 3: " << gradebook[idx].scores.exam3 << "\n";
    cout << "Average: " << fixed << setprecision(2) << gradebook[idx].scores.average << "\n";
    cout << "Letter: " << gradebook[idx].scores.letter << "\n";
    cout << "----------------------------\n";
}

void displaySemesterReport() {
    string sem;
    cout << "Enter semester (e.g., Fall 2025): ";
    cin.ignore();
    getline(cin, sem);

    int foundCount = 0;
    double totalAvg = 0;
    double maxAvg = -1;
    double minAvg = 101;

    cout << "ID    | Name                | E1   E2   E3   | Avg    | Letter\n";
    cout << "-------------------------------------------------------\n";

    for (int i = 0; i < studentCount; i++) {
        if (gradebook[i].semester == sem) {
            cout << gradebook[i].id << " | ";
            cout << gradebook[i].name.last << ", " << gradebook[i].name.first << " | ";
            cout << gradebook[i].scores.exam1 << " ";
            cout << gradebook[i].scores.exam2 << " ";
            cout << gradebook[i].scores.exam3 << " | ";
            cout << fixed << setprecision(2) << gradebook[i].scores.average << " | ";
            cout << gradebook[i].scores.letter << "\n";

            foundCount++;
            totalAvg += gradebook[i].scores.average;

            if (gradebook[i].scores.average > maxAvg) {
                maxAvg = gradebook[i].scores.average;
            }
            if (gradebook[i].scores.average < minAvg) {
                minAvg = gradebook[i].scores.average;
            }
        }
    }

    if (foundCount == 0) {
        cout << "No records for that semester.\n";
    }
    else {
        cout << "Students: " << foundCount << "\n";
        cout << "Semester Average: " << fixed << setprecision(2) << (totalAvg / foundCount) << "\n";
        cout << "Highest Average: " << fixed << setprecision(2) << maxAvg << "\n";
        cout << "Lowest Average: " << fixed << setprecision(2) << minAvg << "\n";
    }
}

void listAllStudents() {
    if (studentCount == 0) {
        cout << "No students added yet.\n";
        return;
    }

    cout << "ID    | Name                | Semester\n";
    cout << "-----------------------------------------\n";

    for (int i = 0; i < studentCount; i++) {
        cout << gradebook[i].id << " | ";
        cout << gradebook[i].name.last << ", " << gradebook[i].name.first << " | ";
        cout << gradebook[i].semester << "\n";
    }
}

void showMenu() {
    cout << "\n*************** Faculty Gradebook ***************\n";
    cout << "Please choose one of the following operations\n";
    cout << "1- Add a new student record\n";
    cout << "2- Enter/Update scores (by ID)\n";
    cout << "3- Display report for a student (by ID)\n";
    cout << "4- Display report for a semester\n";
    cout << "5- List all students\n";
    cout << "0- Exit\n";
    cout << "Choice: ";
}

int main() {
    srand(time(0));

    int choice;

    while (true) {
        showMenu();
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        cout << "\n";

        if (choice == 0) {
            cout << "Thank you for using the Faculty Gradebook!\n";
            cout << "Goodbye!\n";
            break;
        }

        if (choice == 1) {
            addNewStudent();
        }
        else if (choice == 2) {
            enterUpdateScores();
        }
        else if (choice == 3) {
            displayStudentReport();
        }
        else if (choice == 4) {
            displaySemesterReport();
        }
        else if (choice == 5) {
            listAllStudents();
        }
        else {
            cout << "Invalid choice. Please try again.\n";
        }

        cout << "Press any key to return to Main Menu!\n";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
    }

    return 0;
}