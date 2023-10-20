//: Assignment1Question4.cpp

/* 
 Title: Assignment1Question4.cpp
 Description: Using switch-cases to make a cpp definition help program
 Date: June 3, 2023
 Author: Joseph Bresee
 Version: 1.0
 Copyright: 2023 Joseph K. Bresee
 */

/*
 DOCUMENTATION
 
 Program Purpose:
 	Looping, Formatting
 Compile (assuming Cygwin is running): g++ -o Assignment1Question4 Assignment1Question4.cpp
 Execution (assuming Cygwin is running): ./Assignment1Question4
 
 Notes: in Cygwin, main must return type int
 
 Classes: none

 Variables:
 def - string - placeholder for the string to be assigned to def depending on case
 choice - char - user input to hold what case the user chose
*/

/*
 TEST PLAN

 Normal case 1:
 5
 2
 3
 1
 4
 9
 one
 x

 Bad case 1 (giving choice a multi-digit response)
 5
 2
 3
 1
 4
 12
 14
 31
 x

 Discussion:
 If you give choice a multi-digit response, it only reads the first response; therefore '12' will be treated as '1'.
 Other than this, exception handling (by default) works fine.
 	
*/

#include <iostream>
#include <string>  //string header to simplify code: One print statement, and the rest is just writing definition. Makes code very easy to read.
using namespace std;

/*******************************************************************************************************************************/

int main() {
    char choice;  //choice is a char for the inclusion of x as a type of answer.
    string def;
    
    do 
    {
        cout << "C++ Help Menu" << endl;  //printing menu & options. It is important to include the number / input needed for each case you select.
        cout << "Select Help on:" << endl;
        cout << "1. If" << endl;
        cout << "2. Switch" << endl;
        cout << "3. For" << endl;
        cout << "4. While" << endl;
        cout << "5. Do-while" << endl;
        cout << "x. Exit" << endl << endl;
        //I used individual printing for each case to help with modularity. Maybe in the future I would want to edit this code and include more cases, 
        //or even edit some cases. This makes it easy to copy and paste more printing lines.
        cout << "Selection: ";
        cin >> choice;
        
        switch (choice) {
            case '1':
                def = "if: a conditional statement that houses a block of code, and only executes that block of code when condition is true.";
                break;
            case '2':
                def = "switch: a statement that tests a variable against a list of values. If the chosen variable is a choice, it runs that case's block of code. If variable is not a choice, program can default to an error message.";
                break;
            case '3':
                def = "for: a looping statement that checks a condition and then executes a block of code if condition is true. If false, loop breaks. This looping style is used when the number of iterations is known.";
                break;
            case '4':
                def = "while: a looping statement that repeatedly executes a block of statements while a particular condition is true. If false, loop breaks. This looping style is used when the number of iterations is unknown.";
                break;
            case '5':
                def = "do-while: a looping statement that repeatedly executes a block of statements while a particular condition is true. If false, loop breaks. This looping style is used when the number of iterations is unknown, and the user wants the block of code to execute once before condition is checked.";
                break;
                //For the sake of efficient coding, I decided to only define one string called 'def' that is assigned a different string for each case. It would require more memory and 
                //lines of code to declare a string for each # of case. All the case does is assign the appropriate definition to the def string.
            case 'x':
                cout << endl << "Thank you. Good bye." << endl <<endl;
            
                return 0;
                
            default:
                cout << "Invalid selection. Please try again." << endl;
                continue;
        }
        
        cout <<endl << def <<endl << endl; //Then here, at the end of the code, we print the def string.
        
    } while (choice != 'x'); //With this do while, we can keep asking the user for input on what decision they want to make (a definition or exit)
    //until they choose exit.

    /*
    default:
                    throw invalid_argument("Invalid selection. Please try again."); //we do not need a try since in this
                    //case our default is already kind of our try. This is not a very applicable place to use this type of error handling, since default will
                    //handle our errors, but this is for the sake of practice.
            }
            
            if (choice != 'x') {
                cout << endl << def << endl << endl;
            }
        } while (choice != 'x');
    } catch (const exception& e) {
        cerr << "Exception: " << e.what() << endl; //e.what() points to the error message I wrote above
        return 1; //returning 1 indicates that an error occured on the code.
    }
    
    return 0;
}

**I know this is not required for marks, but input on using this handling would rock!**
*/
    
    return 0;
}
