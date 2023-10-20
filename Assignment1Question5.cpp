//: Assignment1Question5.cpp

/* 
 Title: Assignment1Question5.cpp
 Description: Printing all prime numbers from 1 to 10,000
 Date: June 7, 2023
 Author: Joseph Bresee
 Version: 1.0
 Copyright: 2023 Joseph K. Bresee
 */

/*
 DOCUMENTATION
 
 Program Purpose:
 	Looping, computational thinking
 Compile (assuming Cygwin is running): g++ -o Assignment1Question5 Assignment1Question5.cpp
 Execution (assuming Cygwin is running): ./Assignment1Question5
 
 Notes: in Cygwin, main must return type int
 
 Classes: none

 Variables:
 i - int - counter for loop from 1-10000
 j - int - counter for loop from 2 - i/2, checks factors of i
 is_prime - bool - used to say if a number is prime or not
*/

/*
 TEST PLAN
    My test plan is to look up all prime digits from 1-10000, and use a 
    file converter online to compare the list of prime numbers to the output of my program.
    If its a match, then the code works.

 Discussion:
 There is no input required for this function, so bad cases aren't really relevant. However, I have talked more about this program in my journal.
 	
*/

#include <iostream>
using namespace std;

/*******************************************************************************************************************************/

int main() {
    
     cout << "Prime numbers from 1 to 10000:" << endl;
    
    for(int i=2; i<=10000; i++) //for this loop we iterate every number from 2 to 10000, since I dont know how many spaces there are between each
    //prime number or a formula to calculate the distance between prime numbers.
    {   
        bool is_prime = true; //assume true then test until proven false.
        
          for(int j=2; j<=i/2; j++)  //j compared to i/2 since factor trees are the same once u get to the halfway mark. Since we are testing i against numbers 2 to i/2, we will never test i against one and i against itself; this is how we differentiate composite from prime.
          {
              if(i%j==0)
              {
                  is_prime = false;
                  break;
              }
          }
        if(is_prime)
        {
            cout <<i<<", "; //this block of code is only reached if i modulus j is not 0, so i only prints if it is prime. However, the loop does run
            //for every number between 2 and 10000. I can possibly change the run speed of this program if I know how to iterate only throuhg prime numbers.
    }
}
    
    return 0;
}
