/*
    COPYRIGHT (C) 2022 Jacen Conlan (jcc126) All rights reserved.

    "lzw435M.cpp"
    Algorithms - Project 2 - LZW Encryption (Part 2)
    Author: Jacen Conlan (jcc126@uakron.edu)
    Version: 1.01 03.07.2022
    Purpose: main file for Algorithms Project 2 (Part 2)
*/

// This code is derived in parts from LZW@RosettaCode for UA CS435

#include "headerM.h"
#include "functionsM.h"

// Main function for Algorithms Project 2 (Part 1)
int main(int argc, char* argv[]) 
{
   // If no arguments are passed
   if (argc == 1 || (*argv[1] != 'c' && *argv[1] != 'e'))
   {
      cout << endl << "This program requires several specific arguments." << endl;
      cout << "Please see the README for more information." << endl << endl;
      exit(1);
   }
   
   string fileName = argv[2];
   vector<int> compressed;
   string decompressed;
   string fileData;
   
   switch (*argv[1])
   {
      case 'c':
      {
         cout << "Compressing the file: " << fileName << endl;
         fileData = readTextFile(fileName);
         compress(fileData, back_inserter(compressed));
         writeCompressedFile(compressed, fileName);
         break;
      }
         
      case 'e':
      {
         cout << "Decompressing the file: " << fileName << endl;
         fileData = readCompressedFile(fileName);
         compressed = separateCodes(fileData, 10);
         decompressed = decompress(compressed.begin(), compressed.end());
         
         string newFileName = fileName.substr(0, fileName.find(".txt"));
         ofstream outFile;
         outFile.open(newFileName += "M(2).txt");
         outFile << decompressed;
         outFile.close();
         break;
      }

      default:
         cout << "Uh how did that happen??";
   }

   return 0;
}

// END OF FILE //
