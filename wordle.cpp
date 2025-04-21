#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
void wordHelp( string& inputPattern, int posNum, string floatingNum, const set<string>& dict, set<string>& words);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    // Declaration of results stored in set of words and an input string
    set<string> words;

    string inputPattern = in;
    // calls the recursive solution for the problem statement
    wordHelp(inputPattern,0,floating,dict,words);
     
    return words;

}

// Define any helper functions here
void wordHelp( string& inputPattern, int posNum, string floatingNum, const set<string>& dict, set<string>& words)
{

  // checks if the entire pattern is reached 
  if(posNum == (int)inputPattern.size())
  {
     //Checks if the floating characters are used and that the word exists in the dictionary
    if(floatingNum.empty() && dict.find(inputPattern) != dict.end())
    {
       // add it to set
      words.insert(inputPattern);
    }
    return;
  }


  // For loop for iterating through remaining spaces and keeping a count
  int spaces =0;
  for(size_t m = posNum; m < inputPattern.size(); m++)
  {
    if(inputPattern[m] == '-')
    {
      spaces++;
    }

  }

  // Checks if there are more floating characters than spaces
  if(floatingNum.size() > (size_t)spaces)
  {
    return;
  }
  
  // Checks if the current position already has character
  if(inputPattern[posNum] != '-')
  {
     // recrusively go to next position
    wordHelp(inputPattern, posNum+1, floatingNum, dict, words);
    return;
  }

  // for loop that iterates through and attempts to place each floating character , and go to the next position
  for(size_t n=0; n < floatingNum.size(); n++)
  {
   
   char float1 = floatingNum[n];
   inputPattern[posNum] = float1;
   // remove the current floating character from set
   string float2 = floatingNum;
   float2.erase(n,1);
   // Recursive call
   wordHelp(inputPattern, posNum + 1, float2, dict, words);

   inputPattern[posNum] = '-';
  }

  // Checks if there are more spaces than floating characters
  if((size_t)spaces > floatingNum.size())
  {
    // Loops through each letter of the alphabet
    for( char b = 'a'; b <='z'; b++)
    {
     bool isFloat = false;
     for( char c: floatingNum)
     {
       if (b == c)
       {
          isFloat = true;
          break;
       }
     }
     // checks if letters are not in floating set, and calls recursive function to fo to next psoition
     if(!isFloat)
     { 
        inputPattern[posNum]= b;
        wordHelp(inputPattern, posNum +1, floatingNum, dict, words);
        inputPattern[posNum] = '-';
     }
    }
  }

}

