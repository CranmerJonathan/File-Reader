#include "cranmer_wordentry.h"
#include <iostream>
#include <string.h>

using std::string;

//constructor
WordEntry :: WordEntry()
{
  this->word = "";
  this->repetition = -99;
}

//constructor with parameter
WordEntry :: WordEntry(string input)
{
  this->word = input;
  this->repetition = 1;
}

//adds repetition
void WordEntry :: addRepetition()
{
  this->repetition++;
}

//get word
string WordEntry :: getWord()
{
  return this->word;
}

//get Repetition
int WordEntry ::  getRepetition()
{
  return this->repetition;
}

//override the == operator
bool operator == (const WordEntry word, const WordEntry word2)
{
  if((word.word).compare(word2.word) == 0)
    {
      return true;
    }
  else
    {
      return false;
    }
}

//override the > operator
bool operator > (const WordEntry word, const WordEntry word2)
{
  if((word.word).compare(word2.word) > 0)
    {
      return true;
    }
  else
    {
      return false;
    }
}

//override the < operator
bool operator < (const WordEntry word, const WordEntry word2)
{
  if((word.word).compare(word2.word) < 0)
    {
      return true;
    }
  else
    {
      return false;
    }
}
