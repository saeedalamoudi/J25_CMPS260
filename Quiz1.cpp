#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <iomanip>

using namespace std;

struct Date {
    int day;
    int month;
    int year;
};

struct Appointment {
    int id;
    string name;
    Date date;
    string purpose;
};

Appointment schedule[50];
int appointmentCount = 0;

void addAppointment() {
    if (appointmentCount >= 50) {
        cout << "Schedule is full!" << endl;
        return;
    }

    string nm, purp;
    int d, m, y;

    cout << "Name: ";
    getline(cin, nm);

    cout << "Date (DD MM YYYY): ";
    cin >> d >> m >> y;
    cin.ignore();

    cout << "Purpose: ";
    getline(cin, purp);

    int apptID = 1000 + rand() % 9000;

    schedule[appointmentCount].id = apptID;
    schedule[appointmentCount].name = nm;
    schedule[appointmentCount].date.day = d;
    schedule[appointmentCount].date.month = m;
    schedule[appointmentCount].date.year = y;
    schedule[appointmentCount].purpose = purp;

    appointmentCount++;

    cout << "Appointment added! ID: " << apptID << endl;
}

void viewByDate() {
    int d, m, y;
    cout << "Enter date (DD MM YYYY): ";
    cin >> d >> m >> y;

    cout << "Appointments on " << setfill('0') << setw(2) << d << "/"
        << setw(2) << m << "/" << y << ":" << endl;

    int foundCount = 0;

    for (int i = 0; i < appointmentCount; i++) {
        if (schedule[i].date.day == d && schedule[i].date.month == m && schedule[i].date.year == y) {
            cout << "ID: " << schedule[i].id << " | " << schedule[i].name
                << " | " << schedule[i].purpose << endl;
            foundCount++;
        }
    }

    if (foundCount == 0) {
        cout << "No appointments for this date." << endl;
    }
}

int main() {
    srand(time(0));

    int option;

    do {
        cout << endl;
        cout << "*********** Appointment Scheduler ***********" << endl;
        cout << "1. Add Appointment" << endl;
        cout << "2. View Appointments by Date" << endl;
        cout << "3. Exit" << endl;
        cout << "Choice: ";
        cin >> option;
        cin.ignore();
        cout << endl;

        switch (option) {
        case 1:
            addAppointment();
            cout << "---------------------------------------------" << endl;
            break;
        case 2:
            viewByDate();
            cout << "---------------------------------------------" << endl;
            break;
        case 3:
            cout << "Thank you for using the scheduler!" << endl;
            break;
        default:
            cout << "Invalid option!" << endl;
            cout << "---------------------------------------------" << endl;
        }

    } while (option != 3);

    return 0;
}