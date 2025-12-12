#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <iomanip>
#include <string>
#include <limits>

using namespace std;

struct Patient {
    string id;
    string name;
    string severity;
    int waitTime;
    string status;
};

void loadPatients(list<Patient>& patients) {
    ifstream file("patients.txt");
    if (!file.is_open()) {
        return;
    }

    string line;
    getline(file, line);

    while (getline(file, line)) {
        stringstream ss(line);
        string id, name, severity, waitStr, status;

        getline(ss, id, ',');
        getline(ss, name, ',');
        getline(ss, severity, ',');
        getline(ss, waitStr, ',');
        getline(ss, status, ',');

        Patient pat;
        pat.id = id;
        pat.name = name;
        pat.severity = severity;
        pat.waitTime = stoi(waitStr);
        pat.status = status;

        patients.push_back(pat);
    }

    file.close();
}

void savePatients(const list<Patient>& patients) {
    ofstream file("patients.txt");
    if (!file.is_open()) {
        cout << "Error saving patients!" << endl;
        return;
    }

    file << "ID,Name,Severity,Wait,Status" << endl;
    for (const auto& pat : patients) {
        file << pat.id << "," << pat.name << "," << pat.severity << ","
            << pat.waitTime << "," << pat.status << endl;
    }

    file.close();
}

void registerPatient(list<Patient>& patients) {
    Patient newPatient;

    cout << "Enter patient ID: ";
    cin >> newPatient.id;
    cin.ignore();

    cout << "Enter name: ";
    getline(cin, newPatient.name);

    cout << "Enter condition severity: ";
    getline(cin, newPatient.severity);

    cout << "Enter estimated wait time: ";
    cin >> newPatient.waitTime;

    newPatient.status = "Waiting";

    patients.push_back(newPatient);
    cout << "Patient registered successfully!" << endl;
}

void displayQueue(const list<Patient>& patients) {
    if (patients.empty()) {
        cout << "No patients in queue." << endl;
        return;
    }

    cout << "=========== ER WAITING LIST ===========" << endl;
    cout << left << setw(10) << "ID" << setw(20) << "Name" << setw(15) << "Severity"
        << setw(12) << "Wait(min)" << "Status" << endl;
    cout << "------------------------------------------------------" << endl;

    for (const auto& pat : patients) {
        cout << left << setw(10) << pat.id << setw(20) << pat.name
            << setw(15) << pat.severity << setw(12) << pat.waitTime
            << pat.status << endl;
    }
}

void admitPatient(list<Patient>& patients) {
    if (patients.empty()) {
        cout << "No patients in queue." << endl;
        return;
    }

    for (auto& pat : patients) {
        if (pat.status == "Waiting") {
            pat.status = "Admitted";
            cout << "Patient " << pat.id << " has been admitted to the ER." << endl;
            return;
        }
    }

    cout << "No waiting patients to admit." << endl;
}

void viewSummary(const list<Patient>& patients) {
    if (patients.empty()) {
        cout << "No patients to summarize." << endl;
        return;
    }

    int totalPatients = patients.size();
    int admittedCount = 0;
    int waitingCount = 0;
    int totalWaitTime = 0;

    for (const auto& pat : patients) {
        if (pat.status == "Admitted") {
            admittedCount++;
        }
        else {
            waitingCount++;
            totalWaitTime += pat.waitTime;
        }
    }

    float avgWaitTime = (waitingCount > 0) ? (float)totalWaitTime / waitingCount : 0.0;

    cout << "========== ER SUMMARY ==========" << endl;
    cout << "Total Patients: " << totalPatients << endl;
    cout << "Admitted: " << admittedCount << endl;
    cout << "Waiting: " << waitingCount << endl;
    cout << "Avg Wait Time (Waiting): " << fixed << setprecision(2) << avgWaitTime << " minutes" << endl;
    cout << "================================" << endl;
}

void displayMenu() {
    cout << "\n****** Welcome to Emergency Room Queue Manager ******" << endl;
    cout << "Please choose one of the following operations:" << endl;
    cout << "1. Register New Patient" << endl;
    cout << "2. Display Patient Queue" << endl;
    cout << "3. Admit Patient" << endl;
    cout << "4. View ER Summary" << endl;
    cout << "5. Exit" << endl;
    cout << "-> ";
}

int main() {
    list<Patient> patients;
    loadPatients(patients);

    int choice;

    do {
        displayMenu();
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << endl;

        switch (choice) {
        case 1:
            registerPatient(patients);
            break;
        case 2:
            displayQueue(patients);
            break;
        case 3:
            admitPatient(patients);
            break;
        case 4:
            viewSummary(patients);
            break;
        case 5:
            savePatients(patients);
            cout << "Patient queue saved to patients.txt. Have a safe shift!" << endl;
            break;
        default:
            cout << "Invalid option. Try again." << endl;
        }

    } while (choice != 5);

    return 0;
}