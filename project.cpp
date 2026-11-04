#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;

// Structure to store item details
struct Item {
    int id;
    string student;
    string name;
    string category;
    string location;
    string date;
    string status;
};

vector<Item> records;
int nextID = 1;

// Save records in file
void saveRecords() {
    ofstream file("lost_found.txt");

    for (auto item : records) {
        file << item.id << "|"
             << item.student << "|"
             << item.name << "|"
             << item.category << "|"
             << item.location << "|"
             << item.date << "|"
             << item.status << endl;
    }

    file.close();
}

// Load records from file
void loadRecords() {
    records.clear();

    ifstream file("lost_found.txt");
    string line;

    nextID = 1;

    while (getline(file, line)) {
        Item item;
        size_t pos;
        vector<string> data;

        stringstream ss(line);
        string part;

        while (getline(ss, part, '|')) {
            data.push_back(part);
        }

        if (data.size() == 7) {
            item.id = stoi(data[0]);
            item.student = data[1];
            item.name = data[2];
            item.category = data[3];
            item.location = data[4];
            item.date = data[5];
            item.status = data[6];

            records.push_back(item);

            if (item.id >= nextID)
                nextID = item.id + 1;
        }
    }

    file.close();
}

// Student login
bool login() {
    string id, password;

    cout << "\nEnter Student ID: ";
    cin >> id;

    cout << "Enter Password: ";
    cin >> password;

    if (id == "student" && password == "1234") {
        cout << "\nLogin Successful!\n";
        return true;
    }

    cout << "\nInvalid Login Details!\n";
    return false;
}

// Report lost item
void reportLost() {
    Item item;

    item.id = nextID++;
    item.student = "Student";

    cout << "\nEnter item name: ";
    cin >> item.name;

    cout << "Enter category: ";
    cin >> item.category;

    cout << "Enter lost location: ";
    cin >> item.location;

    cout << "Enter date (DD-MM-YYYY): ";
    cin >> item.date;

    item.status = "Lost";

    records.push_back(item);
    saveRecords();

    cout << "\nLost item reported successfully!\n";
    cout << "Record ID: " << item.id << endl;
}

// Report found item
void reportFound() {
    Item item;

    item.id = nextID++;
    item.student = "Student";

    cout << "\nEnter item name: ";
    cin >> item.name;

    cout << "Enter category: ";
    cin >> item.category;

    cout << "Enter found location: ";
    cin >> item.location;

    cout << "Enter date (DD-MM-YYYY): ";
    cin >> item.date;

    item.status = "Found";

    records.push_back(item);
    saveRecords();

    cout << "\nFound item reported successfully!\n";
    cout << "Record ID: " << item.id << endl;
}

// Search item
void searchItem() {
    string name;
    bool found = false;

    cout << "\nEnter item name to search: ";
    cin >> name;

    for (auto item : records) {
        if (item.name == name) {
            cout << "\nRecord ID: " << item.id;
            cout << "\nItem: " << item.name;
            cout << "\nCategory: " << item.category;
            cout << "\nLocation: " << item.location;
            cout << "\nDate: " << item.date;
            cout << "\nStatus: " << item.status << endl;

            found = true;
        }
    }

    if (!found)
        cout << "\nItem not found!\n";
}

// Automatic matching
void autoMatch() {
    bool found = false;

    cout << "\n------- MATCHED ITEMS -------\n";

    for (int i = 0; i < records.size(); i++) {
        for (int j = i + 1; j < records.size(); j++) {

            if (records[i].name == records[j].name &&
                records[i].category == records[j].category &&
                records[i].status != records[j].status) {

                cout << "\nPossible Match Found!";
                cout << "\nItem: " << records[i].name;
                cout << "\nLost Location: ";

                if (records[i].status == "Lost")
                    cout << records[i].location;
                else
                    cout << records[j].location;

                cout << "\nFound Location: ";

                if (records[i].status == "Found")
                    cout << records[i].location;
                else
                    cout << records[j].location;

                cout << "\nLost Record ID: "
                     << (records[i].status == "Lost" ?
                         records[i].id : records[j].id);

                cout << "\nFound Record ID: "
                     << (records[i].status == "Found" ?
                         records[i].id : records[j].id);

                cout << "\n";

                found = true;
            }
        }
    }

    if (!found)
        cout << "No matching records found.\n";
}

// View all records
void viewRecords() {
    cout << "\n------- ALL RECORDS -------\n";

    if (records.empty()) {
        cout << "No records available.\n";
        return;
    }

    for (auto item : records) {
        cout << "\nID: " << item.id;
        cout << "\nStudent: " << item.student;
        cout << "\nName: " << item.name;
        cout << "\nCategory: " << item.category;
        cout << "\nLocation: " << item.location;
        cout << "\nDate: " << item.date;
        cout << "\nStatus: " << item.status << "\n";
    }
}

// Delete record
void deleteRecord() {
    int id;
    bool found = false;

    cout << "\nEnter record ID to delete: ";
    cin >> id;

    for (int i = 0; i < records.size(); i++) {
        if (records[i].id == id) {
            records.erase(records.begin() + i);
            saveRecords();

            cout << "\nRecord deleted successfully!\n";
            found = true;
            break;
        }
    }

    if (!found)
        cout << "\nRecord not found!\n";
}

// Item statistics
void statistics() {
    int lost = 0, found = 0;

    for (auto item : records) {
        if (item.status == "Lost")
            lost++;
        else if (item.status == "Found")
            found++;
    }

    cout << "\n------- ITEM STATISTICS -------\n";
    cout << "Total Records: " << records.size();
    cout << "\nLost Items: " << lost;
    cout << "\nFound Items: " << found;
    cout << "\n";
}

// Export report
void exportReport() {
    ofstream file("Campus_Report.txt");

    file << "SMART CAMPUS LOST AND FOUND REPORT\n";
    file << "==================================\n";

    for (auto item : records) {
        file << "\nID: " << item.id;
        file << "\nItem: " << item.name;
        file << "\nCategory: " << item.category;
        file << "\nLocation: " << item.location;
        file << "\nDate: " << item.date;
        file << "\nStatus: " << item.status << "\n";
    }

    file.close();

    cout << "\nReport exported successfully!\n";
    cout << "File Name: Campus_Report.txt\n";
}

// Main function
int main() {
    int choice;

    cout << "====================================\n";
    cout << " SMART CAMPUS LOST & FOUND SYSTEM\n";
    cout << "====================================\n";

    if (!login())
        return 0;

    loadRecords();

    do {
        cout << "\n========== MAIN MENU ==========\n";
        cout << "1. Report Lost Item\n";
        cout << "2. Report Found Item\n";
        cout << "3. Search Item\n";
        cout << "4. Auto Match Lost & Found\n";
        cout << "5. View All Records\n";
        cout << "6. Delete Record\n";
        cout << "7. Item Statistics\n";
        cout << "8. Export Report\n";
        cout << "9. Exit\n";

        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: reportLost(); break;
            case 2: reportFound(); break;
            case 3: searchItem(); break;
            case 4: autoMatch(); break;
            case 5: viewRecords(); break;
            case 6: deleteRecord(); break;
            case 7: statistics(); break;
            case 8: exportReport(); break;
            case 9:
                cout << "\nThank you for using the system!\n";
                break;
            default:
                cout << "\nInvalid choice!\n";
        }

    } while (choice != 9);

    return 0;
}