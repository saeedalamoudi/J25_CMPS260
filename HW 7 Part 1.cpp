#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <limits>

using namespace std;

struct Order {
    string id;
    string name;
    string item;
    int quantity;
    float price;
    string status;
};

void loadOrders(vector<Order>& orders) {
    ifstream file("orders.txt");
    if (!file.is_open()) {
        return;
    }

    string line;
    getline(file, line);

    while (getline(file, line)) {
        stringstream ss(line);
        string id, name, item, qtyStr, priceStr, totalStr, status;

        getline(ss, id, ',');
        getline(ss, name, ',');
        getline(ss, item, ',');
        getline(ss, qtyStr, ',');
        getline(ss, priceStr, ',');
        getline(ss, totalStr, ',');
        getline(ss, status, ',');

        Order ord;
        ord.id = id;
        ord.name = name;
        ord.item = item;
        ord.quantity = stoi(qtyStr);
        ord.price = stof(priceStr);
        ord.status = status;

        orders.push_back(ord);
    }

    file.close();
}

void saveOrders(const vector<Order>& orders) {
    ofstream file("orders.txt");
    if (!file.is_open()) {
        cout << "Error saving orders!" << endl;
        return;
    }

    file << "ID,Name,Item,Qty,Price,Total,Status" << endl;
    for (const auto& ord : orders) {
        float total = ord.quantity * ord.price;
        file << ord.id << "," << ord.name << "," << ord.item << ","
            << ord.quantity << "," << fixed << setprecision(2) << ord.price << ","
            << total << "," << ord.status << endl;
    }

    file.close();
}

void placeOrder(vector<Order>& orders) {
    Order newOrder;

    cout << "Enter Order ID: ";
    cin >> newOrder.id;
    cin.ignore();

    cout << "Enter customer name: ";
    getline(cin, newOrder.name);

    cout << "Enter menu item: ";
    getline(cin, newOrder.item);

    cout << "Enter quantity: ";
    cin >> newOrder.quantity;

    cout << "Enter price per item: ";
    cin >> newOrder.price;

    newOrder.status = "Pending";

    orders.push_back(newOrder);
    cout << "Order added!" << endl;
}

void displayOrders(const vector<Order>& orders) {
    if (orders.empty()) {
        cout << "No orders to display." << endl;
        return;
    }

    cout << "=========== CURRENT ORDERS ===========" << endl;
    cout << left << setw(10) << "ID" << setw(15) << "Name" << setw(15) << "Item"
        << setw(8) << "Qty" << setw(10) << "Price" << setw(10) << "Total" << "Status" << endl;
    cout << "---------------------------------------------------" << endl;

    for (const auto& ord : orders) {
        float total = ord.quantity * ord.price;
        cout << left << setw(10) << ord.id << setw(15) << ord.name << setw(15) << ord.item
            << setw(8) << ord.quantity << "$" << fixed << setprecision(2) << setw(9) << ord.price
            << "$" << setw(9) << total << ord.status << endl;
    }
}

void markServed(vector<Order>& orders) {
    string orderID;
    cout << "Enter Order ID to mark as served: ";
    cin >> orderID;

    bool found = false;
    for (auto& ord : orders) {
        if (ord.id == orderID) {
            found = true;
            if (ord.status == "Pending") {
                ord.status = "Served";
                cout << "Order " << orderID << " marked as Served." << endl;
            }
            else {
                cout << "Order is already served." << endl;
            }
            break;
        }
    }

    if (!found) {
        cout << "Order not found!" << endl;
    }
}

void salesSummary(const vector<Order>& orders) {
    if (orders.empty()) {
        cout << "No orders to summarize." << endl;
        return;
    }

    int totalOrders = orders.size();
    int servedCount = 0;
    int pendingCount = 0;
    float totalSales = 0.0;

    for (const auto& ord : orders) {
        if (ord.status == "Served") {
            servedCount++;
            totalSales += ord.quantity * ord.price;
        }
        else {
            pendingCount++;
        }
    }

    cout << "========== SALES SUMMARY ==========" << endl;
    cout << "Total Orders: " << totalOrders << endl;
    cout << "Served: " << servedCount << endl;
    cout << "Pending: " << pendingCount << endl;
    cout << "Total Sales: $" << fixed << setprecision(2) << totalSales << endl;
    cout << "===================================" << endl;
}

void displayMenu() {
    cout << "\n****** Welcome to Restaurant Order Manager ******" << endl;
    cout << "Please choose one of the following operations:" << endl;
    cout << "1. Place New Order" << endl;
    cout << "2. Display All Orders" << endl;
    cout << "3. Mark Order as Served" << endl;
    cout << "4. View Sales Summary" << endl;
    cout << "5. Exit" << endl;
    cout << "-> ";
}

int main() {
    vector<Order> orders;
    loadOrders(orders);

    int choice;

    do {
        displayMenu();
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << endl;

        switch (choice) {
        case 1:
            placeOrder(orders);
            break;
        case 2:
            displayOrders(orders);
            break;
        case 3:
            markServed(orders);
            break;
        case 4:
            salesSummary(orders);
            break;
        case 5:
            saveOrders(orders);
            cout << "Orders saved to orders.txt. Have a great day!" << endl;
            break;
        default:
            cout << "Invalid option. Try again." << endl;
        }

    } while (choice != 5);

    return 0;
}