//: Assignment1Question2.cpp

/* 
 Title: Assignment1Question2.cpp
 Description: Temperature conversion from user input
 Date: June 2, 2023
 Author: Joseph Bresee
 Version: 1.0
 Copyright: 2023 Joseph K. Bresee
 */

/*
 DOCUMENTATION
 
 Program Purpose:
 	User Input, conditions including chars
 Compile (assuming Cygwin is running): g++ -o Assignment1Question2 Assignment1Question2.cpp
 Execution (assuming Cygwin is running): ./Assignment1Question2
 
 Notes: in Cygwin, main must return type int
 
 Classes: none

 Variables:
 	temp - float - the input of the value of the temperature you want to convert
    unit - char - either f or c upper or lowercase, to specify what unit the temperature is given in
    ans - char - response to another conversion, should be y or n upper or lowercase (however could be other single letter responses)
    c - float - temperature passed to function converting celsius to fahrenheit
    f - float - temperature passed to function converting fahrenheit to celsius
*/

/*
 TEST PLAN
 
 Normal case 1:

 45
 F
 Y
 -12
 C
 N

 Normal case 2:
 0
 C
 Y
 0
 F
 N

 Bad Data case 1 (wrong type)
 temperature is 30 degrees
 
 Bad Data case 2 (too big of number)
100000000000000000000000000000
 
 Bad Data case 3 (wrong char input)
 7
 h
 h
 
 Bad case 4 (full string response):
 7
 Celsius **or** Fahrenheit

 Bad Data case 5 (different char response)
 7
 cy **or** fy
 7
 fy **or** cy


 Discussion:
    The program cannot take in char values as an int so the program runs incorrectly.
    When a value over the max value that an int can hold is given as input, the program runs incorrectly, the same as Bad case 1
    When a non c or f char is given (upper or lower), condition is not met and conversion is not calculated and printed.
    When a char is given a string it uses the first letter as input, and the second letter as the next input.
*/

#include <iostream>
using namespace std;

/*******************************************************************************************************************************/

float C_to_F(float c) //F = (C * 9 / 5) + 32 
{
    float temp = (c*9/5)+32;
 
    return temp;
}

float F_to_C(float f) //(F – 32 ) * 5 / 9
{
    float temp = (f-32)*5/9;
 
    return temp;
}

/*******************************************************************************************************************************/

int main()
{
    
    float temp; //temperature, which can have decimal place
    char unit; //measurement type (ferenheit or celcius//
    char ans;
    
    cout<<"This program converts Temperatures from Fahrenheit to Celsius and vice versa."<<endl;
    
    
    do
    {   
        cout<<"Please enter your temperature: ";
        cin>>temp; //input
    
        cout<<"Please enter the units (F/C): ";
        cin>>unit; //input
        
        
        if (unit=='C' || unit=='c') //both cases for celcius
        {
            float in_f = C_to_F(temp);
            cout<<"A temperature of "<<temp<<" degrees Celsius is equivalent to "<<in_f<<" degrees Fahrenheit."<<endl;
        }
        else if (unit=='F' || unit=='f') //both cases for fahrenheit
        {        
            float in_c = F_to_C(temp);
            cout<<"A temperature of "<<temp<<" degrees Fahrenheit is equivalent to "<<in_c<<" degrees Celsius."<<endl;  
        }
        
        cout<<"Do you want another conversion? (Y/N): ";
        cin>>ans; //input
        
        
    } while((ans=='Y' || ans=='y') && (ans!='N' || ans!='n'));  //the do while loop is used here because we do not need to ask the user if they want a conversion when they first run the program;
    //this would be futile, since we can tell the user already wants a conversion since they ran the program. 
    //Then, we ask if user wants another conversion. Another conversion will happen if the user enters a y or Y, and will end if the user enters a non-y or Y answer.


    cout<<"Thank you. Goodbye."<<endl;

    /*To strengthen this code, we can implement more exception handling. In real world programming, we want to be able to handle any sort of input a user gives, to prevent
     crashing and to increase ease of use. 
     We can:
     1. implement measures to handle non - c or C or f or F answers when asking for a unit of measurement
    we can do this by using if else statements and a continue statement within our do-while.

     2. implement measures to handle non - float type inputs for our temperature (and use edge cases like coldest and hottest temperatures possible)
     we can do this the same way as above.

     3. We can handle non y or Y or n or N by using another do-while, embedded within the main do-while. This do-while would run while the answer is not
     y or Y or n or N , and print an error statement. Then we can change our larger scope do-while condition to be only while
     y or Y is entered.
        */
        
    return 0;
}