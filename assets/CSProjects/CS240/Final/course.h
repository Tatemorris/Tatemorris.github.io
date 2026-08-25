//  filename:  course.h

/*
       Author:  Wei Kian Chen
  Modified by:
        Class: CSI-240-03
   Assignment: Final Project
Date Assigned: April 1, 2025
     Due Date: 13:00 EST April 25, 2025

Description:
   The class is created to store the basic information for a course.

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

#ifndef COURSE_H
#define COURSE_H

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Course
{
   protected:
      string mCode, mTitle, mMajor;   

   public:
      Course();
      Course(string code, string title, string major);
      Course(const Course &obj);
      
      string getCode();
      string getMajor();
      string getTitle();

      void setCode(string code);
      void setMajor(string major);
      void setTitle(string title);

      friend istream& operator>>(istream &input, Course &obj);
      friend ostream& operator<<(ostream& output, Course obj);
      friend ifstream& operator>>(ifstream& input, Course &obj);
      friend ofstream& operator<<(ofstream& output, Course obj);

      bool operator==(string rhs);
      bool operator==(Course rhs);
      friend bool operator==(string lhs, Course rhs);

      bool operator!=(string rhs);
      bool operator!=(Course rhs);
      friend bool operator!=(string lhs, Course rhs);

      bool operator<(string rhs);
      bool operator<(Course rhs);
      friend bool operator<(string lhs, Course rhs);

      bool operator<=(string rhs);
      bool operator<=(Course rhs);
      friend bool operator<=(string lhs, Course rhs);

      bool operator>(string rhs);
      bool operator>(Course rhs);
      friend bool operator>(string lhs, Course rhs);

      bool operator>=(string rhs);
      bool operator>=(Course rhs);
      friend bool operator>=(string lhs, Course rhs);
};

#endif