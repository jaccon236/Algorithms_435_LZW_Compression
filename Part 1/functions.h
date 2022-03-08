/*
    COPYRIGHT (C) 2022 Jacen Conlan (jcc126) All rights reserved.

    "functions.h"
    Algorithms - Project 2 - LZW Encryption (Part 1)
    Author: Jacen Conlan (jcc126@uakron.edu)
    Version: 1.01 03.07.2022
    Purpose: function header file for Algorithms Project 2 (Part 1)
*/

// This code is derived in parts from LZW@RosettaCode for UA CS435

#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

#pragma once

#include "header.h"

// Function declarations

// Refactored versions of provided functions
string int2BinaryString(int, int);
int binaryString2Int(string);
void binaryIODemo(vector<int>);

// Extracted functions from binaryIODemo()
string readCompressedFile(string);
void writeCompressedFile(vector<int>, string, int);

// Functions written for this project
vector<int> separateCodes(const string&, int);
string readTextFile(string);

// Templated functions must be defined in the header file
// These functions are refactored versions of the provided code for the assignment
template <typename Iterator>
Iterator compress(const string &uncompressed, Iterator result) 
{
   // Necessary Variables
   string w, wc;
   char c;

   // Build the dictionary, start with 256.
   map<string, int> dictionary;
   int dictSize = 256;
   
   for (int i = 0; i < 256; i++)
   {
      dictionary[string(1, i)] = i;
   }

   for (string::const_iterator it = uncompressed.begin();
        it != uncompressed.end(); ++it) 
   {
      c = *it;
      wc = w + c;

      if (dictionary.count(wc))
      {
         w = wc;
      }

      else 
      {
         *result++ = dictionary[w];

         // Add wc to the dictionary. Assuming the max size is 4096!!!
         if (dictionary.size() < 4096)
         {
            dictionary[wc] = dictSize++;
         }
            
         w = string(1, c);
      }
   }
 
   // Output the code for w.
   if (!w.empty())
   {
      *result++ = dictionary[w];
   }
    
  return result;
}

// Decompress a list of output ks to a string.
// "begin" and "end" must form a valid range of ints
template <typename Iterator>
string decompress(Iterator begin, Iterator end) 
{
   // Build the dictionary.
   map<int, string> dictionary;
   int dictSize = 256;
   
   for (int i = 0; i < 256; i++)
   {
      dictionary[i] = string(1, i);
   }
      
   string w(1, *begin++);
   string result = w;
   string entry;

   // cout << "\ndecompressed: " << result <<";";
   
   for ( ; begin != end; begin++) 
   {
      int k = *begin;

      if (dictionary.count(k))
      {
         entry = dictionary[k];
      }
         
      else if (k == dictSize)
      {
         entry = w + w[0];
      }
         
      else
      {
         throw "Bad compressed k";
      }
         
      result += entry;

      // cout << "\ndecompressed: " << result <<";";
   
      // Add w+entry[0] to the dictionary.
      if (dictionary.size()<4096)
      {
         dictionary[dictSize++] = w + entry[0];
      }

      w = entry;
   }

   return result;
}

#endif // FUNCTIONS_H_INCLUDED

// END OF FILE //
