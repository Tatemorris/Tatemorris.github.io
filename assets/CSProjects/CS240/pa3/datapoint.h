#ifndef DATAPOINT_H
#define DATAPOINT_H

#include <iostream>
#include <cmath>

using namespace std;

class DataPoint
{
private:
    double attributes[22]; // The 22 attributes of the mushroom
    char classification; // 'e' for edible or 'p' for poisonous
    double mDistance; // Used to store the distance from a test point

public:
    // Default constructor
    DataPoint();

    // Copy constructor
    DataPoint(const DataPoint& other);

    // Destructor
    ~DataPoint();

    // Getters
    double getAttribute(int index) const;
    char getClassification() const;
    double getDistance() const;

    // Operator Overloads
    bool operator==(const DataPoint& other) const;
    DataPoint& operator=(const DataPoint& other);
    bool operator<(const DataPoint& other) const;
    bool operator>(const DataPoint& other) const;
    friend ostream& operator<<(ostream& os, const DataPoint& dp);
    friend istream& operator>>(istream& is, DataPoint& dp);

    // Setters
    void setAttribute(int index, double value);
    void setClassification(char classification);
    void setDistance(double distance);
};

#endif
