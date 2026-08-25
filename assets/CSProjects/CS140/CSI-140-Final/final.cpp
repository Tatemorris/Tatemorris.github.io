// Author: Tate Morris
// Class: CSI-140-01
// Assignment: Final
// Date Assigned: 11/19
// Due Date: 12/6 13:00
// 
// Description:
// Create a bank program with a log-in system and ways for tellers to access, add, remove, edit, and search client accounts.
//
// Certification of Authenticity:
// I certify that this is entirely my own work, except where I have given
// fully-documented references to the work of others. I understand the definition and
// consequences of plagiarism and acknowledge that the assessor of this assignment
// may, for the purpose of assessing this assignment:
// - Reproduce this assignment and provide a copy to another member of academic staff;
// and/or
// - Communicate a copy of this assignment to a plagiarism checking service (which may
// then retain a copy of this assignment on its database for the purpose of future
// plagiarism checkin
//Signed: Tate Morris Date: 12/3
// 

#include "header.h"
#include "functions.cpp"

int main()
{
    vector<string> tellers;
    vector<string> accounts;
    string loggedInTeller;

    cout << "Welcome to Goober Credit Union's Bank Telling System" << endl;
    cout << "----------------------------------------------------" << endl;

    loadTellersFromFile(tellers, "tellers.dat");

    login(tellers, loggedInTeller);

    if (!loggedInTeller.empty())
    {
        showMenu(accounts, loggedInTeller);
    }

    return 0;
}
