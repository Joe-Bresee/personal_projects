//: Assignment1Question1.cpp

/* 
 Title: Assignment1Question1.cpp
 Description: Printing a multiplication table that goes up to the product 144
 Date: June 2, 2023
 Author: Joseph Bresee
 Version: 1.0
 Copyright: 2023 Joseph K. Bresee
 */

/*
 DOCUMENTATION
 
 Program Purpose:
 	Nested Looping, Formatting
 Compile (assuming Cygwin is running): g++ -o Assignment1Question1 Assignment1Question1.cpp
 Execution (assuming Cygwin is running): ./Assignment1Question1
 
 Notes: in Cygwin, main must return type int
 
 Classes: none

 Variables:
 	i - int - used as a counter for the first row loop as well as the outer loop for printing table
 	j - int - used as a counter for the inner loop for printing table
   prod - int - holds the value of i*j; is the value of the number to be displayed in its cell
   n - int - a parameter for the multiplication table printing function; determines the number that the table goes up to
   SIZE - int - a parameter for the multiplication table printing function; determines the width of each individual cell
*/

/*
 TEST PLAN
 
 Normal case:
    times_table(12, 4)

 Bad Data case 1 (n is less than 1)
    times_table(-3, 4)
 
 Bad Data case 2 (char passed into n & SIZE)
    times_table(t, w)

 
 Bad Data case 3 (n's max digits is larger than SIZE)
    times_table(100, 2)
    
 
 Bad Data case 4 (SIZE is less than 1)
    times_table(12, -5)

 Bad Data case 5 (n and SIZE are passed floating point numbers)
    times_table(12.8, 4.3)

 Discussion:
 	The program truncates floating point numbers; memory for ints is not big enough for decimals, so they always round down
 	When n is less than 1, the outer loop's condition is not met and the looping does not run
   When a char is passed into the function, compilation shows an error; the compiler thinks that the chars are variables
   When the digits of the times table reaches a larger value than SIZE, formatting fails, since the setw has no extra cushion
   When SIZE is less than 1, it appears that setw defaults to a width of 1
*/

#include <iostream>
#include <iomanip> //header for setw function

using namespace std;

void times_table(const int n, const int SIZE)  //n is how big u want ur table to be, SIZE is size of each product entry or cell.
{
    
    cout<<setw(SIZE)<<"     |"; //very top left cell
    for(int i=1; i<=n; i++) //loop for top row #s
    { 
       cout<<setw(SIZE)<<i<<" |";
    }
    cout<<endl;
    
    for (int i=1; i<=n; i++)  //column loop
    {
      cout<<setw(SIZE)<<i<<" |";
        
      for (int j=1; j<=n; j++)  //row loop
      {
          int prod = i*j;
          
          cout<<setw(SIZE)<<prod<<" |";
      }
      cout<< endl << endl;
    }
    
    return;
}

int main()
{
 
    times_table(12, 4);
    
}