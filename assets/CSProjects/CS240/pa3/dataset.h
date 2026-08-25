#ifndef DATASET_H
#define DATASET_H

#include "datapoint.h"

struct DataSet
{
    struct Node
    {
        DataPoint mData;
        Node* mNext;
    };

    Node* head;
    Node* tail;
    int count;

    // Default constructor
    DataSet();

    // Destructor
    ~DataSet();

    // Getters
    int getCount() const;
    Node* getHead() const;
    Node* getTail() const;


    //List Manip Functions

    // Insert a new DataPoint
    void insert(const DataPoint& dp);

    // Check if a DataPoint exists
    bool isExist(const DataPoint& dp) const;

    // Load data points from a file
    void load(const string& filename);

    // Remove a DataPoint
    void remove(const DataPoint& dp);

    // Store data points into a file
    void store(const string& filename) const;

};

#endif
