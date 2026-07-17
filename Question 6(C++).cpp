#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>

using namespace std;

class Component {
private:
    string componentName;
    string componentCategory;
    string componentCode;
    int quantity;
    double unitPrice;
    int minimumStockLevel;
    double componentValue;

public:

    void setComponentDetails() {
        cout << "\nEnter component name: ";
        cin.ignore();
        getline(cin, componentName);

        cout << "Enter component category: ";
        getline(cin, componentCategory);

        cout << "Enter component code: ";
        getline(cin, componentCode);

        cout << "Enter quantity: ";
        cin >> quantity;

        cout << "Enter unit price: ";
        cin >> unitPrice;

        cout << "Enter minimum stock level: ";
        cin >> minimumStockLevel;
    }

    bool validateDetails() {
        if (quantity < 0 || unitPrice < 0 || minimumStockLevel < 0) {
            return false;
        }
        return true;
    }

    void calculateComponentValue() {
        componentValue = quantity * unitPrice;
    }

    string getStockStatus() {
        if (quantity == 0)
            return "Out of stock";
        else if (quantity > 0 && quantity <= minimumStockLevel)
            return "Low stock";
        else
            return "In stock";
    }

    double getComponentValue() {
        return componentValue;
    }

    void displayComponentDetails() {
        cout << fixed << setprecision(2);
        cout << "\nComponent: " << componentName << endl;
        cout << "Category: " << componentCategory << endl;
        cout << "Code: " << componentCode << endl;
        cout << "Quantity: " << quantity << endl;
        cout << "Unit Price: " << unitPrice << endl;
        cout << "Minimum Stock Level: " << minimumStockLevel << endl;
        cout << "Component Value: " << componentValue << endl;
        cout << "Stock Status: " << getStockStatus() << endl;
    }

    void saveComponentDetails(ofstream &file) {
        file << fixed << setprecision(2);
        file << "\nComponent: " << componentName << endl;
        file << "Category: " << componentCategory << endl;
        file << "Code: " << componentCode << endl;
        file << "Quantity: " << quantity << endl;
        file << "Unit Price: " << unitPrice << endl;
        file << "Minimum Stock Level: " << minimumStockLevel << endl;
        file << "Component Value: " << componentValue << endl;
        file << "Stock Status: " << getStockStatus() << endl;
    }
};

int main() {

    cout << "=============================================\n";
    cout << "ELECTRONIC COMPONENTS INVENTORY MANAGEMENT SYSTEM\n";
    cout << "=============================================\n";

    int numberOfComponents;
    cout << "\nEnter number of component types: ";
    cin >> numberOfComponents;

    while (numberOfComponents <= 0) {
        cout << "Invalid number. Enter again: ";
        cin >> numberOfComponents;
    }

    vector<Component> components;
    double totalInventoryValue = 0;

    ofstream file("components_inventory.txt");

    if (!file) {
        cout << "Error opening file!" << endl;
        return 1;
    }

    file << "ELECTRONIC COMPONENTS INVENTORY REPORT\n";
    file << "========================================\n";

    for (int i = 0; i < numberOfComponents; i++) {

        Component comp;

        comp.setComponentDetails();

        while (!comp.validateDetails()) {
            cout << "Invalid input detected! Please re-enter details.\n";
            comp.setComponentDetails();
        }

        comp.calculateComponentValue();
        totalInventoryValue += comp.getComponentValue();

        comp.displayComponentDetails();
        comp.saveComponentDetails(file);

        components.push_back(comp);
    }

    cout << fixed << setprecision(2);
    cout << "\nINVENTORY REPORT\n";
    cout << "Total Inventory Value: " << totalInventoryValue << endl;

    file << "\nTotal Inventory Value: " << totalInventoryValue << endl;

    file.close();

    cout << "\nReport saved to components_inventory.txt\n";
    cout << "\nThank you for using the system.\n";

    return 0;
}
