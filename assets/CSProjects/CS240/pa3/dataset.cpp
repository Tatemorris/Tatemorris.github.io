#include "dataset.h"
#include <iostream>
#include <fstream>

using namespace std;

/**
 * Purpose: Initializes an empty DataSet object.
 * Pre-condition: None.
 * Post-condition: The DataSet object is initialized with head as nullptr, tail as nullptr, and count as 0.
 */
DataSet::DataSet()
{
    head = nullptr;
    tail = nullptr;
    count = 0;
}

/**
 * Purpose: Destroys the DataSet object and deallocates memory for its nodes.
 * Pre-condition: A DataSet object exists with dynamically allocated nodes.
 * Post-condition: All nodes are deleted, and memory is deallocated.
 */
DataSet::~DataSet()
{
    Node* current = head;
    while (current != nullptr)
    {
        Node* temp = current;
        current = current->mNext;
        delete temp;
    }
}


/**
 * Purpose: Returns the number of DataPoints in the DataSet.
 * Pre-condition: The DataSet object is properly initialized.
 * Post-condition: Returns the count of nodes in the DataSet.
 */
int DataSet::getCount() const
{
    return count;
}

/**
 * Purpose: Returns the head of the DataSet.
 * Pre-condition: The DataSet object is properly initialized.
 * Post-condition: Returns a pointer to the head node of the DataSet.
 */
DataSet::Node* DataSet::getHead() const
{
    return head;
}

/**
 * Purpose: Returns the tail of the DataSet.
 * Pre-condition: The DataSet object is properly initialized.
 * Post-condition: Returns a pointer to the tail node of the DataSet.
 */
DataSet::Node* DataSet::getTail() const
{
    return tail;
}


/**
 * Purpose: Inserts a new DataPoint into the DataSet.
 * Pre-condition: A valid DataPoint object is passed as an argument.
 * Post-condition: A new node containing the DataPoint is inserted at the end of the DataSet.
 */
void DataSet::insert(const DataPoint& dp)
{
    Node* newNode = new Node;
    newNode->mData = dp;
    newNode->mNext = nullptr;

    if (tail != nullptr)
    {
        tail->mNext = newNode;
    }
    else
    {
        head = newNode;
    }
    tail = newNode;
    count++;
}

/**
 * Purpose: Checks if a DataPoint exists in the DataSet.
 * Pre-condition: A valid DataPoint object is passed as an argument.
 * Post-condition: Returns true if the DataPoint exists in the DataSet, false otherwise.
 */
bool DataSet::isExist(const DataPoint& dp) const
{
    Node* current = head;
    while (current != nullptr)
    {
        if (current->mData == dp)
        {
            return true;
        }
        current = current->mNext;
    }
    return false;
}

/**
 * Purpose: Loads DataPoints from a file into the DataSet.
 * Pre-condition: A valid file name is passed and the file exists.
 * Post-condition: DataPoints from the file are inserted into the DataSet.
 */
void DataSet::load(const string& filename)
{
    ifstream file(filename);
    if (!file)
    {
        cout << "Failed to open file!" << endl;
        return;
    }

    DataPoint dp;
    while (file >> dp)
    {
        insert(dp);
    }
    file.close();
}

/**
 * Purpose: Removes a DataPoint from the DataSet.
 * Pre-condition: A valid DataPoint object is passed as an argument.
 * Post-condition: The specified DataPoint is removed from the DataSet, if it exists.
 */
void DataSet::remove(const DataPoint& dp)
{
    Node* current = head;
    Node* prev = nullptr;
    while (current != nullptr && !(current->mData == dp))
    {
        prev = current;
        current = current->mNext;
    }

    if (current == nullptr) return; // Not found

    if (prev != nullptr)
    {
        prev->mNext = current->mNext;
    }
    else
    {
        head = current->mNext;
    }

    if (current == tail)
    {
        tail = prev;
    }

    delete current;
    count--;
}

/**
 * Purpose: Stores all DataPoints in the DataSet to a file.
 * Pre-condition: A valid file name is passed.
 * Post-condition: All DataPoints are written to the specified file.
 */
void DataSet::store(const string& filename) const
{
    ofstream file(filename);
    if (!file)
    {
        cout << "Failed to open file!" << endl;
        return;
    }

    Node* current = head;
    while (current != nullptr)
    {
        file << current->mData << endl;
        current = current->mNext;
    }
    file.close();
}
