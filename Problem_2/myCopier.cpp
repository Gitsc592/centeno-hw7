////////////////////////////////////////////////////
// Filename: myCopier.cpp
// Author: Sed Centeno
// Date: 10/21/2024
//
// Description:
// This program copies the complete contents of one file and pastes it into
// another file.
//
// Arguments:
// input.txt output.txt
//
// Example Invocation:
// ./myCopier file1.txt file2.txt
/////////////////////////////////////////////////////

#include <iostream>
#include <fstream>
using namespace std;

int main(int argc, char *argv[]){
  // Check if proper arguments have been supplied.
  if (argc < 3){
    cout << "Invalid usage of the program, please supply proper arguments";
    cout << endl;
    cout << "e.g: ./myCopier file1.txt file2.txt" << endl; 
    return 2;
  }
  
  fstream input;
  fstream output;
  string line;

  // Open files
  input.open(argv[1], fstream::in);
  output.open(argv[2], fstream::out);
  
  // Get each line of input file and put into output file until EOF.
  while(!input.eof()){
    getline(input, line);

    // getline doesn't include newline, so I must append.
    // Also checks if at the end of the file so it doesn't add an extra newline
    // to the output.
    if (!input.eof()){
      output << line << endl;
    }else{
      output << line;
    }
  }

  // Close files
  input.close();
  output.close();
  
  return 0;
}
