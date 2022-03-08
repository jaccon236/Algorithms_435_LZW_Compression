COPYRIGHT (C) 2022 Jacen Conlan (jcc126) All rights reserved.
    Algorithms Project 2 - LZW Compression
    Author: Jacen Conlan (jcc126@uakron.edu)
    Version: 1.10 03.07.2022
    Purpose: This README covers the important things to know for Algorithms Project 2 - LZW Compression

Base LZW code can be found at: http://rosettacode.org/wiki/LZW_compression#C.2B.2B
Original project code provided by Dr. Duan for Algorithms 435 - Project 2.
    Comments above functions provide context for refactored code vs code written by the author for this project.

The code for this project can be found at: https://github.com/jaccon236/Algorithms_435_LZW_Compression

% Part 1 - lzw435
    Purpose:
        This program compresses *.txt files into *.lzw files and decompresses *.lzw files into *.txt files using an LZW Compression Algorithm with a static 12 bit binary code length.
            Compressed *.txt files will be appended with the *.lzw extension meaning their full extension is *.txt.lzw
            Decompressed *.lzw files will be stored as new *.txt files with the naming convention originalFileName(2).txt

    Compilation:
        To compile lzw435.cpp multiple files are required. This README assumes you have a C++ compiler installed and are able to utilize Makefiles. 
            If this project has been accessed via GitHub, you may skip to step 3.

     1) Put lzw435.cpp in the same directory as the files listed below. All of these files can be found via GitHub but should also have been submitted via zip files. 
        The files that are needed in conjunction with lzw435.cpp to compile the program are:
            header.h
            functions.h
            functions.cpp
            Makefile

     2) Using the Makefile provided with the code for this project, no modifications are necessary 
            You can create your own Makefile as long as you know how to do this properly if you would like to

     3) Once all required files are in the same directory, run the "make" command or it's equivalent on your system to build the project.
            No warnings or errors should appear.

     4) Assuming everything has been done correctly, multiple object and *.d files appear in the directory along with lzw435.exe.
            If they have not, verify that you have followed all of the steps correctly. If you are still having issues, email me any questions you may have.
            To remove these files from the directory when finished using the program, an OS specific clean command can be run
                1) If your OS is Linux based use: make clean
                2) If your OS is Windows based use: make cleanw

    Execution:
        Arguments: This program expects multiple arguments.
            1) The name of the program
            2) The 'mode' of the program
                c: compression mode
                e: expansion (decompression) mode
            3) The name of the file to be compressed or expanded
        
        Formatting: Replace filename with the name of the *.txt or *.lzw file. Make sure to include all file extensions.
            To compress a *.txt file: 
                ./lzw435.exe c filename.txt
            
            To expand or decompress a *.txt.lzw file:
                ./lzw435.exe e filename.txt.lzw

        Output: This program will output text to the console and to *.txt or *.lzw files.
            1) The console will show that it is either compressing or decompressing a file and the name of the file.
            2) If a file was compressed, filename.txt.lzw will be created or updated with the compressed file data.
            3) If a file was expanded (decompressed), filename(2).txt will be created or updated with the expanded file data.
            4) If incorrect formatting of arguments are provided, the program will terminate and prompt the user with their mistake.
            5) If the file name specified does not exist in the current directory, the program will terminate and prompt the user with their mistake.

% Part 2 - lzw435M
    Purpose:
        This program compresses *.txt files into *.lzw2 files and decompresses *.lzw2 files into *.txt files using an LZW Compression Algorithm with a variable 10 to 16 bit binary code length.
            Compressed *.txt files will be appended with the *.lzw2 extension meaning their full extension is *.txt.lzw2
            Decompressed *.lzw2 files will be stored as new *.txt files with the naming convention originalFileNameM(2).txt

    Compilation:
        To compile lzw435M.cpp multiple files are required. This README assumes you have a C++ compiler installed and are able to utilize Makefiles. 
            If this project has been accessed via GitHub, you may skip to step 3.

     1) Put lzw435M.cpp in the same directory as the files listed below. All of these files can be found via GitHub but should also have been submitted via zip files. 
        The files that are needed in conjunction with lzw435M.cpp to compile the program are:
            headerM.h
            functionsM.h
            functionsM.cpp
            Makefile

     2) Using the Makefile provided with the code for this project, no modifications are necessary 
            You can create your own Makefile as long as you know how to do this properly if you would like to

     3) Once all required files are in the same directory, run the "make" command or it's equivalent on your system to build the project.
            No warnings or errors should appear.

     4) Assuming everything has been done correctly, multiple object and *.d files appear in the directory along with lzw435M.exe.
            If they have not, verify that you have followed all of the steps correctly. If you are still having issues, email me any questions you may have.
            To remove these files from the directory when finished using the program, an OS specific clean command can be run
                1) If your OS is Linux based use: make clean
                2) If your OS is Windows based use: make cleanw

    Execution:
        Arguments: This program expects multiple arguments.
            1) The name of the program
            2) The 'mode' of the program
                c: compression mode
                e: expansion (decompression) mode
            3) The name of the file to be compressed or expanded
        
        Formatting: Replace filename with the name of the *.txt or *.lzw2 file. Make sure to include all file extensions.
            To compress a *.txt file: 
                ./lzw435M.exe c filename.txt
            
            To expand or decompress a *.txt.lzw2 file:
                ./lzw435M.exe e filename.txt.lzw2

        Output: This program will output text to the console and to *.txt or *.lzw2 files.
            1) The console will show that it is either compressing or decompressing a file and the name of the file.
            2) If a file was compressed, filename.txt.lzw2 will be created or updated with the compressed file data.
            3) If a file was expanded (decompressed), filenameM(2).txt will be created or updated with the expanded file data.
            4) If incorrect formatting of arguments are provided, the program will terminate and prompt the user with their mistake.
            5) If the file name specified does not exist in the current directory, the program will terminate and prompt the user with their mistake.

% END OF README %