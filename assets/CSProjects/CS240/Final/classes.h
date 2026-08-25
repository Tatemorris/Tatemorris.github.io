//  filename:  classes.h

/*
       Author:  Wei Kian Chen
  Modified by:
        Class: CSI-240-03
   Assignment: Final Project
Date Assigned: April 1, 2025
     Due Date: 13:00 EST April 25, 2025

Description:
   The class is created to classes to schedule, and it is child of
the Course class. However, this is used for this project

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

#ifndef CLASSES_H
#define CLASSES_H

#include <iostream>
#include <fstream>
#include <string>
#include "course.h"

using namespace std;

class Classes : public Course
{
   private:
      string mSection, mSemester;
      int    mStudentCount;

   public:
      Classes();
      Classes(string code, string title, string major, 
              string section, string semester,
              int studentCount);
      Classes(const Classes &obj);

      string getSection();
      string getSemester();
      int    getStudentCount();

      void setSection(string section);
      void setSemester(string semester);
      void setStudentCount(int count);

      friend istream& operator>>(istream& input, Classes &obj);
      friend ostream& operator<<(ostream& output, Classes obj);
      friend ifstream& operator>>(ifstream& input, Classes &obj);
      friend ofstream& operator<<(ofstream& output, Classes obj);
};

#endif