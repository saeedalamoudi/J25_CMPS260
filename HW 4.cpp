#include <iostream>
#include <limits>
#include <iomanip>

using namespace std;

void displayGrades(int grades[], int size, int index = 0);
int sumGrades(int grades[], int size);
int countFailing(int grades[], int size);
int findMax(int grades[], int size, int index = 0, int currentMax = -1);

int gradeArray[100];
int gradeCount = 0;

void displayGrades(int grades[], int size, int index) {
    if (index >= size) {
        cout << endl;
        return;
    }
    cout << grades[index] << " ";
    displayGrades(grades, size, index + 1);
}

int sumGrades(int grades[], int size) {
    if (size == 0) {
        return 0;
    }
    return grades[size - 1] + sumGrades(grades, size - 1);
}

int countFailing(int grades[], int size) {
    if (size == 0) {
        return 0;
    }
    int failCount = (grades[size - 1] < 60) ? 1 : 0;
    return failCount + countFailing(grades, size - 1);
}

int findMax(int grades[], int size, int index, int currentMax) {
    if (index >= size) {
        return currentMax;
    }
    if (grades[index] > currentMax) {
        currentMax = grades[index];
    }
    return findMax(grades, size, index + 1, currentMax);
}

void enterGrades() {
    int numGrades;
    cout << "How many grades do you want to enter?" << endl;
    cout << "-> ";
    cin >> numGrades;

    if (numGrades > 100) {
        cout << "Maximum 100 grades allowed!" << endl;
        return;
    }

    for (int i = 0; i < numGrades; i++) {
        cout << "Enter grade #" << (i + 1) << ": ";
        cin >> gradeArray[i];
    }

    gradeCount = numGrades;
    cout << "Grades successfully saved!" << endl;
}

void displayAllGrades() {
    if (gradeCount == 0) {
        cout << "No grades entered yet!" << endl;
        return;
    }

    cout << "Grades entered:" << endl;
    cout << "-> ";
    displayGrades(gradeArray, gradeCount, 0);
}

void calculateAverage() {
    if (gradeCount == 0) {
        cout << "No grades entered yet!" << endl;
        return;
    }

    int total = sumGrades(gradeArray, gradeCount);
    double average = static_cast<double>(total) / gradeCount;

    cout << fixed << setprecision(2);
    cout << "The average grade is: " << average << endl;
}

void countFailingGrades() {
    if (gradeCount == 0) {
        cout << "No grades entered yet!" << endl;
        return;
    }

    int failCount = countFailing(gradeArray, gradeCount);
    cout << "Number of failing grades: " << failCount << endl;
}

void findHighestGrade() {
    if (gradeCount == 0) {
        cout << "No grades entered yet!" << endl;
        return;
    }

    int highest = findMax(gradeArray, gradeCount, 0, gradeArray[0]);
    cout << "Highest grade: " << highest << endl;
}

void displayMenu() {
    cout << "\n******** Welcome to Recursive Grade Analyzer ********" << endl;
    cout << "Please choose one of the following operations:" << endl;
    cout << "1. Enter Grades" << endl;
    cout << "2. Display Grades" << endl;
    cout << "3. Calculate Average Grade (using Recursion)" << endl;
    cout << "4. Count Failing Grades (using Recursion)" << endl;
    cout << "5. Find Highest Grade (using Recursion)" << endl;
    cout << "6. Exit" << endl;
    cout << "-> ";
}

int main() {
    int choice;

    while (true) {
        displayMenu();
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << endl;

        if (choice == 6) {
            cout << "Thank you for using Recursive Grade Analyzer!" << endl;
            break;
        }

        switch (choice) {
        case 1:
            enterGrades();
            break;
        case 2:
            displayAllGrades();
            break;
        case 3:
            calculateAverage();
            break;
        case 4:
            countFailingGrades();
            break;
        case 5:
            findHighestGrade();
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}