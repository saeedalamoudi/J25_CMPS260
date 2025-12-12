#include <iostream>
#include <string>
#include <iomanip>
#include <limits>

using namespace std;

class Item {
private:
    string name;
    double price;

protected:
    Item(string itemName, double itemPrice) {
        name = itemName;
        price = itemPrice;
    }

    double getPriceBase() const {
        return price;
    }

public:
    virtual void display() const = 0;
    virtual double getPrice() const = 0;
    virtual void receiptEntry() const = 0;

    string getName() const {
        return name;
    }

    virtual ~Item() {}
};

class FoodItem : public Item {
private:
    string expirationDate;

public:
    FoodItem(string itemName, double itemPrice, string expDate)
        : Item(itemName, itemPrice) {
        expirationDate = expDate;
    }

    void display() const override {
        cout << "Name: " << getName() << " | Price: $" << fixed << setprecision(2)
            << getPrice() << " | Exp: " << expirationDate << endl;
    }

    double getPrice() const override {
        return getPriceBase();
    }

    void receiptEntry() const override {
        cout << getName() << " - $" << fixed << setprecision(2) << getPrice() << endl;
    }
};

class ElectronicItem : public Item {
private:
    int warrantyMonths;

public:
    ElectronicItem(string itemName, double itemPrice, int warranty)
        : Item(itemName, itemPrice) {
        warrantyMonths = warranty;
    }

    void display() const override {
        cout << "Name: " << getName() << " | Price: $" << fixed << setprecision(2)
            << getPrice() << " | Warranty: " << warrantyMonths << " months" << endl;
    }

    double getPrice() const override {
        return getPriceBase();
    }

    void receiptEntry() const override {
        cout << getName() << " - $" << fixed << setprecision(2) << getPrice() << endl;
    }
};

Item* store[50];
int storeCount = 0;

Item* purchases[20];
int purchaseCount = 0;

void addItemToStore() {
    if (storeCount >= 50) {
        cout << "Store is full!" << endl;
        return;
    }

    string type, itemName, expDate;
    double itemPrice;
    int warranty;

    cout << "Enter item type (Food/Electronic): ";
    getline(cin, type);

    cout << "Enter item name: ";
    getline(cin, itemName);

    cout << "Enter price: ";
    cin >> itemPrice;
    cin.ignore();

    if (type == "Food" || type == "food") {
        cout << "Enter expiration date: ";
        getline(cin, expDate);
        store[storeCount] = new FoodItem(itemName, itemPrice, expDate);
    }
    else if (type == "Electronic" || type == "electronic") {
        cout << "Enter warranty in months: ";
        cin >> warranty;
        cin.ignore();
        store[storeCount] = new ElectronicItem(itemName, itemPrice, warranty);
    }
    else {
        cout << "Invalid item type!" << endl;
        return;
    }

    storeCount++;
    cout << "Item added successfully!" << endl;
}

void displayAvailableItems() {
    if (storeCount == 0) {
        cout << "No items in store." << endl;
        return;
    }

    for (int i = 0; i < storeCount; i++) {
        store[i]->display();
    }
}

void buyItem() {
    if (purchaseCount >= 20) {
        cout << "Cart is full!" << endl;
        return;
    }

    string itemName;
    cout << "Enter item name: ";
    getline(cin, itemName);

    int index = -1;
    for (int i = 0; i < storeCount; i++) {
        if (store[i]->getName() == itemName) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        cout << "Item not found." << endl;
        return;
    }

    purchases[purchaseCount] = store[index];
    purchaseCount++;

    cout << "Purchased " << store[index]->getName() << " for $"
        << fixed << setprecision(2) << store[index]->getPrice() << endl;
}

void viewReceipt() {
    if (purchaseCount == 0) {
        cout << "No items purchased yet." << endl;
        return;
    }

    cout << "---- Receipt ----" << endl;

    double total = 0.0;

    for (int i = 0; i < purchaseCount; i++) {
        cout << (i + 1) << ". ";
        purchases[i]->receiptEntry();
        total += purchases[i]->getPrice();
    }

    cout << "Total: $" << fixed << setprecision(2) << total << endl;
}

void displayMenu() {
    cout << "\n************* Welcome to QuickMart POS *************" << endl;
    cout << "1 - Add item to store" << endl;
    cout << "2 - Display available items" << endl;
    cout << "3 - Buy item by name" << endl;
    cout << "4 - View receipt" << endl;
    cout << "0 - Exit" << endl;
    cout << "Choice: ";
}

int main() {
    int choice;

    while (true) {
        displayMenu();
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << endl;

        if (choice == 0) {
            cout << "Thank you for shopping at QuickMart!" << endl;
            break;
        }

        switch (choice) {
        case 1:
            addItemToStore();
            break;
        case 2:
            displayAvailableItems();
            break;
        case 3:
            buyItem();
            break;
        case 4:
            viewReceipt();
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    }

    for (int i = 0; i < storeCount; i++) {
        delete store[i];
    }

    return 0;
}