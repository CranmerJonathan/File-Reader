/*
Author: Jonathan Cranmer
Date: June 30rd, 2022
Description: This is the class that stores the string and its frequency
*/


#pragma once
#ifdef CRANMER_WORDENTRY_H
#define CRANMER_WORDENTRY_H

#endif
#include <string.h>
#include <iostream>
#include <cstring>

using std::string;


//class being delcared
class WordEntry
{
 public:
  //public methods
  WordEntry();
  WordEntry(string);
  virtual ~WordEntry() = default;
  void addRepetition();
  string getWord();
  int getRepetition();

 private:
  //private data
  int repetition;
  string word;

  //overriding the operators
  friend bool operator == (WordEntry, WordEntry);
  friend bool operator == (WordEntry, long int);
  friend bool operator > (WordEntry, WordEntry);
  friend bool operator < (WordEntry, WordEntry);
};

