#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

const string TELLERS_FILE = "tellers.dat";
const string ACCOUNTS_FILE = "accounts.dat";

bool convertStr2Double(string stringValue, double &doubleValue);
string toUpper(string str);
void loadTellersFromFile(vector<string>& tellers, const string& filename);
void displayMenu();
void login(const vector<string>& tellers, string& loggedInTeller);
bool authenticate(const vector<string>& tellers, const string& username, const string& password);
void createAccount(vector<string>& accounts, const string& filename);
void deleteAccount(vector<string>& accounts, const string& filename);
void updateAccount(vector<string>& accounts, const string& filename);
void searchAccount(const vector<string>& accounts);
void showMenu(vector<string>& accounts, string& loggedInTeller);

#endif