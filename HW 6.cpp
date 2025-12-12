#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <limits>

using namespace std;

template <typename T1, typename T2>
struct Package {
    T1 id;
    string name;
    string type;
    int etaHours;
    T2 fee;
    string status;
};

template <typename T1, typename T2>
int loadPackages(Package<T1, T2> packages[]) {
    ifstream file("packages.txt");
    if (!file.is_open()) {
        return 0;
    }

    string line;
    getline(file, line);

    int count = 0;
    while (getline(file, line) && count < 100) {
        stringstream ss(line);
        string idStr, name, type, etaStr, feeStr, status;

        getline(ss, idStr, ',');
        getline(ss, name, ',');
        getline(ss, type, ',');
        getline(ss, etaStr, ',');
        getline(ss, feeStr, ',');
        getline(ss, status, ',');

        packages[count].id = stoi(idStr);
        packages[count].name = name;
        packages[count].type = type;
        packages[count].etaHours = stoi(etaStr);
        packages[count].fee = stod(feeStr);
        packages[count].status = status;
        count++;
    }

    file.close();
    return count;
}

template <typename T1, typename T2>
void savePackages(Package<T1, T2> packages[], int count) {
    ofstream file("packages.txt");
    if (!file.is_open()) {
        cout << "Error saving packages!" << endl;
        return;
    }

    file << "ID,Name,Type,ETA,Fee,Status" << endl;
    for (int i = 0; i < count; i++) {
        file << packages[i].id << "," << packages[i].name << ","
            << packages[i].type << "," << packages[i].etaHours << ","
            << fixed << setprecision(2) << packages[i].fee << ","
            << packages[i].status << endl;
    }

    file.close();
}

template <typename T1, typename T2>
void addPackage(Package<T1, T2> packages[], int& count) {
    if (count >= 100) {
        cout << "Package limit reached!" << endl;
        return;
    }

    T1 pkgID;
    string recipientName, deliveryType;
    int eta;
    T2 fee;

    cout << "Enter package ID: ";
    cin >> pkgID;
    cin.ignore();

    cout << "Enter recipient name: ";
    getline(cin, recipientName);

    cout << "Enter delivery type (Standard/Express/Fragile): ";
    getline(cin, deliveryType);

    cout << "Enter delivery ETA (in hours): ";
    cin >> eta;

    cout << "Enter delivery fee: ";
    cin >> fee;

    packages[count].id = pkgID;
    packages[count].name = recipientName;
    packages[count].type = deliveryType;
    packages[count].etaHours = eta;
    packages[count].fee = fee;
    packages[count].status = "Pending";

    count++;
    cout << "Package added!" << endl;
}

template <typename T1, typename T2>
void displayPackages(Package<T1, T2> packages[], int count) {
    if (count == 0) {
        cout << "No packages to display." << endl;
        return;
    }

    cout << "============ PACKAGES ============" << endl;
    cout << left << setw(10) << "ID" << setw(15) << "Name" << setw(15) << "Type"
        << setw(10) << "ETA" << setw(10) << "Fee" << "Status" << endl;
    cout << "-----------------------------------------------" << endl;

    for (int i = 0; i < count; i++) {
        cout << left << setw(10) << packages[i].id << setw(15) << packages[i].name
            << setw(15) << packages[i].type << setw(10) << packages[i].etaHours
            << "$" << fixed << setprecision(2) << setw(9) << packages[i].fee
            << packages[i].status << endl;
    }
}

template <typename T1, typename T2>
void markDelivered(Package<T1, T2> packages[], int count) {
    T1 pkgID;
    cout << "Enter package ID to mark as delivered: ";
    cin >> pkgID;

    int index = -1;
    for (int i = 0; i < count; i++) {
        if (packages[i].id == pkgID) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        cout << "Package not found!" << endl;
        return;
    }

    packages[index].status = "Delivered";
    cout << "Package " << pkgID << " marked as Delivered." << endl;
}

template <typename T1, typename T2>
void deliveryReport(Package<T1, T2> packages[], int count) {
    if (count == 0) {
        cout << "No packages to report." << endl;
        return;
    }

    int totalPackages = count;
    int deliveredCount = 0;
    int pendingCount = 0;
    T2 totalRevenue = 0;

    for (int i = 0; i < count; i++) {
        if (packages[i].status == "Delivered") {
            deliveredCount++;
            totalRevenue += packages[i].fee;
        }
        else {
            pendingCount++;
        }
    }

    cout << "========== DELIVERY REPORT ==========" << endl;
    cout << "Total Packages: " << totalPackages << endl;
    cout << "Delivered: " << deliveredCount << endl;
    cout << "Pending: " << pendingCount << endl;
    cout << "Total Revenue: $" << fixed << setprecision(2) << totalRevenue << endl;
    cout << "=====================================" << endl;
}

void displayMenu() {
    cout << "\n******** Welcome to Package Delivery Tracker ********" << endl;
    cout << "Please choose one of the following operations:" << endl;
    cout << "1. Add New Package" << endl;
    cout << "2. Display All Packages" << endl;
    cout << "3. Mark Package as Delivered" << endl;
    cout << "4. View Delivery Report" << endl;
    cout << "5. Exit" << endl;
    cout << "-> ";
}

int main() {
    Package<int, double> packages[100];
    int count = loadPackages(packages);

    int choice;

    do {
        displayMenu();
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << endl;

        switch (choice) {
        case 1:
            addPackage(packages, count);
            break;
        case 2:
            displayPackages(packages, count);
            break;
        case 3:
            markDelivered(packages, count);
            break;
        case 4:
            deliveryReport(packages, count);
            break;
        case 5:
            savePackages(packages, count);
            cout << "Data saved to packages.txt. Goodbye!" << endl;
            break;
        default:
            cout << "Invalid option. Try again." << endl;
        }

    } while (choice != 5);

    return 0;
}