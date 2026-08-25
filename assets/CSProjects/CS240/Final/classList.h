//  filename:  classList.h

/*
       Author:  Wei Kian Chen
  Modified by:
        Class: CSI-240-03
   Assignment: Final Project
Date Assigned: April 1, 2025
     Due Date: 13:00 EST April 25, 2025

Description:
   The linked list class is created to classes to schedule. However,
this is used for this project

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

#ifndef CLASS_LIST_H
#define CLASS_LIST_H

#include <iostream>
#include <string>
#include "classes.h"

using namespace std;

class ClassList
{
   struct Node
   {
      Classes mData;
      Node    *mNext;

      Node();
      Node(Classes data);
   };

private:
   Node *mHead, *mTail;
   int  mCount;

public:
   ClassList();
   ~ClassList();

   int     getCount();
   Classes getData(int index);

   void display();
   bool insert(Classes data);
   bool insertAtBack(Classes data);
   bool insertAtFront(Classes data);
   bool isEmpty();
   bool isExist(string courseCode);
   bool isSectionExist(string sectionCode);
   int  locate(string sectionCode);
   bool remove(string sectionCode);
   bool removeAtBack();
   bool removeAtFront();
};

#endif