#include "header.h"

using namespace std;

/*** Purpose: convert a string to double
* Pre: the string to be converted is stored in stringValue
* Post: The numeric value for the given string in doubleValue and
* true if the string can be converted into double and false if
* the string cannot be converted into a double
*************************************************************************/
bool convertStr2Double(string stringValue, double &doubleValue)
{
    stringstream ss;
    ss << stringValue;
    ss >> doubleValue;

    if (ss.fail() || !ss.eof())
        return false;
    else
        return true;
}

/*** Purpose: convert a string to uppercase
* Pre: the string to be converted is stored in str
* Post: The string in the uppercase
*************************************************************************/
string toUpper(string str)
{
    for (size_t i = 0; i < str.length(); ++i)
        str[i] = toupper(str[i]);
    return str;
}

void loadTellersFromFile(vector<string>& tellers, const string& filename) 
{
    ifstream file(filename);
    string line;

    while (getline(file, line)) 
    {
        tellers.push_back(line);
    }

    file.close();
}

void displayMenu() 
{
    cout << "1. Create new account\n";
    cout << "2. Delete existing account\n";
    cout << "3. Update account information\n";
    cout << "4. Search for account information\n";
    cout << "5. Logout\n";
    cout << "Enter your choice: ";
}

bool authenticate(const vector<string>& tellers, const string& username, const string& password) 
{
    for (const string& entry : tellers) 
    {
        size_t spacePos = entry.find(' '); // Find the space that separates the username and password
        if (spacePos != string::npos) 
        {
            string storedUsername = entry.substr(0, spacePos);
            string storedPassword = entry.substr(spacePos + 1);

            // Check if the input username and password match the stored ones
            if (storedUsername == username && storedPassword == password) 
            {
                return true;
            }
        }
    }
    return false;
}

void login(const vector<string>& tellers, string& loggedInTeller) {
    string username;
    string password;
    bool success = false;
    const int MAX_ATTEMPTS = 3; // Maximum number of login attempts
    int attempts = 0;

    while (attempts < MAX_ATTEMPTS) {
        cout << "Enter username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;

        if (authenticate(tellers, username, password)) {
            loggedInTeller = username;
            cout << "Login successful!" << endl;
            success = true;
            break; // Exit the loop on successful login
        } else {
            attempts++;
            cout << "Login failed. You have " << (MAX_ATTEMPTS - attempts) << " attempt(s) left." << endl;
        }
    }

    if (!success) {
        cout << "All login attempts failed. Exiting..." << endl;
    }
}

void createAccount(vector<string>& accounts, const string& filename) 
{
    // Seed the random number generator with the current time
    srand(static_cast<int>(time(0)));

    int newID;
    bool isUnique;

    do {
        // Generate a random 5-digit number
        newID = 10000 + rand() % 90000; // Ensures a 5-digit number in the range 10000-99999
        isUnique = true;

        // Check if the ID already exists
        for (const string& account : accounts) {
            if (to_string(newID) == account) {
                isUnique = false;
                break;
            }
        }
    } while (!isUnique);

    string ssn, name, address, phone;

    // Collect account details
    cout << "Enter Social Security Number (format: XXX-XX-XXXX): ";
    cin.ignore();
    getline(cin, ssn);

    cout << "Enter Full Name: ";
    getline(cin, name);

    cout << "Enter Address: ";
    getline(cin, address);

    cout << "Enter Phone Number (format: XXX XXX XXXX): ";
    getline(cin, phone);

    // Save account details
    ofstream file(filename, ios::app);
    if (file.is_open()) {
        file << newID << endl;
        file << ssn << endl;
        file << name << endl;
        file << address << endl;
        file << phone << endl;
        file.close();
    } else {
        cout << "Error: Could not open file to save account." << endl;
    }

    // Add the account ID to the vector for future uniqueness checks
    accounts.push_back(to_string(newID));

    cout << "Account created successfully with ID: " << newID << endl;
}

void deleteAccount(vector<string>& accounts, const string& idToDelete) 
{
    for (size_t i = 0; i < accounts.size(); ++i) 
    {
        if (accounts[i] == idToDelete)  // Ensure comparison matches your data structure
        {
            accounts.erase(accounts.begin() + i);
            cout << "Account with ID " << idToDelete << " has been deleted.\n";
            return;
        }
    }
    cout << "Account with ID " << idToDelete << " not found.\n";
}

void updateAccount(const string& filename) 
{
    string accountID;
    cout << "Enter the account ID to update: ";
    cin >> accountID;

    ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        cout << "Error: Could not open file." << endl;
        return;
    }

    vector<string> fileContents;
    string line;
    bool accountFound = false;

    while (getline(inputFile, line)) {
        fileContents.push_back(line);
    }
    inputFile.close();

    for (size_t i = 0; i < fileContents.size(); i += 5) {
        if (fileContents[i] == accountID) {
            accountFound = true;
            string newName, newAddress, newPhone;
            int choice;

            cout << "What would you like to update?\n";
            cout << "1. Name\n2. Address\n3. Phone Number\nEnter choice: ";
            cin >> choice;
            cin.ignore(); // Clear input buffer

            if (choice == 1) {
                cout << "Enter new name: ";
                getline(cin, newName);
                fileContents[i + 2] = newName;
            } else if (choice == 2) {
                cout << "Enter new address: ";
                getline(cin, newAddress);
                fileContents[i + 3] = newAddress;
            } else if (choice == 3) {
                cout << "Enter new phone number: ";
                getline(cin, newPhone);
                fileContents[i + 4] = newPhone;
            } else {
                cout << "Invalid choice." << endl;
                return;
            }

            break;
        }
    }

    if (!accountFound) {
        cout << "Account with ID " << accountID << " not found." << endl;
        return;
    }

    ofstream outputFile(filename);
    if (!outputFile.is_open()) {
        cout << "Error: Could not open file for writing." << endl;
        return;
    }

    for (const string& content : fileContents) {
        outputFile << content << endl;
    }
    outputFile.close();

    cout << "Account updated successfully." << endl;
}


void searchAccount(const string& filename) {
    string accountID;
    cout << "Enter the account ID to search for: ";
    cin >> accountID;

    ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        cout << "Error: Could not open file." << endl;
        return;
    }

    string line;
    vector<string> accountDetails;
    bool accountFound = false;

    while (getline(inputFile, line)) {
        accountDetails.push_back(line);
    }
    inputFile.close();

    for (size_t i = 0; i < accountDetails.size(); i += 5) {
        if (accountDetails[i] == accountID) {
            accountFound = true;

            cout << "Account Details:\n";
            cout << "ID: " << accountDetails[i] << endl;
            cout << "SSN: " << accountDetails[i + 1] << endl;
            cout << "Name: " << accountDetails[i + 2] << endl;
            cout << "Address: " << accountDetails[i + 3] << endl;
            cout << "Phone: " << accountDetails[i + 4] << endl;

            break;
        }
    }

    if (!accountFound) {
        cout << "Account with ID " << accountID << " not found." << endl;
    }
}


void showMenu(vector<string>& accounts, string& loggedInTeller)
{
    int choice;

    cout << "Hello " << loggedInTeller << "! What would you like to do today?" << endl;
    do
    {
        displayMenu();
        cin >> choice;

        switch (choice)
        {
            case 1:
                createAccount(accounts, "accounts.dat");
                break;
            case 2:
                {
                    string idToDelete;
                    cout << "Enter account ID to delete: ";
                    cin >> idToDelete;
                    deleteAccount(accounts, idToDelete);
                }
                break;
            case 3:
                updateAccount(accounts, "accounts.dat");
                break;
            case 4:
                searchAccount(accounts);
                break;
            case 5:
                cout << "Logging out...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 5);
}
