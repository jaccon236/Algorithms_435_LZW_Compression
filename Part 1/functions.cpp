/*
    COPYRIGHT (C) 2022 Jacen Conlan (jcc126) All rights reserved.

    "functions.cpp"
    Algorithms - Project 2 - LZW Encryption (Part 1)
    Author: Jacen Conlan (jcc126@uakron.edu)
    Version: 1.01 03.07.2022
    Purpose: functions file for Algorithms Project 2 (Part 1)
*/

// This code is derived in parts from LZW@RosettaCode for UA CS435

#include "functions.h"

// Convert an integer value to a binary string
// This function is refactored from the version provided in the assignment
string int2BinaryString(int c, int cl) 
{
      string p = ""; //a binary code string with code length = cl
      int code = c;

      while (c > 0) 
      {         
		   if (c % 2 == 0)
         {
            p = "0" + p;
         }
            
         else
         {
            p = "1" + p;
         }
            
         c = c >> 1;   
      }

      int zeros = cl-p.size();

      if (zeros<0) 
      {
         cout << "\nWarning: Overflow. code " << code <<" is too big to be coded by " << cl <<" bits!\n";
         p = p.substr(p.size() - cl);
      }

      else 
      {
         for (int i=0; i<zeros; i++)  //pad 0s to left of the binary code if needed
         {
            p = "0" + p;
         }
      }

      return p;
}

// Convert a binary string to an integer value
// This function is refactored from the version provided in the assignment
int binaryString2Int(string p) 
{
   int code = 0;

   if (p.size() > 0) 
   {
      if (p.at(0) == '1')
      {
         code = 1;
      }
         
      p = p.substr(1);
      while (p.size() > 0)
      { 
         code = code << 1; 

		   if (p.at(0) == '1')
         {
            code++;
         }
            
         p = p.substr(1);
      }
   }
   
   return code;
}

// Reads the data in from a compressed file
// This function is refactored and extracted from binaryIODemo() provided in the assignment
string readCompressedFile(string fileName)
{
   string zeros = "00000000";
   ifstream myfile2;
   myfile2.open (fileName.c_str(),  std::ios::binary);
   
   struct stat filestatus;
   stat(fileName.c_str(), &filestatus);
   long fsize = filestatus.st_size; //get the size of the file in bytes
   
   char c2[fsize];
   myfile2.read(c2, fsize);
   
   string s = "";
   long count = 0;

   while(count < fsize) 
   {
      unsigned char uc =  (unsigned char) c2[count];
      string p = ""; //a binary string

      for (int j = 0; j < 8 && uc > 0; j++) 
      {         
		   if (uc % 2 == 0)
         {
            p = "0" + p;
         }
            
         else
         {
            p = "1" + p;
         }
            
         uc = uc >> 1;   
      }

      p = zeros.substr(0, 8 - p.size()) + p; //pad 0s to left if needed
      s += p; 
      count++;
   } 
   myfile2.close();
   return s;
}

// Writes compressed data to a compressed .lzw file
// This function is refactored and extracted from binaryIODemo() provided in the assignment
void writeCompressedFile(vector<int> compressed, string fileName, int bits)
{
    string bcode= "";
    string p;

    for (vector<int>::iterator it = compressed.begin() ; it != compressed.end(); ++it) 
    {
        p = int2BinaryString(*it, bits);
        bcode += p;
    }

    if (fileName.find(".lzw") == string::npos)
    {
        fileName += ".lzw";
    }

    ofstream myfile;
    myfile.open(fileName.c_str(), std::ios::binary);
    
    string zeros = "00000000";
    if (bcode.size() % 8 != 0) //make sure the length of the binary string is a multiple of 8
    {
        bcode += zeros.substr(0, 8 - bcode.size() % 8);
    }
        
    for (int i = 0; i < int(bcode.size()); i += 8) 
    {
        int b = 1;
        for (int j = 0; j < 8; j++) 
        {
            b = b << 1;
            if (bcode.at(i + j) == '1')
            {
                b += 1;
            } 
        }

        char c = (char) (b & 255); //save the string byte by byte
        myfile.write(&c, 1);  
    }

    myfile.close();
}

// Separates the compressed data in a string into binary codes of the specified bit length
// Returns a vector of the binary codes as integers
vector<int> separateCodes(const string &fileData, int bits)
{
    string temp;
    vector<int> codes;

    // Iterate through the data in chunks of the specificed bit length
    for (int i = 0; i < int(fileData.size() / bits); i++)
    {
        // Set temp to an empty string
        temp = "";

        // Iterate through the chunk of data
        for (int j = 0; j < bits; j++)
        {
            // Append each bit to temp until temp is a chunk of the specified bit length
            temp += fileData.at((i * bits) + j);
        }

        // Convert temp to a binary integer and push it onto the vector
        codes.push_back(binaryString2Int(temp));
    }

    return codes;
}

// Basic function to read a text file and return the contexts of the file as a string
string readTextFile(string fileName)
{
    ifstream inFile;
    inFile.open(fileName);

    // If the file does not open or does not exist, exit the program
    if (!inFile)
    {
        cout << "The specified file could not be opened. Please try again." << endl;
        cout << "Please see the README for more information." << endl << endl;
        exit(1);
    }

    string data;
    string line;

    // Read the data of the file into a string one line at a time
    while (getline(inFile, line))
    {
        // Add a new line if there are still more lines of data
        if (!inFile.eof())
        {
            data += line + '\n';
        }

        // Do not add a new line if there are no more lines to read in
        else
        {
            data += line;
        }
        
    }

    inFile.close();
    return data;
}

// For the sake of clarity and consistency, binaryIODemo is included below in its refactored form
// Some unnecessary bits of this function have been removed to make the function less confusing
// This code is unused in this project as the necessary functions have been extracted above
void binaryIODemo(vector<int> compressed) 
{
    //example for integer c; looking for a 9 bit code
    int c = 69;
    int bits = 9; //length of the code
    string p = int2BinaryString(c, bits);
    cout << "c = " << c <<" : binary string = "<< p << "; back to code = " << binaryString2Int(p) << endl;
    
    // This section of the code was extracted for writeCompressedFile()
    string bcode= "";
    for (vector<int>::iterator it = compressed.begin() ; it != compressed.end(); ++it) 
    {
        //assuming 12 bits
        bits = 12;
        p = int2BinaryString(*it, bits);
        cout << "c = " << *it << " : binary string = " << p << "; back to code = " << binaryString2Int(p) << endl;
        bcode += p;
    }
    
    //writing to file 
    cout << "string 2 save : "<<bcode << endl;
    string fileName = "example435.lzw"; //this is for demo you should not hard code the final name.
    ofstream myfile;
    myfile.open(fileName.c_str(), std::ios::binary);
    
    std::string zeros = "00000000";
    if (bcode.size()%8!=0) //make sure the length of the binary string is a multiple of 8
    {
        bcode += zeros.substr(0, 8-bcode.size()%8);
    }
        
    int b; 
    for (int i = 0; i < int(bcode.size()); i+=8) 
    { 
        b = 1;
        for (int j = 0; j < 8; j++) 
        {
            b = b << 1;
            if (bcode.at(i + j) == '1')
            b += 1;
        }

        char c = (char) (b & 255); //save the string byte by byte
        myfile.write(&c, 1);  
    }

    myfile.close();

    // This section of the code was extracted for readCompressedFile()
    //reading from a file
    ifstream myfile2;
    myfile2.open (fileName.c_str(), std::ios::binary);
    
    struct stat filestatus;
    stat(fileName.c_str(), &filestatus);
    long fsize = filestatus.st_size; //get the size of the file in bytes
    
    char c2[fsize];
    myfile2.read(c2, fsize);
    
    string s = "";
    long count = 0;
    while(count<fsize) 
    {
        unsigned char uc =  (unsigned char) c2[count];
        string p = ""; //a binary string
        for (int j=0; j<8 && uc>0; j++) 
        {         
            if (uc % 2 == 0)
            {
                p = "0" + p;
            }
                
            else
            {
                p = "1" + p;
            }

            uc = uc >> 1;   
        }

        p = zeros.substr(0, 8-p.size()) + p; //pad 0s to left if needed
        s += p; 
        count++;
    }

    myfile2.close();
    cout << " saved string : "<< s << endl; 
}

// END OF FILE //
