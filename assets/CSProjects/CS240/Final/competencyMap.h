//  filename:  competencyMap.h

/*
       Author:  Wei Kian Chen
  Modified by:
        Class: CSI-240-03
   Assignment: Final Project
Date Assigned: April 1, 2025
     Due Date: 13:00 EST April 25, 2025

Description:
   The struct is created to store all the College's competenty code
and its value for a course. This is intented to be use inside the
Competency class.

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

#ifndef COMPETENCY_MAP_H
#define COMPETENCY_MAP_H

#include <iostream>
#include <fstream>
#include <string>
#include "commonFunctions.h"

using namespace std;

struct CompetencyMap
{
   string mCode;
   int    mValue;

   CompetencyMap();
};

istream& operator>>(istream& input, CompetencyMap& obj);
ifstream& operator>>(ifstream& input, CompetencyMap& obj);
ostream& operator<<(ostream& output, CompetencyMap obj);
ofstream& operator<<(ofstream& output, CompetencyMap obj);

#endif