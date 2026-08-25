/*
       Author: Tate
        Class: CSI-240-03
   Assignment: Final Project
Date Assigned: April 1, 2025
     Due Date: 13:00 EST April 25, 2025

Description:
   Implementation of the CompetencyMap struct to store a competency
   code and its value for a course.

Certification of Authenticity:
   I certify that this is entirely my own work, except where I have
   given fully-documented references to the work of others. I
   understand the definition and consequences of plagiarism and
   acknowledge that the assessor of this assignment may, for the
   purpose of assessing this assignment:
   - Reproduce this assignment and provide a copy to another member
     of academic staff; and/or
   - Communicate a copy of this assignment to a plagiarism checking
     service(which may then retain a copy of this assignment on its
    database for the purpose of future plagiarism checking)
*/

#include "competencyMap.h"

/*
Purpose: Default constructor for CompetencyMap struct
Pre-condition: None                                        
Post-condition: A CompetencyMap object is created with default values                             
*/
CompetencyMap::CompetencyMap()
{
    mCode = "";
    mValue = 0;
}

/*                            
Purpose: Read CompetencyMap data from console input        
Pre-condition: Valid istream object                        
Post-condition: CompetencyMap object is populated
*/
istream& operator>>(istream& input, CompetencyMap& obj)
{
    cout << "Enter Competency Code: ";
    input >> obj.mCode;

    cout << "Enter Competency Value (1-3): ";
    input >> obj.mValue;

    // Input validation for value
    while (obj.mValue < 1 || obj.mValue > 3)
    {
        cout << "Invalid value. Enter a value between 1 and 3: ";
        input >> obj.mValue;
    }

    return input;
}

/*************************************************************
* Function: operator>>                                       *
* Purpose: Read CompetencyMap data from file input           *
* Pre-condition: Valid ifstream object                       *
* Post-condition: CompetencyMap object is populated          *
* Author: [Your Name]                                        *
**************************************************************/
ifstream& operator>>(ifstream& input, CompetencyMap& obj)
{
    input >> obj.mCode >> obj.mValue;
    return input;
}

/*************************************************************
* Function: operator<<                                       *
* Purpose: Display CompetencyMap data to console             *
* Pre-condition: Valid ostream object                        *
* Post-condition: CompetencyMap data is displayed            *
* Author: [Your Name]                                        *
**************************************************************/
ostream& operator<<(ostream& output, CompetencyMap obj)
{
    output << "Competency Code: " << obj.mCode << endl;
    output << "Competency Value: " << obj.mValue << endl;
    return output;
}

/*************************************************************
* Function: operator<<                                       *
* Purpose: Write CompetencyMap data to file                  *
* Pre-condition: Valid ofstream object                       *
* Post-condition: CompetencyMap data is written to file      *
* Author: [Your Name]                                        *
**************************************************************/
ofstream& operator<<(ofstream& output, CompetencyMap obj)
{
    output << obj.mCode << " " << obj.mValue;
    return output;
}