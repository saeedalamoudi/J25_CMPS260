#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <limits>

using namespace std;

template <typename T1, typename T2>
struct Appointment {
    T1 id;
    string name;
    string type;
    int timeUntil;
    T2 bill;
    string status;
};

template <typename T1, typename T2>
int loadAppointments(Appointment<T1, T2> appointments[]) {
    ifstream file("appointments.txt");
    if (!file.is_open()) {
        return 0;
    }

    string line;
    getline(file, line);

    int count = 0;
    while (getline(file, line) && count < 100) {
        stringstream ss(line);
        string id, name, type, timeStr, billStr, status;

        getline(ss, id, ',');
        getline(ss, name, ',');
        getline(ss, type, ',');
        getline(ss, timeStr, ',');
        getline(ss, billStr, ',');
        getline(ss, status, ',');

        appointments[count].id = id;
        appointments[count].name = name;
        appointments[count].type = type;
        appointments[count].timeUntil = stoi(timeStr);
        appointments[count].bill = stof(billStr);
        appointments[count].status = status;
        count++;
    }

    file.close();
    return count;
}

template <typename T1, typename T2>
void saveAppointments(Appointment<T1, T2> appointments[], int count) {
    ofstream file("appointments.txt");
    if (!file.is_open()) {
        cout << "Error saving appointments!" << endl;
        return;
    }

    file << "ID,Name,Type,Time,Bill,Status" << endl;
    for (int i = 0; i < count; i++) {
        file << appointments[i].id << "," << appointments[i].name << ","
            << appointments[i].type << "," << appointments[i].timeUntil << ","
            << fixed << setprecision(2) << appointments[i].bill << ","
            << appointments[i].status << endl;
    }

    file.close();
}

template <typename T1, typename T2>
void addAppointment(Appointment<T1, T2> appointments[], int& count) {
    if (count >= 100) {
        cout << "Appointment limit reached!" << endl;
        return;
    }

    T1 apptID;
    string patientName, apptType;
    int timeHours;
    T2 estimatedBill;

    cout << "Enter appointment ID: ";
    cin >> apptID;
    cin.ignore();

    cout << "Enter patient name: ";
    getline(cin, patientName);

    cout << "Enter appointment type: ";
    getline(cin, apptType);

    cout << "Enter time until appointment (hours): ";
    cin >> timeHours;

    cout << "Enter estimated bill: ";
    cin >> estimatedBill;

    appointments[count].id = apptID;
    appointments[count].name = patientName;
    appointments[count].type = apptType;
    appointments[count].timeUntil = timeHours;
    appointments[count].bill = estimatedBill;
    appointments[count].status = "Pending";

    count++;
    cout << "Appointment added!" << endl;
}

template <typename T1, typename T2>
void displayAppointments(Appointment<T1, T2> appointments[], int count) {
    if (count == 0) {
        cout << "No appointments to display." << endl;
        return;
    }

    cout << "=========== APPOINTMENTS ===========" << endl;
    cout << left << setw(10) << "ID" << setw(20) << "Name" << setw(15) << "Type"
        << setw(10) << "Time" << setw(12) << "Bill" << "Status" << endl;
    cout << "-------------------------------------------------" << endl;

    for (int i = 0; i < count; i++) {
        cout << left << setw(10) << appointments[i].id << setw(20) << appointments[i].name
            << setw(15) << appointments[i].type << setw(10) << appointments[i].timeUntil
            << "$" << fixed << setprecision(2) << setw(11) << appointments[i].bill
            << appointments[i].status << endl;
    }
}

template <typename T1, typename T2>
void markCompleted(Appointment<T1, T2> appointments[], int count) {
    T1 apptID;
    cout << "Enter appointment ID to mark as completed: ";
    cin >> apptID;

    int index = -1;
    for (int i = 0; i < count; i++) {
        if (appointments[i].id == apptID) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        cout << "Appointment not found!" << endl;
        return;
    }

    appointments[index].status = "Completed";
    cout << "Appointment " << apptID << " marked as Completed." << endl;
}

template <typename T1, typename T2>
void appointmentSummary(Appointment<T1, T2> appointments[], int count) {
    if (count == 0) {
        cout << "No appointments to summarize." << endl;
        return;
    }

    int totalAppointments = count;
    int completedCount = 0;
    int pendingCount = 0;
    T2 totalEarnings = 0;

    for (int i = 0; i < count; i++) {
        if (appointments[i].status == "Completed") {
            completedCount++;
            totalEarnings += appointments[i].bill;
        }
        else {
            pendingCount++;
        }
    }

    cout << "======== APPOINTMENT SUMMARY ========" << endl;
    cout << "Total Appointments: " << totalAppointments << endl;
    cout << "Completed: " << completedCount << endl;
    cout << "Pending: " << pendingCount << endl;
    cout << "Total Earnings: $" << fixed << setprecision(2) << totalEarnings << endl;
    cout << "=====================================" << endl;
}

void displayMenu() {
    cout << "\n******* Welcome to Clinic Appointment Manager *******" << endl;
    cout << "Please choose one of the following operations:" << endl;
    cout << "1. Add New Appointment" << endl;
    cout << "2. Display All Appointments" << endl;
    cout << "3. Mark Appointment as Completed" << endl;
    cout << "4. View Appointment Summary" << endl;
    cout << "5. Exit" << endl;
    cout << "-> ";
}

int main() {
    Appointment<string, float> appointments[100];
    int count = loadAppointments(appointments);

    int choice;

    do {
        displayMenu();
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << endl;

        switch (choice) {
        case 1:
            addAppointment(appointments, count);
            break;
        case 2:
            displayAppointments(appointments, count);
            break;
        case 3:
            markCompleted(appointments, count);
            break;
        case 4:
            appointmentSummary(appointments, count);
            break;
        case 5:
            saveAppointments(appointments, count);
            cout << "Data saved to appointments.txt. Goodbye!" << endl;
            break;
        default:
            cout << "Invalid option. Try again." << endl;
        }

    } while (choice != 5);

    return 0;
}