//  filename:  course.cpp

/*
       Author:  [Your Name]
        Class: CSI-240-03
   Assignment: Final Project
Date Assigned: April 1, 2025
     Due Date: 13:00 EST April 25, 2025

Description:
   Implementation of the Course class to store basic information for a course.

Certification of Authenticity:
   I certify that this is entirely my own work, except where I have
   given fully-documented references to the work of others.
*/

#include "course.h"

/*************************************************************
* Function: Course()                                         *
* Purpose: Default constructor for Course class              *
* Pre-condition: None                                        *
* Post-condition: A Course object is created with default    *
*                 values                                     *
* Author: [Your Name]                                        *
**************************************************************/
Course::Course()
{
    mCode = "";
    mTitle = "";
    mMajor = "";
}

/*************************************************************
* Function: Course(string, string, string)                   *
* Purpose: Parameterized constructor for Course class        *
* Pre-condition: Valid strings for parameters                *
* Post-condition: A Course object is created with given      *
*                 values                                     *
* Author: [Your Name]                                        *
**************************************************************/
Course::Course(string code, string title, string major)
{
    mCode = code;
    mTitle = title;
    mMajor = major;
}

/*************************************************************
* Function: Course(const Course&)                            *
* Purpose: Copy constructor for Course class                 *
* Pre-condition: Valid Course object to copy                 *
* Post-condition: A new Course object is created as a copy   *
* Author: [Your Name]                                        *
**************************************************************/
Course::Course(const Course& obj)
{
    mCode = obj.mCode;
    mTitle = obj.mTitle;
    mMajor = obj.mMajor;
}

// Getters
string Course::getCode()
{
    return mCode;
}

string Course::getMajor()
{
    return mMajor;
}

string Course::getTitle()
{
    return mTitle;
}

// Setters
void Course::setCode(string code)
{
    mCode = code;
}

void Course::setMajor(string major)
{
    mMajor = major;
}

void Course::setTitle(string title)
{
    mTitle = title;
}

// I/O operators
istream& operator>>(istream& input, Course& obj)
{
    cout << "Enter Course Code: ";
    getline(input >> ws, obj.mCode);

    cout << "Enter Course Title: ";
    getline(input, obj.mTitle);

    cout << "Enter Course Major(s): ";
    getline(input, obj.mMajor);

    return input;
}

ostream& operator<<(ostream& output, Course obj)
{
    output << "Course Code: " << obj.mCode << endl;
    output << "Course Title: " << obj.mTitle << endl;
    output << "Course Major(s): " << obj.mMajor << endl;

    return output;
}

ifstream& operator>>(ifstream& input, Course& obj)
{
    getline(input, obj.mCode);
    getline(input, obj.mTitle);
    getline(input, obj.mMajor);

    return input;
}

ofstream& operator<<(ofstream& output, Course obj)
{
    output << obj.mCode << endl;
    output << obj.mTitle << endl;
    output << obj.mMajor << endl;

    return output;
}

// Comparison operators
bool Course::operator==(string rhs)
{
    return mCode == rhs;
}

bool Course::operator==(Course rhs)
{
    return mCode == rhs.mCode;
}

bool operator==(string lhs, Course rhs)
{
    return lhs == rhs.mCode;
}

bool Course::operator!=(string rhs)
{
    return mCode != rhs;
}

bool Course::operator!=(Course rhs)
{
    return mCode != rhs.mCode;
}

bool operator!=(string lhs, Course rhs)
{
    return lhs != rhs.mCode;
}

bool Course::operator<(string rhs)
{
    return mCode < rhs;
}

bool Course::operator<(Course rhs)
{
    return mCode < rhs.mCode;
}

bool operator<(string lhs, Course rhs)
{
    return lhs < rhs.mCode;
}

bool Course::operator<=(string rhs)
{
    return mCode <= rhs;
}

bool Course::operator<=(Course rhs)
{
    return mCode <= rhs.mCode;
}

bool operator<=(string lhs, Course rhs)
{
    return lhs <= rhs.mCode;
}

bool Course::operator>(string rhs)
{
    return mCode > rhs;
}

bool Course::operator>(Course rhs)
{
    return mCode > rhs.mCode;
}

bool operator>(string lhs, Course rhs)
{
    return lhs > rhs.mCode;
}

bool Course::operator>=(string rhs)
{
    return mCode >= rhs;
}

bool Course::operator>=(Course rhs)
{
    return mCode >= rhs.mCode;
}

bool operator>=(string lhs, Course rhs)
{
    return lhs >= rhs.mCode;
}