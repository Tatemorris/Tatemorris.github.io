//  filename:  classList.h

/*
       Author:  Wei Kian Chen
  Modified by:
        Class: CSI-240-03
   Assignment: Final Project
Date Assigned: April 1, 2025
     Due Date: 13:00 EST April 25, 2025

Description:
   The class is created to store all the College's competenties in
a dynamic array within the class. The count records the number of College's
competencies and the dyanmic array stored all of them

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

#ifndef COLLEGE_COMPETENCIES_H
#define COLLEGE_COMPETENCIES_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "ccStruct.h"

using namespace std;

const string CCFILE = "competencies.txt";


class CollegeCompetencies
{
   private:
      int      mCount;
      CCStruct *mCompetencies;

   public:
      CollegeCompetencies();
      ~CollegeCompetencies();

      int      getCompetenciesCount();
      CCStruct getCompetencies(int index);

      void setCompetencies(int index, CCStruct competency);

      void display();
      void insert(CCStruct obj);
      bool isCodeExist(string code);
      bool isDescriptionExist(string description);
      void load();
      int  locate(string code);
      void remove(string code);
      void store();
};

#endif