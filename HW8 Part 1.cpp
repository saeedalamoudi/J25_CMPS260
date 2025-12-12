#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

struct Patient {
    string id;
    string name;
    string condition;
    int severity;
    Patient* next;
};

Patient* head = nullptr;
int totalServed = 0;

void loadPatients() {
    ifstream in("patients.txt");
    if (!in) return;

    string line;
    getline(in, line);

    while (getline(in, line)) {
        if (line.empty()) continue;

        Patient* node = new Patient;
        node->next = nullptr;

        int start = 0;
        int pos = line.find(',');

        node->id = line.substr(start, pos - start);

        start = pos + 1;
        pos = line.find(',', start);
        node->name = line.substr(start, pos - start);

        start = pos + 1;
        pos = line.find(',', start);
        node->condition = line.substr(start, pos - start);

        start = pos + 1;
        node->severity = stoi(line.substr(start));

        if (!head) {
            head = node;
        }
        else {
            Patient* cur = head;
            while (cur->next) cur = cur->next;
            cur->next = node;
        }
    }
}

void savePatients() {
    ofstream out("patients.txt");
    out << "ID,Name,Condition,Severity\n";

    Patient* cur = head;
    while (cur) {
        out << cur->id << ","
            << cur->name << ","
            << cur->condition << ","
            << cur->severity << "\n";
        cur = cur->next;
    }
}

void addPatient() {
    Patient* node = new Patient;
    node->next = nullptr;

    cout << "Enter Patient ID: ";
    cin >> node->id;
    cin.ignore();

    cout << "Enter patient name: ";
    getline(cin, node->name);

    cout << "Enter condition: ";
    getline(cin, node->condition);

    cout << "Enter severity (1-5): ";
    cin >> node->severity;

    if (!head) {
        head = node;
    }
    else {
        Patient* cur = head;
        while (cur->next) cur = cur->next;
        cur->next = node;
    }

    cout << "Patient added to the queue.\n";
}

void displayQueue() {
    if (!head) {
        cout << "No patients in queue.\n";
        return;
    }

    cout << "=========== CURRENT QUEUE ===========\n";
    cout << left << setw(10) << "ID"
        << setw(20) << "Name"
        << setw(22) << "Condition"
        << "Severity\n";
    cout << "-----------------------------------------\n";

    Patient* cur = head;
    while (cur) {
        cout << left << setw(10) << cur->id
            << setw(20) << cur->name
            << setw(22) << cur->condition
            << cur->severity << "\n";
        cur = cur->next;
    }
}

void servePatient() {
    if (!head) {
        cout << "No patients in queue.\n";
        return;
    }

    Patient* temp = head;
    head = head->next;

    cout << "Serving Patient: " << temp->id << " - " << temp->name << "\n";
    delete temp;
    totalServed++;
}

void showSummary() {
    int count = 0;
    int severitySum = 0;

    Patient* cur = head;
    while (cur) {
        count++;
        severitySum += cur->severity;
        cur = cur->next;
    }

    double avg = (count == 0) ? 0.0 : (double)severitySum / count;

    cout << "========== ER SUMMARY ==========\n";
    cout << "Total Patients Served: " << totalServed << "\n";
    cout << "Patients in Queue: " << count << "\n";
    cout << fixed << setprecision(2);
    cout << "Average Severity of Waiting Patients: " << avg << "\n";
    cout << "================================\n";
}

int main() {
    loadPatients();
    int choice;

    do {
        cout << "\n****** Welcome to ER Patient Queue Manager ******\n";
        cout << "1. Add New Patient\n";
        cout << "2. Display Patient Queue\n";
        cout << "3. Serve Next Patient\n";
        cout << "4. View ER Summary\n";
        cout << "5. Exit\n→ ";
        cin >> choice;

        switch (choice) {
        case 1: addPatient(); break;
        case 2: displayQueue(); break;
        case 3: servePatient(); break;
        case 4: showSummary(); break;
        case 5:
            savePatients();
            cout << "Patient queue saved to patients.txt. Stay safe!\n";
            break;
        default:
            cout << "Invalid option. Try again.\n";
        }
    } while (choice != 5);

    return 0;
}
