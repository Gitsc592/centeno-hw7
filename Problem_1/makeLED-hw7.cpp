/** Simple On-board LED flashing program - written in C++ by Derek Molloy
*    simple functional struture for the Exploring BeagleBone book
*
*    This program uses USR LED 3 and can be executed in three ways:
*         makeLED on
*         makeLED off
*         makeLED flash  (flash at 100ms intervals - on 50ms/off 50ms)
*         makeLED status (get the trigger status)
*
* * Written by Derek Molloy for the book "Exploring BeagleBone: Tools and 
* Techniques for Building with Embedded Linux" by John Wiley & Sons, 2014
* ISBN 9781118935125. Please see the file README.md in the repository root 
* directory for copyright and GNU GPLv3 license information.            */

//////////////////////////////////////////////////////
// Filename: makeLED-hw7.cpp
// Editor : Sed Centeno
// Date : 10/21/2024
//
// Description:
// Creates new functionality which takes a new argument "blink N"
// and blinks the LED N times at a rate of 0.5 Hz
//
// New Argument:
// blink N(integer)
//
// Example Invocation:
// ./makeLED-hw7 blink 5
///////////////////////////////////////////////////////

#include<iostream>
#include<fstream>
#include<string>
#include<unistd.h>
using namespace std;

#define LED3_PATH "/sys/class/leds/beaglebone:green:usr3"
#define blinkDelayTime 1

void writeLED(string filename, string value){
   fstream fs;
   string path(LED3_PATH);
   fs.open((path + filename).c_str(), fstream::out);
   fs << value;
   fs.close();
}

void removeTrigger(){
  writeLED("/trigger", "none");
}

int main(int argc, char* argv[]){
   if(argc<2){ // Should now be < 2 because of new "blink N" argument.
	cout << "Usage is makeLED-hw7 and one of: " << endl;
        cout << "   on, off, flash, status or blink N" << endl;
	cout << " e.g. ./makeLED-hw7 blink 5" << endl;
        return 2;
   }
   string cmd(argv[1]);
   cout << "Starting the makeLED program" << endl;
   cout << "The current LED Path is: " << LED3_PATH << endl;

   // select whether command is on, off, flash or status
   if(cmd=="on"){
        cout << "Turning the LED on" << endl;
	removeTrigger();
        writeLED("/brightness", "1");
   }
   else if (cmd=="off"){
        cout << "Turning the LED off" << endl;
	removeTrigger();
        writeLED("/brightness", "0");
   }
   else if (cmd=="flash"){
        cout << "Flashing the LED" << endl;
        writeLED("/trigger", "timer");
        writeLED("/delay_on", "50");
        writeLED("/delay_off", "50");
   }
   else if (cmd=="status"){
	// display the current trigger details
        std::fstream fs;
	fs.open( LED3_PATH "/trigger", std::fstream::in);
	string line;
	while(getline(fs,line)) cout << line << endl;
	fs.close();
   }
   // New blink argument logic
   else if (cmd=="blink"){
    // Checks if N has been supplied.
    if (argc < 3){
      cout << "Please supply the amount of times you would like to blink";
      cout << endl;
      cout << "e.g: ./makeLED-hw7 blink 5" << endl;
      return 2;
    }
    
    // Convert string to integer for blink Amount
    int blinkAmount = stoi(argv[2], nullptr, 10);
    
    // While loop for turning LED on and off at 0.5 Hz
    removeTrigger();
    for (int i = 0; i < blinkAmount; i++){
      writeLED("/brightness", "1");
      sleep(blinkDelayTime);
      writeLED("/brightness", "0");
      sleep(blinkDelayTime);
    }
   }
   else{
	cout << "Invalid command!" << endl;
   }
   cout << "Finished the makeLED Program" << endl;
   return 0;
}
