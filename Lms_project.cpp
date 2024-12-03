#include <iostream>
#include <string>
#include <fstream>
using namespace std;

struct Record {
    string name;
    string bookTitle;
    string type; // "Donor" or "Receiver"
};

class BookDonationSystem {
private:
    static const int MAX_RECORDS = 100;
    Record records[MAX_RECORDS];
    int recordCount;

public:
    BookDonationSystem() : recordCount(0) {
        loadFromFile(); // Load existing records from file
    }

    void saveToFile() {
        ofstream outFile("records.txt", ios::trunc);
        if (!outFile) {
            cout << "Error opening file for saving.\n";
            return;
        }
        for (int i = 0; i < recordCount; i++) {
            outFile << records[i].name << endl;
            outFile << records[i].bookTitle << endl;
            outFile << records[i].type << endl;
        }
        outFile.close();
        cout << "Records saved to file successfully.\n";
    }

    void loadFromFile() {
        ifstream inFile("records.txt");
        if (!inFile) {
            cout << "No previous records found.\n";
            return;
        }
        recordCount = 0;
        while (!inFile.eof() && recordCount < MAX_RECORDS) {
            getline(inFile, records[recordCount].name);
            getline(inFile, records[recordCount].bookTitle);
            getline(inFile, records[recordCount].type);
            if (!records[recordCount].name.empty()) { // Avoid adding empty records
                recordCount++;
            }
        }
        inFile.close();
        cout << "Records loaded from file successfully.\n";
    }

    void addRecord() {
        if (recordCount >= MAX_RECORDS) {
            cout << "Record storage is full.\n";
            return;
        }

        Record newRecord;
        cout << "Enter Name: ";
        cin.ignore();
        getline(cin, newRecord.name);
        cout << "Enter Book Title: ";
        getline(cin, newRecord.bookTitle);
        cout << "Enter Type (Donor/Receiver): ";
        getline(cin, newRecord.type);

        records[recordCount++] = newRecord;
        cout << "Record added successfully.\n";
        saveToFile();
    }

    void deleteRecord() {
        string name;
        cout << "Enter the name to delete record: ";
        cin.ignore();
        getline(cin, name);

        for (int i = 0; i < recordCount; i++) {
            if (records[i].name == name) {
                for (int j = i; j < recordCount - 1; j++) {
                    records[j] = records[j + 1];
                }
                recordCount--;
                cout << "Record deleted successfully.\n";
                saveToFile();
                return;
            }
        }
        cout << "Record not found.\n";
    }

    void updateRecord() {
        string name;
        cout << "Enter the name to update record: ";
        cin.ignore();
        getline(cin, name);

        for (int i = 0; i < recordCount; i++) {
            if (records[i].name == name) {
                cout << "Enter new Name: ";
                getline(cin, records[i].name);
                cout << "Enter new Book Title: ";
                getline(cin, records[i].bookTitle);
                cout << "Enter new Type (Donor/Receiver): ";
                getline(cin, records[i].type);
                cout << "Record updated successfully.\n";
                saveToFile();
                return;
            }
        }
        cout << "Record not found.\n";
    }

    void searchBook() {
        string title;
        cout << "Enter Book Title to search: ";
        cin.ignore();
        getline(cin, title);

        bool found = false;
        for (int i = 0; i < recordCount; i++) {
            if (records[i].bookTitle == title) {
                cout << "Name: " << records[i].name << ", Type: " << records[i].type << "\n";
                found = true;
            }
        }
        if (!found) {
            cout << "Book not found in records.\n";
        }
    }

    void displayRecords() {
        if (recordCount == 0) {
            cout << "No records available.\n";
            return;
        }

        for (int i = 0; i < recordCount; i++) {
            cout << "Name: " << records[i].name
                 << ", Book Title: " << records[i].bookTitle
                 << ", Type: " << records[i].type << "\n";
        }
    }

    void menu() {
        int choice;
        do {
            cout << "\nBook Donation System Menu:\n";
            cout << "1. Add Record of donor/receiver\n";
            cout << "2. Delete Record of donor/receiver\n";
            cout << "3. Update Record\n";
            cout << "4. Search a particular Book (using Book Title)\n";
            cout << "5. Display all records\n";
            cout << "6. Exit\n";
            cout << "Enter choice: ";
            cin >> choice;

            switch (choice) {
                case 1: addRecord(); break;
                case 2: deleteRecord(); break;
                case 3: updateRecord(); break;
                case 4: searchBook(); break;
                case 5: displayRecords(); break;
                case 6: cout << "Exiting...\n"; break;
                default: cout << "Invalid choice. Please try again.\n";
            }
        } while (choice != 6);
    }
};

int main() {
    BookDonationSystem system;
    system.menu();
    return 0;
}
