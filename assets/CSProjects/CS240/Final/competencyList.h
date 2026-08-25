//  filename:  competencyList.h

/*
       Author:  Wei Kian Chen
  Modified by:
        Class: CSI-240-03
   Assignment: Final Project
Date Assigned: April 1, 2025
     Due Date: 13:00 EST April 25, 2025

Description:
   This is a linked list created for all the courses (with their 
competency map) we have in Champlain.

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

#ifndef COMPETENCY_LIST_H
#define COMPETENCY_LIST_H

#include <iostream>
#include <string>
#include "competencies.h"

using namespace std;

class CompetencyList
{
   struct Node
   {
      Competency mData;
      Node*      mNext;

      Node();
      Node(Competency data);
   };

   private:
      Node* mHead, * mTail;
      int  mCount;

   public:
      CompetencyList();
      ~CompetencyList();

      int        getCount();
      Competency getData(int index);

      void display();
      bool insert(Competency data);
      bool insertAtBack(Competency data);
      bool insertAtFront(Competency data);
      bool isEmpty();
      bool isExist(string courseCode);
      int  locate(string courseCode);
      bool remove(string courseCode);
      bool removeAtBack();
      bool removeAtFront();
      void removeCompetency(string competecyCode);
      void updateCompetency(string oriCode, string newCode);
};

#endif