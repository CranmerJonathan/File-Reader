/*
Author: Jonathan Cranmer
Date: June 30rd, 2022
Description: Houses the main function and a few functions that help every go alright
*/


#include "cranmer_bst.hpp"
#include "cranmer_wordentry.h"

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <limits>
#include <cstring>
#include <cctype>
#include <stdio.h>
#include <string.h>

using std::cout;
using std::endl;
using std::string;
using std::ifstream;
using std::cin;
using std::numeric_limits;
using std::streamsize;
using std::ws;
using std::stringstream;
using std::ofstream;
using std::swap;

BST<WordEntry>* fileReader();
void promptUser();
string getFile();
int shouldQuit();
char getCharInput();
char yOrN();
void printTree(BST<WordEntry>*);
void printMostAndLeast(WordEntry*, int);
void promptUserFrequency(BST<WordEntry>*);
void writeToFile(WordEntry*, int);
WordEntry* frequencyQuickSort(WordEntry*, int, int);
int partition(WordEntry*, int, int);

//main function
int main(int argc, char** argv){
  BST<WordEntry>* tree = fileReader();
  
  if(tree->getRoot() == nullptr)
    {
      return 0;
    }
  else 
    {
      printTree(tree);
    }

  return 0;
}

//This guy gets the file name from the user and reads it and creates the tree from it
BST<WordEntry>* fileReader()
{
  int size;
  string filename = getFile(), line, word;

  ifstream input;

  BST<WordEntry>* tree = new BST<WordEntry>();

  WordEntry* entry;

  input.open(filename);

  //File name is cringe and lame
  while(!input.is_open())
    {
      if(shouldQuit())
	{
	  return tree;
	}
      else
	{
	  filename = getFile();
	  input.open(filename);
	}
    }

  //File name is pog and works
  while(getline(input, line, '\n'))
    {
      stringstream inputString(line);
      
      //ok so this is a lot but this is the meat of the function
      while(inputString)
	{
	  //inputstream is done break
	  if(!(inputString >> word))
	    {
	      break;
	    }
	  //creates tree and takes in input making it lower case and only letters
	  size = word.length();
	  char charArray[size + 1];
	  char* pointer;
	  strcpy(charArray, word.c_str());
	  for(int i = 0; i < size; i++)
	    {
	      charArray[i] = tolower(charArray[i]);
	    }
	  pointer = strtok(charArray, "~!@#$%^&*()_+`1234567890-={}|[]\\:\";'<>?,./");
	  //add to tree if pointer has a value and than take in new value rince and repeat
	  while(pointer != NULL)
	    {
	      word = string(pointer);
	      entry = new WordEntry(word);
	      if(tree->ElementExist(*entry))
		{
		  (tree->Find(*entry)->value).addRepetition();
		}
	      else 
		{
		  tree->Insert(*entry);
		}
	      entry = NULL;
	      pointer = strtok(NULL, "~!@#$%^&*()_+`1234567890-={}|[]\\:\";'<>?,./");
	    }
	}

    }

  //NO DATA LEAKS!!!!
  delete entry;
  input.close();
  return tree;
}

//get file name from user
string getFile()
{
  string filename;
  promptUser();
  cin >> filename;
  return filename;
}

//prompt user for file to read from
void promptUser()
{
  cout << "Please enter the name of the file that you would like to read from. ";
}

//ask user if should quit
int shouldQuit()
{
  char userInput;
  while(userInput != 'y' && userInput != 'n')
    {
      cout << "No such file exists" << endl << "Would you like to continue (y/n)? ";
      userInput = getCharInput();
    }
  if(userInput == 'y')
    {
      return 0;
    }
  else
    {
      return 1;
    }
}

//get char input from user
char getCharInput()
{
  char userInput;

  while(!(cin >> userInput))
    {
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      cout << "Incorrect Input. Please enter a character. ";
    }
  cin.clear();
  cin.ignore(numeric_limits<streamsize>::max(), '\n');

  return userInput;
}

//Prints out most least unique words and ask user if they want frequency of a word or to print to a file
void printTree(BST<WordEntry>* tree)
{
  int size;
  size = tree->Count();
  WordEntry* array;
  array = tree->ToArray();

  printMostAndLeast(array, size);

  promptUserFrequency(tree);
  writeToFile(array, size);

  delete[] array;
}

//prints 5 most common words 5 least common words and all the unique words
void printMostAndLeast(WordEntry* array, int size)
{
  int i;
  WordEntry number1, number2, number3, number4, number5;
  
  for(i = 0; i < size; i++)
    {
      if(number1.getRepetition() < array[i].getRepetition())
	{
	  number1 = array[i];
	}
      else if(number2.getRepetition() < array[i].getRepetition())
        {
          number2 = array[i];
        }
      else if(number3.getRepetition() < array[i].getRepetition())
        {
          number3 = array[i];
	}
      else if(number4.getRepetition() < array[i].getRepetition())
        {
          number4 = array[i];
	}
      else if(number5.getRepetition() < array[i].getRepetition())
        {
          number5 = array[i];
	}
    }
  
  cout << endl <<"Most common words: " << number1.getWord() << ", " << number2.getWord() << ", " << number3.getWord() << ", " << number4.getWord() << ", " << number5.getWord() << endl;

  cout << endl << "Unique words: ";

   for(i = 0; i < size; i++)
    {
      if(array[i].getRepetition() == 1)
	{
	  cout << array[i].getWord() << ", ";
	}
      else if(number1.getRepetition() > array[i].getRepetition() && array[i].getRepetition() != 0)
        {
          number1 = array[i];
        }
      else if(number2.getRepetition() > array[i].getRepetition() && array[i].getRepetition() != 0)
        {
          number2 = array[i];
	}
      else if(number3.getRepetition() > array[i].getRepetition() && array[i].getRepetition() != 0)
        {
          number3 = array[i];
	}
      else if(number4.getRepetition() > array[i].getRepetition() && array[i].getRepetition() != 0)
        {
          number4 = array[i];
	}
      else if(number5.getRepetition() > array[i].getRepetition() && array[1].getRepetition() != 0)
        {
          number5 = array[i];
	}
    }

  cout << endl;

  cout << endl << "Least common words: " << number1.getWord() << ", " << number2.getWord() << ", " << number3.getWord() << ", " << number4.getWord() << ", " << number5.getWord() << endl;
}

//asks user if they want to know the frequency of a word
void promptUserFrequency(BST<WordEntry>* tree)
{
  cout << endl << "Would you like to get the frequency of a word?(y/n) ";
  char prompt = getCharInput();
  while(prompt != 'y' && prompt != 'n')
    {
      cout << "Please enter y or n. ";
      prompt = getCharInput();
    }

  //if they want frequency get the frequency and ask again
  while(prompt == 'y')
    {
      string word;
      cout << "What word? ";
      cin >> word;
      WordEntry entry = WordEntry(word);
      //if element exist get frequency
      if(tree->ElementExist(entry))
	{
	  entry = (tree->Find(entry))->value;
	  cout << entry.getWord() << "'s Frequency is " << entry.getRepetition() << endl;
	}
      //if not tell them let em know
      else 
	{
	  cout << "Word is never used." << endl;
	}
      
      //reprompt user
      cout << "Would you like to get the frequency of another word?(y/n) ";
      char prompt = getCharInput();
      if(prompt == 'n')
	{
	  break;
	}
      while(prompt != 'y' && prompt != 'n')
	{
	  cout << "Please enter y or n. ";
	  prompt = getCharInput();
	}
    }
}

//write to file that user defines if they want to
void writeToFile(WordEntry* array, int size)
{
  //ask user for consent
  cout << endl << "Would you like to write to a file?(y/n) ";
  char prompt = getCharInput();
  int i;

  while(prompt != 'y' && prompt != 'n')
    {
      cout << "Please enter y or n. ";
      prompt = getCharInput();
    }
  if(prompt == 'n')
    {
      return;
    }
  //ask for name of file and how it is sorted
  else
    {
      prompt = 'f';
      cout << "It is sorted alphabetically." << endl 
	   << "Would you like to sort by frequency?(y/n) ";
      while(prompt != 'y' && prompt != 'n')
	{
	  cout << "Please enter y or n. ";
	  prompt = getCharInput();
	}
      if(prompt == 'y')
	{
	  frequencyQuickSort(array, 0, size - 1);
	}

      cout << "What is the name of the file? ";
      string name;
      cin >> name;
      ofstream myfile;
      myfile.open(name);
      
      //print file 
      if(!(myfile.is_open()))
	{
	  cout << "Unable to open file.";
	  return;
	}
      
      for(i = 0; i < size; i++)
	{
	  myfile << "Word: " << array[i].getWord() << ", " 
		 << "Frequency: " << array[i].getRepetition() << endl;
	}
      myfile.close();
    }
}

//organizes the array by frequency using quick sort
WordEntry* frequencyQuickSort(WordEntry* array, int start, int end)
{
  if (start >= end)
    {
      return array;
    }
 
  int p = partition(array, start, end);
 
  frequencyQuickSort(array, start, p - 1);
 
  frequencyQuickSort(array, p + 1, end);
}

//partitions array and helps the quicksort guy
int partition(WordEntry* array, int start, int end)
{
  int pivot = array[start].getRepetition();
 
  int count = 0;
  for (int i = start + 1; i <= end; i++) 
    {
      if (array[i].getRepetition() <= pivot)
	{
	  count++;
	}
    }

  int pivotIndex = start + count;
  swap(array[pivotIndex], array[start]);
 
  int i = start, j = end;
 
  while (i < pivotIndex && j > pivotIndex) {
 
    while (array[i].getRepetition() <= pivot) {
      i++;
    }
 
    while (array[j].getRepetition() > pivot) {
      j--;
    }
 
    if (i < pivotIndex && j > pivotIndex) {
      swap(array[i++], array[j--]);
    }
  }
 
  return pivotIndex;
}
