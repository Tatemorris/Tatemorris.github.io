//  filename:  classList.h

/*
       Author:  Wei Kian Chen
  Modified by:
        Class: CSI-240-03
   Assignment: Final Project
Date Assigned: April 1, 2025
     Due Date: 13:00 EST April 25, 2025

Description:
   The class is created to store all the College's competenties for
a class, and it is a child class of the Course class. It is
intented to be used with the CompetencyList class. The count records
the number of College's competencies and the dyanmic array stored 
all of them (the code and value pair).

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

#ifndef COMPETENCY_H
#define COMPETENCY_H

#include <iostream>
#include <fstream>
#include <string>
#include "course.h"
#include "competencyMap.h"
//#include "commonFunctions.h"

using namespace std;


class Competency : public Course
{
   private:
      int           mCompetencyCount;
      CompetencyMap *mCompetencyList;

   public:
      Competency();
      Competency(string code, string title, string major);
      Competency(const Competency &obj);
      ~Competency();

      int           getCompetencyCount();
      CompetencyMap getCompetency(int index);

      void setCompetency(int index, CompetencyMap competency);

      void insertCompetency(CompetencyMap competency);
      bool isExist(string competencyCode);
      void removeCompetency(string competencyCode);
      void updateCompetency(string oriCode, string newCode);

      friend istream& operator>>(istream &input, Competency &obj);
      friend ostream& operator<<(ostream &output, Competency obj);
      friend ifstream& operator>>(ifstream &input, Competency &obj);
      friend ofstream& operator<<(ofstream &output, Competency obj);

      Competency operator=(Competency rhs);
};

#endif