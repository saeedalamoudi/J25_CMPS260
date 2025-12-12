#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <limits>

using namespace std;

struct Item {
    string name;
    string category;
    int quantity;
    double price;
};

struct Transaction {
    string type;
    string itemName;
    int quantity;
    double unitPrice;
};

Item inventory[100];
int inventoryCount = 0;

int loadInventory(Item items[]) {
    ifstream file("inventory.txt");
    if (!file.is_open()) {
        return 0;
    }

    string line;
    getline(file, line);

    int count = 0;
    while (getline(file, line) && count < 100) {
        stringstream ss(line);
        string name, category, qtyStr, priceStr;

        getline(ss, name, ',');
        getline(ss, category, ',');
        getline(ss, qtyStr, ',');
        getline(ss, priceStr, ',');

        items[count].name = name;
        items[count].category = category;
        items[count].quantity = stoi(qtyStr);
        items[count].price = stod(priceStr);
        count++;
    }

    file.close();
    return count;
}

void saveInventory(Item items[], int count) {
    ofstream file("inventory.txt");
    if (!file.is_open()) {
        cout << "Error saving inventory!" << endl;
        return;
    }

    file << "Name,Category,Quantity,Price" << endl;
    for (int i = 0; i < count; i++) {
        file << items[i].name << "," << items[i].category << ","
            << items[i].quantity << "," << fixed << setprecision(2) << items[i].price << endl;
    }

    file.close();
}

int loadTransactions(Transaction txns[]) {
    ifstream file("transactions.txt");
    if (!file.is_open()) {
        return 0;
    }

    string line;
    getline(file, line);

    int count = 0;
    while (getline(file, line) && count < 1000) {
        stringstream ss(line);
        string type, itemName, qtyStr, priceStr;

        getline(ss, type, ',');
        getline(ss, itemName, ',');
        getline(ss, qtyStr, ',');
        getline(ss, priceStr, ',');

        txns[count].type = type;
        txns[count].itemName = itemName;
        txns[count].quantity = stoi(qtyStr);
        txns[count].unitPrice = stod(priceStr);
        count++;
    }

    file.close();
    return count;
}

void saveTransaction(Transaction t) {
    ifstream checkFile("transactions.txt");
    bool fileExists = checkFile.is_open();
    checkFile.close();

    ofstream file("transactions.txt", ios::app);
    if (!file.is_open()) {
        cout << "Error saving transaction!" << endl;
        return;
    }

    if (!fileExists) {
        file << "Type,ItemName,Quantity,UnitPrice" << endl;
    }

    file << t.type << "," << t.itemName << "," << t.quantity << ","
        << fixed << setprecision(2) << t.unitPrice << endl;

    file.close();
}

void displayInventory(Item items[], int count) {
    cout << "============== INVENTORY ==============" << endl;
    cout << left << setw(20) << "Item Name" << setw(20) << "Category"
        << setw(10) << "Qty" << "Price" << endl;
    cout << "---------------------------------------------" << endl;

    for (int i = 0; i < count; i++) {
        cout << left << setw(20) << items[i].name << setw(20) << items[i].category
            << setw(10) << items[i].quantity << "$" << fixed << setprecision(2)
            << items[i].price << endl;
    }
}

void buyItem(Item items[], int count) {
    string itemName;
    int qty;

    cout << "Enter item to buy: ";
    getline(cin, itemName);
    cout << "Quantity: ";
    cin >> qty;

    int index = -1;
    for (int i = 0; i < count; i++) {
        if (items[i].name == itemName) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        cout << "Item not found in inventory!" << endl;
        return;
    }

    if (items[index].quantity < qty) {
        cout << "Insufficient quantity in stock!" << endl;
        return;
    }

    items[index].quantity -= qty;

    Transaction t;
    t.type = "BUY";
    t.itemName = itemName;
    t.quantity = qty;
    t.unitPrice = items[index].price;
    saveTransaction(t);

    double total = qty * items[index].price;
    cout << "Successfully purchased " << qty << " x " << itemName << " for $"
        << fixed << setprecision(2) << total << endl;
}

void returnItem(Item items[], int count) {
    string itemName;
    int qty;

    cout << "Enter item to return: ";
    getline(cin, itemName);
    cout << "Quantity: ";
    cin >> qty;

    int index = -1;
    for (int i = 0; i < count; i++) {
        if (items[i].name == itemName) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        cout << "Item not found in inventory!" << endl;
        return;
    }

    items[index].quantity += qty;

    Transaction t;
    t.type = "RETURN";
    t.itemName = itemName;
    t.quantity = qty;
    t.unitPrice = items[index].price;
    saveTransaction(t);

    cout << qty << " x " << itemName << " returned and added back to inventory." << endl;
}

void showProfitReport(Transaction txns[], int count) {
    double totalRevenue = 0.0;
    double totalRefunds = 0.0;

    for (int i = 0; i < count; i++) {
        double amount = txns[i].quantity * txns[i].unitPrice;
        if (txns[i].type == "BUY") {
            totalRevenue += amount;
        }
        else if (txns[i].type == "RETURN") {
            totalRefunds += amount;
        }
    }

    double netProfit = totalRevenue - totalRefunds;

    cout << "========== PROFIT REPORT ==========" << endl;
    cout << "Total Revenue: $" << fixed << setprecision(2) << totalRevenue << endl;
    cout << "Total Refunds: $" << fixed << setprecision(2) << totalRefunds << endl;
    cout << "Net Profit: $" << fixed << setprecision(2) << netProfit << endl;
    cout << "==================================" << endl;
}

void addNewItem() {
    if (inventoryCount >= 100) {
        cout << "Inventory is full!" << endl;
        return;
    }

    string name, category;
    int qty;
    double price;

    cout << "Enter item name: ";
    getline(cin, name);
    cout << "Enter category: ";
    getline(cin, category);
    cout << "Enter quantity: ";
    cin >> qty;
    cout << "Enter price: ";
    cin >> price;

    inventory[inventoryCount].name = name;
    inventory[inventoryCount].category = category;
    inventory[inventoryCount].quantity = qty;
    inventory[inventoryCount].price = price;

    inventoryCount++;
    cout << "Item added!" << endl;
}

void displayMenu() {
    cout << "\n******** Welcome to Store Inventory & Profit Tracker ********" << endl;
    cout << "Please choose one of the following operations:" << endl;
    cout << "1. Add New Item to Inventory" << endl;
    cout << "2. Display Inventory" << endl;
    cout << "3. Buy Item" << endl;
    cout << "4. Return Item" << endl;
    cout << "5. View Profit Report" << endl;
    cout << "6. Exit" << endl;
    cout << "-> ";
}

int main() {
    inventoryCount = loadInventory(inventory);

    int choice;

    while (true) {
        displayMenu();
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << endl;

        if (choice == 6) {
            saveInventory(inventory, inventoryCount);
            cout << "Inventory and transactions saved. Goodbye!" << endl;
            break;
        }

        switch (choice) {
        case 1:
            addNewItem();
            break;
        case 2:
            displayInventory(inventory, inventoryCount);
            break;
        case 3:
            buyItem(inventory, inventoryCount);
            break;
        case 4:
            returnItem(inventory, inventoryCount);
            break;
        case 5: {
            Transaction transactions[1000];
            int txnCount = loadTransactions(transactions);
            showProfitReport(transactions, txnCount);
            break;
        }
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}