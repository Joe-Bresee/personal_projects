//: Assignment1Question3.cpp

/* 
 Title: Assignment1Question3.cpp
 Description: Printing a temperature unit conversion table that goes from -40 to 455 degrees
 Date: June 3, 2023
 Author: Joseph Bresee
 Version: 1.0
 Copyright: 2023 Joseph K. Bresee
 */

/*
 DOCUMENTATION
 
 Program Purpose:
 	Looping, Formatting
 Compile (assuming Cygwin is running): g++ -o Assignment1Question3 Assignment1Question3.cpp
 Execution (assuming Cygwin is running): ./Assignment1Question3
 
 Notes: in Cygwin, main must return type int
 
 Classes: none

 Variables:
 c - float - temperature in celcius
 f - float - temperature in fahrenheit
 SIZE - const int - for setw (size for each cells)
 DEC - const int - for setting the precision
*/

/*
 TEST PLAN
 The plan is to run this code, copy the output, and paste it into a file comparison tool online to compare it to the example output
 given. Once they are identical, I know I have formatted correctly.

 Discussion:
 Using this test plan worked fine, but it did not tell me exactly what was wrong with the document; I had to manually highlight each table and compare the 
 amount of spaces to each, and eye-ball which spaces were uneven/different.
 	
*/

#include <iostream>
#include <iomanip> //header for setw function

using namespace std;

/*******************************************************************************************************************************/

float c_to_f(float c) //F = (C * 9 / 5) + 32
{
    float temp = (c*9/5)+32;
 
    return temp;
}

float f_to_c(float f) //(F – 32 ) * 5 / 9
{
    float temp = (f-32)*5/9;
 
    return temp;
}

//these are the same functions from the last question, which I copied and pasted. Another way I could have had these functions in this code is if I created a 
//library with these two conversion functions within it, and include the header for the library in this code.

/*******************************************************************************************************************************/

int main()
{
    const int SIZE = 10; // size of each cell.
    const int DEC = 3;  //precision
 
    cout <<"      Temperature      |      Temperature"<<endl;                     
    cout <<"       (degrees)       |       (degrees)"<<endl;                       
    cout <<"     F           C     |       C           F"<<endl;


    for (int i=0; i<100; i++) //looping for size of table
    {
        float f= -40.000 + (i * 5.000); //incrementation
        float c= f_to_c(f);  //conversion
        
        cout << fixed << setprecision(DEC) << setw(SIZE-1) << f << " " << setw(SIZE+1) << c << "  | ";  //before vertical bar
        
        c= -40.000 + (i * 5.000);  //incrementation
        f= c_to_f(c);  //conversion
        
         cout << fixed << setprecision(DEC) << setw(SIZE) << c << " " << setw(SIZE+1) << f << endl;  //after vertical bar
    }
    
    return 0;
}