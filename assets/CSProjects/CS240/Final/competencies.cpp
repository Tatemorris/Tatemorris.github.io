//  filename:  competencies.cpp

/*
       Author:  [Your Name]
        Class: CSI-240-03
   Assignment: Final Project
Date Assigned: April 1, 2025
     Due Date: 13:00 EST April 25, 2025

Description:
   Implementation of the Competency class, which is a child of Course
   and stores competency information for courses.

Certification of Authenticity:
   I certify that this is entirely my own work, except where I have
   given fully-documented references to the work of others.
*/

#include "competencies.h"

/*************************************************************
* Function: Competency()                                     *
* Purpose: Default constructor for Competency class          *
* Pre-condition: None                                        *
* Post-condition: A Competency object is created with        *
*                 default values                             *
* Author: [Your Name]                                        *
**************************************************************/
Competency::Competency() : Course()
{
    mCompetencyCount = 0;
    mCompetencyList = NULL;
}

/*************************************************************
* Function: Competency(string, string, string)               *
* Purpose: Parameterized constructor for Competency class    *
* Pre-condition: Valid strings for parameters                *
* Post-condition: A Competency object is created with given  *
*                 values                                     *
* Author: [Your Name]                                        *
**************************************************************/
Competency::Competency(string code, string title, string major)
    : Course(code, title, major)
{
    mCompetencyCount = 0;
    mCompetencyList = NULL;
}

/*************************************************************
* Function: Competency(const Competency&)                    *
* Purpose: Copy constructor for Competency class             *
* Pre-condition: Valid Competency object to copy             *
* Post-condition: A new Competency object is created as a    *
*                 copy                                       *
* Author: [Your Name]                                        *
**************************************************************/
Competency::Competency(const Competency& obj) : Course(obj)
{
    // Delete existing array if needed
    if (mCompetencyList != NULL)
    {
        delete[] mCompetencyList;
        mCompetencyList = NULL;
    }

    mCompetencyCount = obj.mCompetencyCount;

    if (mCompetencyCount > 0)
    {
        mCompetencyList = new CompetencyMap[mCompetencyCount];

        // Copy competency data
        for (int i = 0; i < mCompetencyCount; i++)
        {
            mCompetencyList[i] = obj.mCompetencyList[i];
        }
    }
    else
    {
        mCompetencyList = NULL;
    }
}

/*************************************************************
* Function: ~Competency()                                    *
* Purpose: Destructor for Competency class                   *
* Pre-condition: None                                        *
* Post-condition: Dynamically allocated memory is freed      *
* Author: [Your Name]                                        *
**************************************************************/
Competency::~Competency()
{
    if (mCompetencyList != NULL)
    {
        delete[] mCompetencyList;
        mCompetencyList = NULL;
    }
}

/*************************************************************
* Function: getCompetencyCount()                             *
* Purpose: Get the number of competencies                    *
* Pre-condition: None                                        *
* Post-condition: Returns the number of competencies         *
* Author: [Your Name]                                        *
**************************************************************/
int Competency::getCompetencyCount()
{
    return mCompetencyCount;
}

/*************************************************************
* Function: getCompetency(int)                               *
* Purpose: Get a specific competency                         *
* Pre-condition: Valid index                                 *
* Post-condition: Returns the specified competency           *
* Author: [Your Name]                                        *
**************************************************************/
CompetencyMap Competency::getCompetency(int index)
{
    if (index >= 0 && index < mCompetencyCount)
    {
        return mCompetencyList[index];
    }

    // Return default if index is invalid
    return CompetencyMap();
}

/*************************************************************
* Function: setCompetency(int, CompetencyMap)                *
* Purpose: Set a specific competency                         *
* Pre-condition: Valid index and competency                  *
* Post-condition: The specified competency is updated        *
* Author: [Your Name]                                        *
**************************************************************/
void Competency::setCompetency(int index, CompetencyMap competency)
{
    if (index >= 0 && index < mCompetencyCount)
    {
        mCompetencyList[index] = competency;
    }
}

/*************************************************************
* Function: insertCompetency(CompetencyMap)                  *
* Purpose: Insert a new competency                           *
* Pre-condition: Valid competency                            *
* Post-condition: The competency is added if code is unique  *
* Author: [Your Name]                                        *
**************************************************************/
void Competency::insertCompetency(CompetencyMap competency)
{
    // Check if code already exists
    if (isExist(competency.mCode))
    {
        cout << "Error: Competency code " << competency.mCode << " already exists!" << endl;
        return;
    }

    // Create new temp array with increased size
    CompetencyMap* tempList = new CompetencyMap[mCompetencyCount + 1];

    // Copy existing data
    for (int i = 0; i < mCompetencyCount; i++)
    {
        tempList[i] = mCompetencyList[i];
    }

    // Add new competency
    tempList[mCompetencyCount] = competency;

    // Delete old array and update pointer
    if (mCompetencyList != NULL)
    {
        delete[] mCompetencyList;
    }

    mCompetencyList = tempList;
    mCompetencyCount++;
}

/*************************************************************
* Function: isExist(string)                                  *
* Purpose: Check if a competency code exists                 *
* Pre-condition: Valid competency code                       *
* Post-condition: Returns true if code exists, false if not  *
* Author: [Your Name]                                        *
**************************************************************/
bool Competency::isExist(string competencyCode)
{
    for (int i = 0; i < mCompetencyCount; i++)
    {
        if (mCompetencyList[i].mCode == competencyCode)
        {
            return true;
        }
    }
    return false;
}

/*************************************************************
* Function: removeCompetency(string)                         *
* Purpose: Remove a competency by code                       *
* Pre-condition: Valid competency code                       *
* Post-condition: The competency is removed if it exists     *
* Author: [Your Name]                                        *
**************************************************************/
void Competency::removeCompetency(string competencyCode)
{
    // Find the competency to remove
    int indexToRemove = -1;

    for (int i = 0; i < mCompetencyCount; i++)
    {
        if (mCompetencyList[i].mCode == competencyCode)
        {
            indexToRemove = i;
            break;
        }
    }

    // If competency not found, return
    if (indexToRemove == -1)
    {
        cout << "Error: Competency code " << competencyCode << " not found!" << endl;
        return;
    }

    // Create new array with decreased size
    CompetencyMap* tempList = NULL;

    if (mCompetencyCount > 1)
    {
        tempList = new CompetencyMap[mCompetencyCount - 1];

        // Copy elements before the removed one
        for (int i = 0; i < indexToRemove; i++)
        {
            tempList[i] = mCompetencyList[i];
        }

        // Copy elements after the removed one
        for (int i = indexToRemove + 1; i < mCompetencyCount; i++)
        {
            tempList[i - 1] = mCompetencyList[i];
        }
    }

    // Delete old array
    delete[] mCompetencyList;

    // Update pointer and count
    mCompetencyList = tempList;
    mCompetencyCount--;
}

/*************************************************************
* Function: updateCompetency(string, string)                 *
* Purpose: Update a competency code                          *
* Pre-condition: Valid original and new codes                *
* Post-condition: The competency code is updated if original *
*                 exists and new is unique                   *
* Author: [Your Name]                                        *
**************************************************************/
void Competency::updateCompetency(string oriCode, string newCode)
{
    // Check if original code exists
    bool oriExists = false;
    int oriIndex = -1;

    for (int i = 0; i < mCompetencyCount; i++)
    {
        if (mCompetencyList[i].mCode == oriCode)
        {
            oriExists = true;
            oriIndex = i;
            break;
        }
    }

    if (!oriExists)
    {
        cout << "Error: Original competency code " << oriCode << " not found!" << endl;
        return;
    }

    // Check if new code already exists (unless it's the same as original)
    if (oriCode != newCode && isExist(newCode))
    {
        cout << "Error: New competency code " << newCode << " already exists!" << endl;
        return;
    }

    // Update the code
    mCompetencyList[oriIndex].mCode = newCode;
}

/*************************************************************
* Function: operator>>                                       *
* Purpose: Read Competency data from console input           *
* Pre-condition: Valid istream object                        *
* Post-condition: Competency object is populated             *
* Author: [Your Name]                                        *
**************************************************************/
istream& operator>>(istream& input, Competency& obj)
{
    // First read the Course data
    input >> static_cast<Course&>(obj);

    cout << "Enter number of competencies: ";
    input >> obj.mCompetencyCount;

    // Delete existing array if needed
    if (obj.mCompetencyList != NULL)
    {
        delete[] obj.mCompetencyList;
        obj.mCompetencyList = NULL;
    }

    // Create new array if needed
    if (obj.mCompetencyCount > 0)
    {
        obj.mCompetencyList = new CompetencyMap[obj.mCompetencyCount];

        // Read each competency
        for (int i = 0; i < obj.mCompetencyCount; i++)
        {
            cout << "\nCompetency #" << (i + 1) << ":" << endl;
            input >> obj.mCompetencyList[i];
        }
    }

    return input;
}

/*************************************************************
* Function: operator<<                                       *
* Purpose: Display Competency data to console                *
* Pre-condition: Valid ostream object                        *
* Post-condition: Competency data is displayed               *
* Author: [Your Name]                                        *
**************************************************************/
ostream& operator<<(ostream& output, Competency obj)
{
    // First output the Course data
    output << static_cast<Course>(obj);

    output << "Number of Competencies: " << obj.mCompetencyCount << endl;

    // Output each competency
    for (int i = 0; i < obj.mCompetencyCount; i++)
    {
        output << "\nCompetency #" << (i + 1) << ":" << endl;
        output << obj.mCompetencyList[i];
    }

    return output;
}

/*************************************************************
* Function: operator>>                                       *
* Purpose: Read Competency data from file input              *
* Pre-condition: Valid ifstream object                       *
* Post-condition: Competency object is populated             *
* Author: [Your Name]                                        *
**************************************************************/
ifstream& operator>>(ifstream& input, Competency& obj)
{
    // First read the Course data
    input >> static_cast<Course&>(obj);

    // Read competency count
    input >> obj.mCompetencyCount;

    // Delete existing array if needed
    if (obj.mCompetencyList != NULL)
    {
        delete[] obj.mCompetencyList;
        obj.mCompetencyList = NULL;
    }

    // Create new array if needed
    if (obj.mCompetencyCount > 0)
    {
        obj.mCompetencyList = new CompetencyMap[obj.mCompetencyCount];

        // Read each competency
        for (int i = 0; i < obj.mCompetencyCount; i++)
        {
            input >> obj.mCompetencyList[i];
        }
    }

    return input;
}

/*************************************************************
* Function: operator<<                                       *
* Purpose: Write Competency data to file                     *
* Pre-condition: Valid ofstream object                       *
* Post-condition: Competency data is written to file         *
* Author: [Your Name]                                        *
**************************************************************/
ofstream& operator<<(ofstream& output, Competency obj)
{
    // First output the Course data
    output << static_cast<Course>(obj);

    // Output competency count
    output << obj.mCompetencyCount << endl;

    // Output each competency
    for (int i = 0; i < obj.mCompetencyCount; i++)
    {
        output << obj.mCompetencyList[i] << endl;
    }

    return output;
}

/*************************************************************
* Function: operator=                                        *
* Purpose: Assignment operator for Competency class          *
* Pre-condition: Valid Competency object on right side       *
* Post-condition: This object's data is replaced with rhs    *
* Author: [Your Name]                                        *
**************************************************************/
Competency Competency::operator=(Competency rhs)
{
    // Copy Course data
    this->Course::operator=(rhs);

    // Delete existing array if needed
    if (mCompetencyList != NULL)
    {
        delete[] mCompetencyList;
        mCompetencyList = NULL;
    }

    mCompetencyCount = rhs.mCompetencyCount;

    if (mCompetencyCount > 0)
    {
        // Create new array and copy data
        mCompetencyList = new CompetencyMap[mCompetencyCount];

        for (int i = 0; i < mCompetencyCount; i++)
        {
            mCompetencyList[i] = rhs.mCompetencyList[i];
        }
    }

    return *this;
}