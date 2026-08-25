#include "datapoint.h"

/**
 * Purpose of the function
 * Constructor that initializes all attributes to default values.
 * Pre-condition: The DataPoint object is being created.
 * Post-condition: All attributes are initialized to default values.
 */
DataPoint::DataPoint()
{
    for (int i = 0; i < 22; i++)
    {
        attributes[i] = 0; 
    }
    classification = ' ';
    mDistance = 0.0;
}

/**
 * Purpose of the function
 * Copy constructor that initializes the object with the values from another DataPoint.
 * Pre-condition: A DataPoint object exists to copy from.
 * Post-condition: The current object is initialized with the values of the other object.
 */
DataPoint::DataPoint(const DataPoint& other)
{
    for (int i = 0; i < 22; i++)
    {
        attributes[i] = other.attributes[i];
    }
    classification = other.classification;
    mDistance = other.mDistance;
}

/**
 * Purpose of the function
 * Destructor that ensures proper memory cleanup.
 * Pre-condition: The DataPoint object is being destroyed.
 * Post-condition: No resources are left allocated for the object.
 */
DataPoint::~DataPoint() {}

/**
 * Purpose of the function
 * Getter for an attribute of the DataPoint.
 * Pre-condition: The DataPoint object is valid.
 * Post-condition: Returns the value of the requested attribute.
 */
double DataPoint::getAttribute(int index) const
{
    if (index >= 0 && index < 22)
    {
        return attributes[index];
    }
    return -1; // Invalid index
}


/**
 * Purpose of the function
 * Getter for the classification of the DataPoint.
 * Pre-condition: The DataPoint object is valid.
 * Post-condition: Returns the classification of the DataPoint ('e' or 'p').
 */
char DataPoint::getClassification() const
{
    return classification;
}

/**
 * Purpose of the function
 * Getter for the distance of the DataPoint.
 * Pre-condition: The DataPoint object is valid.
 * Post-condition: Returns the distance of the DataPoint.
 */
double DataPoint::getDistance() const
{
    return mDistance;
}

/**
 * Purpose of the function
 * Overload equality operator to compare two DataPoint objects.
 * Pre-condition: The two DataPoint objects are valid.
 * Post-condition: Returns true if all attributes and classification match, otherwise false.
 */
bool DataPoint::operator==(const DataPoint& other) const
{
    for (int i = 0; i < 22; i++)
    {
        if (attributes[i] != other.attributes[i])
        {
            return false;
        }
    }
    return classification == other.classification;
}

/**
 * Purpose of the function
 * Overload assignment operator to copy data from another DataPoint object.
 * Pre-condition: The DataPoint object to copy from exists.
 * Post-condition: The current object is assigned the values of the other DataPoint.
 */
DataPoint& DataPoint::operator=(const DataPoint& other)
{
    if (this != &other)
    {
        for (int i = 0; i < 22; i++)
        {
            attributes[i] = other.attributes[i];
        }
        classification = other.classification;
        mDistance = other.mDistance;
    }
    return *this;
}

/**
 * Purpose of the function
 * Overload less-than operator to compare two DataPoint objects based on distance.
 * Pre-condition: The two DataPoint objects are valid.
 * Post-condition: Returns true if the left DataPoint has a smaller distance than the right.
 */
bool DataPoint::operator<(const DataPoint& other) const
{
    return mDistance < other.mDistance;
}

/**
 * Purpose of the function
 * Overload greater-than operator to compare two DataPoint objects based on distance.
 * Pre-condition: The two DataPoint objects are valid.
 * Post-condition: Returns true if the left DataPoint has a greater distance than the right.
 */
bool DataPoint::operator>(const DataPoint& other) const
{
    return mDistance > other.mDistance;
}

/**
 * Purpose of the function
 * Overload stream insertion operator to output the DataPoint information.
 * Pre-condition: The DataPoint object is valid.
 * Post-condition: The DataPoint attributes and classification are printed.
 */
ostream& operator<<(ostream& output, const DataPoint& dp)
{
    for (int i = 0; i < 22; i++)
    {
        output << dp.attributes[i] << " ";
    }
    output << dp.classification;
    return output;
}

/**
 * Function: operator>>
 * Description: Overloaded input stream operator to read a DataPoint object from an input stream.
 * Parameters: istream& is, DataPoint& dp (the input stream and DataPoint object to read into)
 * Return: istream& (returns the input stream to allow chaining)
 */
std::istream& operator>>(std::istream& input, DataPoint& dp)
{
    // Read the 22 attributes for the mushroom
    for (int i = 0; i < 22; ++i)
    {
        input >> dp.attributes[i];
    }

    // Check if there is a classification in the current file (only for data.txt)
    // This is for data.txt where classification exists, but testdata.txt doesn't have it
    if (input.peek() != '\n' && input.peek() != EOF)
    {
        char classification;
        input >> classification;
        dp.classification = classification; // Set classification as 'e' or 'p'
    }

    return input;
}



/**
 * Purpose of the function
 * Setter for an attribute of the DataPoint.
 * Pre-condition: The DataPoint object is valid and the index is in range.
 * Post-condition: The specified attribute is set to the given value.
 */
void DataPoint::setAttribute(int index, double value)
{
    if (index >= 0 && index < 22)
    {
        attributes[index] = value;
    }
}

/**
 * Purpose of the function
 * Setter for the classification of the DataPoint.
 * Pre-condition: The DataPoint object is valid.
 * Post-condition: The classification is updated to the given value.
 */
void DataPoint::setClassification(char classification)
{
    this->classification = classification;
}

/**
 * Purpose of the function
 * Setter for the distance of the DataPoint.
 * Pre-condition: The DataPoint object is valid.
 * Post-condition: The distance is updated to the given value.
 */
void DataPoint::setDistance(double distance)
{
    mDistance = distance;
}
