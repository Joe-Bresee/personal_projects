//: Assignment4.cpp

/*
Title: Assignment4.cpp
Description: A text-based adventure style game based on Alice's Adventures in Wonderland
Date: June 21, 2023
Author: Joseph Bresee
Version: 1.0
Copyright: 2023 Joseph K. Bresee
*/

/*
DOCUMENTATION

Program Purpose: Demonstrate competency in combining cpp skills learned in past assignments and learning new  cpp skills to complete a fully functioning text-based game.

Compile (assuming Cygwin is running): g++ -o Assignment4 Assignment4.cpp
Execution (assuming Cygwin is running): ./Assignment4

Notes: In Cygwin, the main function must return type int.

Classes: None

Variables:

str - string - holds the word/ string being transformed tolower
c - unsigned char - current character being transformed tolower
NORTH, SOUTH, WEST, EAST - ENUM - holds/names the directions available to move in each location
sentence - const string& - the string passed to the function to be typewritten
delay - const int - the amount of time (milliseconds) slept between each character is displayed
letter - char - current letter within the sentence

name - string - stores the string of characters used for the name of the item, location, character, etc.
description - string - stores the string of characters used to describe the item, location, character, etc.
items - vector - vector of pointers to Items
filename - string - holds the name of a file being opened
line - string - current line obtained from getline(file, line)
separatorPos - size_t - stores the position of the separator, '|', in a string. Not used in this program, but for instances of classes, '|' separates things like name and description in a .txt.
inv_items - vector - vcector of Item*
collectibleCount - int - holds the number of collectibles in the inventory


*/
/*
TEST PLAN

Normal case:

Enter the name of a file that exists and contains text.
The program should display the contents of the file line by line, separated by periods.
The user must press '\n' to progress the line.

Bad Data case 1:

Enter the name of a non-existent file.
The program should display an error message indicating that the file could not be opened.
characters - vector - vector of Character*
connections - map - connects different locations to different directions (NSEW) to essentially buid a map of the game.
requiredPlayerSize - holds the needed playerSize to enter a location
currentLocation - location* - pointer to a instanced location to hold the location the player is currently in
locations - vector - vector of Location* stores all locations in the game
allCharacters - vector - vector of all characters in the game
inventory - Inventory - instanced inventory
playerSize - int - holds the value of the player's size, manipulated by using items. Small, smaller, normal, big, bigger
answer - string - user input of the answer for the riddle question
answered - boolean - holds bool of if the riddle has been answered or not
sequence - vector char - the needed sequence for the player to input to get through the maze
completed - boolean - holds if the maze has been completed or not
validSequence - boolean - holds if theuser has enter the correct sequence or not.
it1, it2 - const_iterator through vector of Item* - holds where the iteration of the function scanning though vectors of items ends (if it goes all the way through, the saught after item is not there)
hoops - vector of strings - holds the name of the hoops to go through
validInput - boolean - holds if the user entered valid input or not
directions - strong vector - names of the 'directions'
userDirection - string - user input
queenDirection - string - opposite of direction. what the player shoulkd enter
nextLocation - location* - pointer to a location that is the location connected by the enumeration (NESW) given by the player
itemChoice - string - the item the player chose to do an action with
locked - boolean - stores if a location's door (direction) is locked or not, and needs a key to be opened
userInput - string - action the user enters
choice - char - part of processing what the user entered for the action


Bad Data case 2:

Enter the name of a file with no contents.
Nothing will be displayed. Once the user presses enter, the program exits. 

Bad Data case 3:

Enter the name of a file that only contains periods.
The program will print each period every time the user presses enter.


Discussion:

The program reads the name of a file from the user and attempts to open it.
If the file is empty, nothing will be displayed, and once the user enters '\n', the program exits.
If the file cannot be opened, it displays an error message.
If the file is successfully opened, it reads the contents of the file line by line.
The program continues to display each line until the end of the file is reached or the user interrupts the program.
*/

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <chrono>
#include <thread>
#include <sstream>
#include <cctype>
#include <algorithm>
#include <map>

using namespace std;

string toLower(string str) {
    transform(str.begin(), str.end(), str.begin(), [](unsigned char c) {
        return tolower(c);
    });
    return str;
}

enum Direction {
    NORTH,
    SOUTH,
    EAST,
    WEST
};

void typewrite(const string& sentence) {
    const int delay = 20; //30

    for (char letter : sentence) {
        cout << letter << flush;
        this_thread::sleep_for(chrono::milliseconds(delay));
    } // i had a newline in here but it messed up some text down the line like <item> (newline) is not in your inventory 
}

void menu(){
    cout << "Command Menu:" << endl;
    cout << "n: Go north" << endl;
    cout << "e: Go east" << endl;
    cout << "s: Go south" << endl;
    cout << "w: Go west" << endl;
    cout << "l: Look around" << endl;
    cout << "t: Take an item (after pressing enter game will prompt you which item you want to take)" << endl;
    cout << "o: Observe an item" << endl;
    cout << "u: Use an item" << endl;
    cout << "i: Look at your inventory"<< endl;
    cout << "?: Show this menu" << endl;
    cout << "q: Quit the game (current game will not be saved)" << endl << endl;
}

class Item {
public:
    string name;
    string description;

    Item(const string& name, const string& description) : name(name), description(description) {}

    void inspect() {
        cout << description << endl;
    }

    vector<Item*> initializeItemsFromFile(const string& filename) {
        vector<Item*> items;
        ifstream file(filename);
        if (!file.is_open()) {
            // Handle file open error
            cout << "Error opening file: " << filename << std::endl;
            return items;
        }

        string line;
        while (getline(file, line)) {
            string name, description;
            size_t separatorPos = line.find('|');
            if (separatorPos != string::npos) {
                name = line.substr(0, separatorPos);
                description = line.substr(separatorPos + 1);
                items.push_back(new Item(name, description));
            }
        }

        file.close();
        return items;
    }

};

class Inventory {
public:
    vector<Item*> inv_items;
    int collectibleCount = 0;

    void addItem(Item* item) {
        inv_items.push_back(item);

        if (item->description.find("(collectible)") != string::npos) {
            collectibleCount++;
            cout << endl;
            typewrite("Collectible count: ");
            cout << endl;
            cout << collectibleCount << "/7" << endl << endl;
            }
        }

     void typewriteItems() const {
        if (inv_items.empty()) {
            typewrite("Your inventory is empty.");
            cout << endl;
        } else {
            typewrite("Items in your inventory:");
            cout << endl;
            for (const auto& item : inv_items) {
                cout << item->name << endl;
            }
        }
        cout << endl;
     }
};

class Character {
public:
    string name;
    string description;

    Character(const string& name, const string& description) : name(name), description(description) {}

    string speak(const string& sentence) {
        cout << name << ": '";
        for (char letter : sentence) {
            cout << letter << flush;
            this_thread::sleep_for(chrono::milliseconds(40));  //100
        }
        cout << "'" << endl << endl; // Add a couple new line after the sentence is spoken.
        return sentence; // Return the original sentence.
}

    vector<Character*> initializeCharactersFromFile(const string& filename) {
        vector<Character*> characters;
        ifstream file(filename);
        if (!file.is_open()) {
            // Handle file open error
            cout << "Error opening file: " << filename << endl;
            return characters;
        }

        string line;
        while (getline(file, line)) {
            string name, description;
            size_t separatorPos = line.find('|');
            if (separatorPos != string::npos) {
                name = line.substr(0, separatorPos);
                description = line.substr(separatorPos + 1);
                characters.push_back(new Character(name, description));
            }
        }

        file.close();
        return characters;
    }
};

class Location {
public:
    string name;
    string description;
    vector<Item*> items;
    vector<Character*> characters;
    map<Direction, Location*> connections;
    int requiredPlayerSize;
    bool locked = false;
    bool comeBack = false;

public:
    Location(const string& name, const string& description, int requiredSize) : name(name), description(description) {
        requiredPlayerSize = requiredSize;
    }

    void addItem(Item* item) {
        items.push_back(item);
    }

    void addCharacter(Character* character) {
        characters.push_back(character);
    }

    void addConnection(Direction direction, Location* connection) {
        connections[direction] = connection;
    }

    int getRequiredPlayerSize() const {
    return requiredPlayerSize;
    }

    void look() {
        typewrite(name);
        cout << endl;
        cout << description << endl << endl; 

       if(!items.empty()){
        typewrite("You see the following item(s) around you: ");
        cout << endl;
        for (const auto& item : items) {
            cout << item->name << endl;
        }
        cout << endl;
        }

        if (!characters.empty()) {
        typewrite("You see the following character(s) around you: ");
        cout << endl;
        for (const auto& character : characters) {
            cout << character->name << endl;
        }
        cout << endl;
        }
        typewrite("You see the following door(s) around you: ");
        cout << endl;
        for (const auto& entry : connections) {
            Direction direction = entry.first;
            Location* connectedLocation = entry.second;
            string directionStr;

            switch (direction) {
                case NORTH:
                    directionStr = "north";
                    break;
                case SOUTH:
                    directionStr = "south";
                    break;
                case EAST:
                    directionStr = "east";
                    break;
                case WEST:
                    directionStr = "west";
                    break;
            }

            cout << "Door to " << directionStr << ": " << connectedLocation->name << endl;
        }
        cout << endl;
    }
    vector<Location*> initializeLocationsFromFile(const string& filename) {
    vector<Location*> locations;
    ifstream file(filename);
    if (!file.is_open()) {
        // Handle file open error
        cout << "Error opening file: " << filename << endl;
        return locations;
    }

    string line;
    while (getline(file, line)) {
        string name, description;
        int height = 0;
        size_t separatorPos = line.find('|');
        if (separatorPos != string::npos) {
            name = line.substr(0, separatorPos);
            size_t separatorPos2 = line.find('|', separatorPos + 1);
            if (separatorPos2 != string::npos) {
                description = line.substr(separatorPos + 1, separatorPos2 - separatorPos - 1);
                height = stoi(line.substr(separatorPos2 + 1));
                locations.push_back(new Location(name, description, height));
            }
        }
    }

    file.close();
    return locations;
}

};

class Game {
private:
    Location* currentLocation;
    vector<Location*> locations;
    vector<Character*> allCharacters;
    Inventory inventory; //vectors to store items in inventory, locations, and characters. Helps with deleting too.

    int playerSize = 0; //0 is normal size

        Character* queen;   //declaration here due to scoping issues in useitem()
    Character* self;
    Character* caterpillar;
    Character* cards;
    Character* cat;
    Character* rabbit;
    Character* mouse;
    Location* mushroom;
    Location* home;
    Item* pocketWatch = new Item("pocketwatch", "A golden-cased, white dialed pocket watch. It must have fallen out of the White Rabbit's waistcoat pocket (collectible).");
    Item* leftmushroom = new Item("left_mushroom", "A small piece of mushroom torn from the left side of the Caterpillar's round mushroom.");
    Item* rightmushroom = new Item("right_mushroom", "A small piece of mushroom torn from the right side of the Caterpillar's round mushroom.");
    Item* gloves = new Item("gloves", "A pair of white kid gloves meant for the Duchess. Perhaps they slipped off her hands as she was dancing through the garden (collectible)");
    Item* woodenkey = new Item("wooden_key", "A key carved out of wood, found in a tree. Perhaps it fits into a wooden lock.");
    Item* crown = new Item("crown", "A golden, sparkly crown, worn by the ruler of Wonderland. Bedazzled with rubies, diamonds, and emeralds.");
    Item* rubykey = new Item("ruby_key", "A magnificent solid ruby key. Shines with a blood-red colour with the right lighting. Found in the middle of the wood, in a little box in maze 2. Perhaps it fits into an equally blood-red keyhole.");




public:

    function<bool(const Item*, const string&)> findItemByName = [&](const Item* item, const string& itemName) -> bool {
            return item->name == itemName;
    };
    vector<Item*>::const_iterator findItem(const vector<Item*>& items, const string& itemName) {
    return find_if(items.begin(), items.end(), [&](const Item* item) {
        return item->name == itemName;
    });
    }


    void homeEvent(){
        currentLocation->comeBack = true;
            rabbit->speak("Oh dear! Oh dear! I shall be late!");
            typewrite("The rabbit took a watch out of its waistcoat-pocket, looked at it, put it back, and then hurried on, not noticing it fell out of his pocket. You see the rabbit jump down a rabbit hole towards the north.");
            cout << endl << endl;
            currentLocation->addItem(pocketWatch);
    }
    void rabbitholeEvent(){
        currentLocation->comeBack = true;
        typewrite("Either the well was very deep, or you fell very slowly, for you have plenty of time as you go down to look about and wonder what was going to happen next. First, you try to look down and make out what you were coming to, but it was too dark to see anything; next you look at the sides of the well, and noticed that they were filled with cupboards and book-shelves; here and there you see maps and pictures hung upon pegs. On one shelf, you see a jar labelled, 'ORANGE MARMALADE', and a scrumptious-looking tart.");
        cout << endl << endl;
        this_thread::sleep_for(chrono::milliseconds(1111));
        typewrite("Down, down, down. Would the fall never come to an end?");
        cout << endl << endl;
        
        for (int i = 0; i < 5; i++)
        {
            typewrite("down");
            cout << endl;
            this_thread::sleep_for(chrono::milliseconds(1111));
        }

        self->speak("I wonder how many miles I've fallen by this time?");
        
        for (int i = 0; i < 5; i++)
        {
            typewrite("down");
            cout << endl;
            this_thread::sleep_for(chrono::milliseconds(1111));
        }

        typewrite("You keep falling (advance game by going north).");
        cout << endl;
    }
    void hallEvent(){
        typewrite("On the glass table you notice a tiny shimmering golden key sitting next to a bottle of some sort of liquid. Looking under the table you notice a tiny little cake.");
        cout << endl << endl;
        currentLocation->comeBack = true;
    }
    void mushroomEvent(){
                caterpillar->speak("Who are you?");
                self->speak("I—I hardly know, sir, just at present—at least I know who I was when I got up this morning, but I think I must have been changed several times since then.");
                caterpillar->speak("What do you mean by that?! Explain yourself!");
                self->speak("I can't explain myself sir, because I'm not myself, you see.");
                caterpillar->speak("How so?");
                self->speak("I don't keep the same size for ten minutes together!");
                caterpillar->speak("Sounds like you ... need some help");
                typewrite("The caterpillar inhales smoke from his hookah, and holds it in his longs for a brief moment before expelling it into the air.");
                cout << endl << endl;
                caterpillar->speak("There are two things I can do for you. The first being, a little piece of advice. I sense you will cross paths with the Queen of Hearts sometime in the future. Remember, she will lie; often the opposite of what she says is the truth.");
                
                typewrite("You wait patiently for your second piece of help. After a minute or two the Caterpillar took the hookah out of its mouth and yawned once or twice, and shook itself. Then it got down off the mushroom, and crawled away in the grass, merely remarking as it went,");
                cout << endl;
                caterpillar->speak("Secondly, one side will make you grow taller, and the other side will make you grow shorter. Of the mushroom, that is.");

                currentLocation->addItem(leftmushroom);
                currentLocation->addItem(rightmushroom);
                currentLocation->comeBack = true;
    }
    void gardenEvent(){
        typewrite("After a time you hear a little pattering of feet in the distance, and you hastily dried your eyes to see what was coming. It was the White Rabbit returning, splendidly dressed, with a pair of white kid gloves in one hand: he came trotting along in a great hurry, muttering to himself as he came,");
        cout << endl << endl;
        rabbit->speak("Oh! the Duchess, the Duchess! Oh! won't she be savage if I've kept her waiting!");
        self->speak("If you please, sir—");
        typewrite("The Rabbit started violently, dropped the white kid gloves, and skurried away into the darkness as hard as he could go.");
        cout << endl << endl;
        currentLocation->addItem(gloves);
        this_thread::sleep_for(chrono::milliseconds(3333));
        typewrite("A small grey speck scurries in the grass");
        cout << endl << endl;
        self->speak("What was that!?");
        this_thread::sleep_for(chrono::milliseconds(2222));
        typewrite("A tiny tail snakes past your ankle, causing a tickling sensation");
        cout << endl << endl;
        this_thread::sleep_for(chrono::milliseconds(1111));
        typewrite("The creature reveals itself:");
        cout << endl << endl;
        cout << "“Fury said to a\n"
        "     mouse, That he\n"
        "    met in the\n"
        "   house,\n"
        " 'Let us\n"
        "  both go to\n"
        "   law: I will\n"
        "    prosecute\n"
        "     you.—Come,\n"
        "       I'll take no\n"
        "       denial; We\n"
        "      must have a\n"
        "    trial: For\n"
        "  really this\n"
        " morning I've\n"
        "nothing\n"
        "to do.'\n"
        "  Said the\n"
        "  mouse to the\n"
        "   cur, 'Such\n"
        "    a trial,\n"
        "     dear sir,\n"
        "        With\n"
        "      no jury\n"
        "    or judge,\n"
        "   would be\n"
        "  wasting\n"
        "  our\n"
        "  breath.'\n"
        "    'I'll be\n"
        "    judge, I'll\n"
        "     be jury,'\n"
        "         Said\n"
        "     cunning\n"
        "      old Fury:\n"
        "      'I'll\n"
        "      try the\n"
        "        whole\n"
        "        cause,\n"
        "          and\n"
        "       condemn\n"
        "       you\n"
        "      to\n"
        "       death.’”\n";
        typewrite("And as quickly as the mouse appeared, it had scuttled away.");
        cout << endl << endl;
        self->speak("Strange.");
        currentLocation->comeBack = true;
    }
    void treeEvent(){
        typewrite("Suddenly, a mischevious grin materializes out of thin air. It floats about for a moment before stopping over a bough on the tree.");
        cout << endl << endl;
        self->speak("Oh! Who are you?");
        cat->speak(" I am the Cheshire Cat, of course. And who might you be?");
        self->speak("I'm not sure at the moment but - pleased to meet you, Mr. Cheshire Cat. But I must say, you look rather peculiar with that grin.");
        cat->speak("Well I am the epitome of peculiar. And curious, as well. ");
        cat->speak("I bet you are trying to continue through the Hedge Maze. However, without the wooden key, you will never get past me and this tree.");
        self->speak("Oh.");
        cat->speak("I can help you but to help you, I need your trust. For your trust, you must answer my three riddles.");

        string answer;
        bool answered = false;

        //first riddle
        while (!answered) {
            cat->speak("I make two people out of one. What am I?");
            cin >> answer;
            answer = toLower(answer);
            cout << endl;
            if (answer == "hint") {
                cat->speak("One of the people may be yourself, and the other may be your reflection.");
                } else if (answer == "mirror" || answer == "a mirror") {
                cat->speak("Correct.");
                answered = true;
                } else {
                cat->speak("Incorrect. Try again or ask for a hint (enter 'hint' for a hint).");
                }
            }
                answer = "";
                answered = false;
            //second riddle
            while (!answered) {
            cat->speak(" Second riddle: I am white when I am dirty, and black when I am clean. What am I?");
            cin >> answer;
            answer = toLower(answer);
            cout << endl;

            if (answer == "hint") {
                cat->speak("Your teacher may use it to write lessons on.");
                } else if (answer == "blackboard" || answer == "a blackboard") {
                cat->speak("Correct.");
                answered = true;
                } else {
                cat->speak("Incorrect. Try again or ask for a hint (enter 'hint' for a hint).");
                }
            }
                answer = "";
                answered = false;

            //third riddle
            while (!answered) {
            cat->speak(" Third and final riddle: You have me today, Tomorrow you'll have more; As your time passes, I'm not easy to store; I don't take up space, But I'm only in one place; I am what you saw, But not what you see. What am I?");
            cin >> answer;
            answer = toLower(answer);
            cout << endl;

            if (answer == "hint") {
                cat->speak("I know you can get this one, you just have to ... remember.");
                } else if (answer == "memory" || answer == "a memory" || answer == "memories") {
                cat->speak("Correct.");
                answered = true;
                } else {
                cat->speak("Incorrect. Try again or ask for a hint (enter 'hint' for a hint).");
                }
            }
            cat->speak("Well done. Now I trust you, as you trust me. For you I shall leave the wooden key");
            typewrite("The Cheshire Cat started warping and fading, but stayed floating about the tree.");
            cout << endl << endl;
            currentLocation->addItem(woodenkey);
            currentLocation->addItem(rubykey);
            currentLocation->comeBack = true;
    }
    void mazeEvent(){
        typewrite("You find yourself at the beginning of a shapeshifting labrynth, unsure of whether to go, north east south or west. ");
        cout << endl << "Navigate through the maze using 'n', 'e', 's', and 'w'. If you make a wrong turn, you might just end up right where you started." << endl << endl;

         vector<char> sequence;

         if(currentLocation->name == "Hedge Maze"){
            sequence = {'n', 'e', 's', 'w', 'n', 'w', 'e', 's'};
         } else if(currentLocation->name == "Hedge Maze (pt.2)"){
            sequence = {'e', 'e', 'w', 's', 'w', 'n', 'e'};
         }

    bool completed = false;

    while (!completed) {

        vector<char> Input;
        char input;
        bool validSequence = true;  

        for (int i = 0; i < sequence.size(); ++i) {
            cin >> input;
            Input.push_back(input);

        =
            if (Input[i] != sequence[i]) {
                validSequence = false;  
                break;
            }
        }

        // Display the result
        if (validSequence) {
            cout << "You find yourself at a clearing in the maze; you realize you have made it through." << endl;
            completed = true;  
        } else {
            cout << "You hear a woody creak sound behind you and turn around. The Hedges shifted and you are now at the start again." << endl;
        }
    }

    }
    void croquetgroundEvent(){
        vector<Item*>::const_iterator it1 = findItem(currentLocation->items, "flamingo");
        vector<Item*>::const_iterator it2 = findItem(inventory.inv_items, "hedgehog");
                
        if (it1 != inventory.inv_items.end() && it2 != inventory.inv_items.end()) {
           queen->speak("Ah, Alice, you have finally decided to join us for a game of croquet. Excellent! Have you got your hedgehog and flamingo?");
           self->speak("N-no, you majesty");
           queen->speak("Dear, how do you suppose you could play croquet, WITHOUT YOUR FLAMINGO, AND YOUR HEDGEHOG?");
           self->speak("Im so sorry Miss - Your Majesty - My Queen - I will come back again when I do. My apologies");
           typewrite("You leave the croquet ground.");
           cout << endl << endl;
           move(WEST);
        }

        queen->speak("Ah, Alice, you have finally decided to join us for a game of croquet. Excellent! Have you got you hedgehog and flamingo?");
        self->speak("Yes, your majesty, I do.");
        queen->speak("Wonderful! Have you ever played this magnificent game?");
        self->speak("Well, Your Majesty, I must admit that I haven't played this version of croquet before. It seems quite unusual.");
        queen->speak("Unusual? Nonsense! This is the finest game of croquet you will ever play. Flamingos make great mallets you know - and hedgehogs for balls.");
        queen->speak("All you have to do, is simply hit the hedgehog through the hoops to win.");
        self->speak("Are there any rules?");
        typewrite("The Queen of Heart scoffed.");
        cout << endl << endl;
        queen->speak("Rules? Ha! We don't need those. I'll just win in the end anyways.");
        self->speak("What about the cards? Are they gonna play too?");
        queen->speak("Oh, those little things? They are just here for show. They repeat whatever I say; it's quite amusing, you know. (Turns to the cards) Isn't that right?");
        cards->speak("Yes, Your Majesty! Whatever you say!");
        self->speak("Alright. I'll give it a try.");
        queen ->speak("Simply do EXACTLY AS I SAY. Let us begin.");
        
        
        vector<string> hoops = {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh"};
        vector<string> directions = {"good", "longitudinal", "inward", "sweetly", "wet", "softly", "sadly"};

            for (int i = 0; i < 7; ++i) {
                cout << hoops[i] << " hoops. " << endl;
                queen->speak("Hit the hedgehog " + directions[i] + ".");

                string userDirection;
                bool validInput = false;
                while (!validInput) {
                    typewrite("Enter your shot direction: ");
                    cin >> userDirection;

                    if (userDirection == "latitudinal" || userDirection == "bad" || userDirection == "outward" || userDirection == "sourly" || userDirection == "dry" || userDirection == "hardly" || userDirection == "happily") {
                        validInput = true;
                    } else {
                        typewrite("Wrong direction. Try again.");
                        cout << endl << endl;
                    }
                }

                string queenDirection;
                if (directions[i] == "longitudinal") queenDirection = "latitudinal";
                else if (directions[i] == "good") queenDirection = "bad";
                else if (directions[i] == "inward") queenDirection = "outward";
                else if (directions[i] == "sweetly") queenDirection = "sourly";
                else if (directions[i] == "wet") queenDirection = "dry";
                else if (directions[i] == "softly") queenDirection = "hardly";
                else if (directions[i] == "sadly") queenDirection = "happily";

                if (userDirection == queenDirection) {
                    cout << endl;
                    typewrite("Great shot! You hit the hedgehog " + userDirection + ". The playing cards cheer.");
                    cout << endl << endl;
                    cards->speak("Go Alice! Woo!");
                    cout << endl << endl;
                } else {
                    cards->speak("Oh no! Alice, wrong way!");
                    queen->speak("OFF WITH YOUR HEAD");
                    typewrite("Re-enter the croquet grounds and try again.");
                    move(WEST);
                }
            }
        
        queen->speak("ALICE! HOW COULD YOU?! HOW COULD YOU HAVE THE HEART TO BEAT ME?!");
        self->speak("Your Majesty, I was simply playing the game!");
        typewrite("Some of the playing cards approach you while the Queen stood there, dazed and confused.");
        cout << endl << endl;
        cards->speak("Alice, Thank You! Thank You!");
        self->speak("What for? I just played the silly game.");
        cards->speak("Nobody has ever beat the Queen of Hearts before - thats why she is - you know, the Queen.");
        typewrite("You stand there confused.");
        cout << endl << endl;
        cards->speak("Alice, we don't think you know what this means. Textland is saved! All you have to do is hit the crown off the Queen's head and put it on yours!");
        self->speak("Oh - I don't know if I can do that, it would hurt the Queen!");
        cards->speak("If you take her crown, you can free all of textland from her jurisdiction. Please, Alice.");
        typewrite("You stand there, thinking about if you should send a hedgehog into the puzzled face of the Queen. Then, you remember all of the creatures of Textland, all the mysterious places, and how much it has taught you. You make your choice.");
        cout << endl << endl;
        queen->speak("OW!");
        typewrite("The Queen stood there picking quills out of her face. She hardly noticed her crown HAD FALLEN OFF HER HEAD.");
        cards->speak("The crown, Alice! Take it!");

        currentLocation->addItem(crown);
        currentLocation->comeBack = true;
    }

    void event(){
        if(currentLocation->name == "Home"){
            homeEvent();
            } 
            
            else if (currentLocation->name == "The Rabbit Hole")
            {
                rabbitholeEvent();
            } 

            else if (currentLocation->name == "The Hall with the Doors")
            {
                hallEvent();

            } 
            
            else if (currentLocation->name == "The Caterpillars Mushroom")
            {
                mushroomEvent();
                
            } else if (currentLocation->name == "The Garden")
            {
                gardenEvent();
            } else if (currentLocation->name == "The Tree")
            {
                treeEvent();
            } else if (currentLocation->name == "Hedge Maze" || "Hedge Maze (pt.2)")
            {
                mazeEvent();
            } else if (currentLocation->name == "Queen's Croquet-Ground")
            {
                croquetgroundEvent();
            }       
    }

    void move(Direction dir){
        if (currentLocation->connections.find(dir) != currentLocation->connections.end()) {
                Location* nextLocation = currentLocation->connections[dir];
                int requiredSize = nextLocation->getRequiredPlayerSize();

                if (nextLocation->name == "The Hall with the Doors"){
                    currentLocation = nextLocation;
                    currentLocation->look();
                    if (!currentLocation->comeBack) {
                        hallEvent();
                    }
                    return;
                }

                if (playerSize == requiredSize) {
                    if (!nextLocation->locked) {
                        currentLocation = nextLocation;
                        currentLocation->look();
                        if(!currentLocation->comeBack){
                        event();
                        }
                        return;
                    } else {
                        typewrite("The door to this way is locked. You cannot enter.");
                    }
                } else {
                    if (requiredSize < playerSize) {
                        typewrite("You are too big to enter.");
                    } else {
                        typewrite("You are too small to enter.");
                    }
                }
                } else {
                    typewrite("You cannot go that way.");
                    }
                    cout << endl;
    }               

    void takeItem(){
        string itemChoice;
        vector<Item*>::const_iterator it1 = findItem(currentLocation->items, itemChoice);
        vector<Item*>::const_iterator it2 = findItem(inventory.inv_items, itemChoice);

        typewrite("What would you like to take?");
            cout << endl;
            cin >> itemChoice;

            it1 = findItem(currentLocation->items, itemChoice);

            it2 = findItem(inventory.inv_items, itemChoice);

            if (it1 != currentLocation->items.end() && it2 == inventory.inv_items.end()) {
                inventory.addItem(*it1);
                it1 = currentLocation->items.erase(it1);
                typewrite(itemChoice + " has been added to your inventory.");
                cout << endl;
            } else if (it2 != inventory.inv_items.end()) {
                typewrite(itemChoice +" is already in your inventory.");
                cout << endl;
            } else {
                typewrite("You do not see a(n) " + itemChoice + ".");
                cout << endl;
                }
    }     

    void observeItem(){    
        string itemChoice;
        vector<Item*>::const_iterator it1 = findItem(currentLocation->items, itemChoice);
        vector<Item*>::const_iterator it2 = findItem(inventory.inv_items, itemChoice);

        typewrite("What item would you like to observe?");
            cout << endl;
            cin >> itemChoice;

            it1 = findItem(currentLocation->items, itemChoice);

            it2 = findItem(inventory.inv_items, itemChoice);

            if (it1 != currentLocation->items.end()) {
                (*it1)->inspect();
            } else if (it2 != inventory.inv_items.end()) {
                (*it2)->inspect();
            } else {
                typewrite("You do not see a(n) " + itemChoice + ".");
                cout << endl;
                }
    }

     void useItem(){
        string itemChoice;
        vector<Item*>::const_iterator it2 = findItem(inventory.inv_items, itemChoice);

        if (inventory.inv_items.empty()) {
                typewrite("Your inventory is empty. There are no items to use.");
                cout << endl;
            } else {
                typewrite("Select an item from your inventory to use:");
                cout << endl;
                inventory.typewriteItems();

                cin >> itemChoice;

                it2 = findItem(inventory.inv_items, itemChoice);
                
                if (it2 != inventory.inv_items.end()) {
                    useItem(*it2); // Function to handle using the selected item
                } else {
                    typewrite("You do not have a(n) " + itemChoice + " in your inventory");
                    cout << endl;
                }
                }
    }

    void typewrite_playerSize(int playerSize){
        if(playerSize == -2){
            typewrite("You are now the smallest in size");
            cout << endl;
        } else if(playerSize == -1){
            typewrite("You are now small in size");
            cout << endl;
        } else if(playerSize == 0){
            typewrite("You are now your normal size");
            cout << endl;
        } else if(playerSize == 1){
            typewrite("You are now big in size");
            cout << endl;
        } else if(playerSize == 2){
            typewrite("You are now biggest in size");
            cout << endl;
        }
    }

    void useItem(Item* item) {

        if (item->name == "crown") {    //end of game sequence started when crown is used. this should be the final command entered in game, only available after defeating the queen.
            typewrite("You turn the crown over in your hands, watching the gemstones sparkle in the light. It feels heavy, heavier than you thought. With a sigh of relief, you place the crown ontop of your head. ");
            cout << endl;
            typewrite("For whatever reason, it fits perfectly; slightly snug, but not too snug. It gives you comfort, having something that feels so comfortable and natural in such an enigmatic, random place. ");
            cout << endl;
            typewrite("You feel transformed by the crown. A sense of power and control washes over you.");
            cout<< endl << endl;
            typewrite("You notice that all of the cards are now gazing at you, with their eyes wide, but shoulders relaxed, smiles on their faces (The numbered cards don't have faces, but you can still feel the idolization). ");
            cout << endl;
            typewrite("Then, they all turn their direction to the Queen."); 
            cout << endl << endl;

            queen->speak("YOU! HOW COULD YOU DO THIS TO ME!? OFF WITH HER HEAD!");

            typewrite("Nobody moved. Instead, everyone looked back at you, waiting for your response - the new Queen's response.");
            cout << endl << endl;

            self->speak("Off with her head.");
            cout << endl << endl;

            typewrite("**END OF GAME**");
            cout << endl << endl << endl;

            typewrite("Collectible count: ");
            cout << inventory.collectibleCount << "/7" << endl << endl;

            if(inventory.collectibleCount == 7){
                typewrite("Congratulations, you have collected all of the collectibles! For this astounding feat you get to recieve an amazing ASCII rendition of the Queen's crown: ");
                cout << endl << endl;

                string filename = "ascii_art.txt";

                ifstream file(filename);
                if (!file.is_open()) {
                    cout << "Error opening file: " << filename << endl;
                }
                string line;
                while (getline(file, line)) {
                    typewrite(line);
                    cout << endl;
                }
                file.close();

                typewrite("Exiting the game...");
                exit(0);
            }
        } 
        else if (item->name == "bottle"){
            if(playerSize>-2) {
                playerSize--;
                typewrite("You take a gulp of the water labelled, 'DRINK ME'. Your clothes start to feel a little looser, it appears you have shrunken in size.");
                cout << endl;
                typewrite_playerSize(playerSize);
                cout << endl;
            } else{
                typewrite("You are as small as you can get");
                cout << endl;
            }
        } 
        else if (item->name == "cake"){
            if(playerSize<2) {
                playerSize++;
                typewrite("You pop the tiny cake in your mouth and bite into the sweet, chewy fondant. Your clothes start to feel a little tighter, it appears you have grown in size.");
                cout << endl;
                typewrite_playerSize(playerSize);
                cout << endl;
            } else {
                typewrite("You are as big as you can get");
                cout << endl;
            }
        } 
        else if (item->name == "right_mushroom"){
            if(playerSize>-2) {
                playerSize--;
                typewrite("You take a bite out of the corner of the piece of mushroom.");
                self->speak("Ouch!");
                typewrite("You feel a violent blow underneath your chin. It had struck your foot!");
                cout << endl;
                typewrite_playerSize(playerSize);
                cout << endl;
            } else {
                typewrite("You are as small as you can get");
                cout << endl;
            }
        }
         else if (item->name == "left_mushroom"){
            if(playerSize<2) {
                playerSize++;
                typewrite("You take a bite out of the corner of the piece of mushroom. You look down and notice your feet look farther and farther.");
                cout << endl;
                typewrite_playerSize(playerSize);
                cout << endl;
            } else {
                typewrite("You are as small as you can get");
                cout << endl;
            }
            } 
            else if (item->name == "hedgehog" || item->name == "flamingo"){
                //croquet stuffs
            } 
            else if (item->name == "golden_key") {
                // Find the garden location
                Location* gardenLocation = nullptr;
                for (const auto& entry : currentLocation->connections) {
                    Direction direction = entry.first;
                    Location* connectedLocation = entry.second;
                    if (connectedLocation->name == "The Garden") {
                        gardenLocation = connectedLocation;
                        break;
                        }
                        }

                    if (gardenLocation) {
                        gardenLocation->locked = false; // Unlock the garden
                        typewrite("You push the golden key into the keyhole in the door that leads to the garden. It seems to be a perfect fit. You turn the key and hear a deadbolt click. You push the door and it swings open.");
                        cout << endl;
                        } else {
                             typewrite("The golden key doesn't seem to fit in any door here.");
                            cout << endl;
                            
                            }
            }
            else if (item->name == "ruby_key") {
                 // Find the croquet ground location
                 Location* croquetgroundLocation = nullptr;
                 for (const auto& entry : currentLocation->connections) {
                    Direction direction = entry.first;
                    Location* connectedLocation = entry.second;
                     if (connectedLocation->name == "Queen's Croquet-Ground") {
                        croquetgroundLocation = connectedLocation;
                        break;
                        }
                        }

                if (croquetgroundLocation) {
                    croquetgroundLocation->locked = false; // Unlock the croquet ground
                    typewrite("You push the ruby key into the keyhole in the door that leads to the Queen's croquet grounds. It seems to be a perfect fit. You turn the key and hear a deadbolt click. You push the door and it swings open.");
                    cout << endl;
                    } else {
                        typewrite("The ruby key doesn't seem to fit in any door here.");
                        cout << endl;
                        }
                        }          
            else if (item->name == "wooden_key") {
                // Find the Maze End location
                Location* mazeendLocation = nullptr;
                for (const auto& entry : currentLocation->connections) {
                    Direction direction = entry.first;
                    Location* connectedLocation = entry.second;
                    if (connectedLocation->name == "Hedge Maze (pt.2)") {
                        mazeendLocation = connectedLocation;
                        break;
                        }
                    }

                if (mazeendLocation) {
                    mazeendLocation->locked = false; // Unlock the Maze End
                    typewrite("You push the wooden key into the keyhole in the door that leads to the second part of the hedge maze. It seems to be a perfect fit. You turn the key and hear a deadbolt click. You push the door and it swings open.");
                    cout << endl;
                    } else {
                    typewrite("The wooden key doesn't seem to fit in any door here.");
                    cout << endl;
                    }
                    }
                    }
    
    void initializeGame() {

         // Create and set up locations, items, and connections between locations
        Location* home = new Location("Home", "Your cozy, familiar home.", 0);
        Location* rabbithole = new Location("The Rabbit Hole", "A deep, seemingly endless rabbit hole filled with cupboards and bookshelves.", 0);
        Location* hall = new Location("The Hall with the Doors", "A long, low hall, lit by a row of lamps hanging from the roof. There are doors all around the hall. In the middle of the hall stands a three-legged table made entirely of solid glass.", 0);
        Location* garden = new Location("The Garden", "A very small, beautiful, lush garden, where you can feel the sunshine's warmth hit your face. Among the garden are flowerbeds of the most colourful flowers, birdbaths, and fountains. Kept by little doors with little keyholes.", -1);
        Location* mushroom = new Location("The Caterpillars Mushroom", "A towering mushroom that seems to touch the clouds. Striped with blue and green, all the way up the stem, it perfectly matches the caterpillar. The smoke from the hookah the Caterpillar holds drifts lazily into the air, forming intriguing patterns.", -2);
        Location* cheshiretree = new Location("The Tree", "A truly hypnotic place, the tree has many vibrant colours and appears to breathe. The leaves ebb and flow with each breath, slowly dancing in the wind. Upon one of the boughs of the tree sits the Cheshire Cat.", 0);
        Location* mazebeginning = new Location("Hedge Maze", "An enigmatic labrynth constructed out of hedges and adorned with flowers. Watch your step as you navigate this maze, for there are many twists and turns.", 1);
        Location* mazeend = new Location("Hedge Maze (pt.2)", "The confusing labrynth carries on.", 1);
        Location* croquetground = new Location("Queen's Croquet-Ground", "Next to the garden, the croquet ground is where the Queen enjoys her games. The ground is covered in lush, green grass with colourful flowers dotted around. Peculiar trees lay out the elaborate croquet course. The Queen's grounds is kept by a door with a blood-red ruby keyhole.", 2);

        garden->locked = true;
        croquetground->locked = true;
        mazeend->locked = true;

        Item* hedgehog = new Item("hedgehog", "A small, spiky, black eyed creature found among the flowers in the garden. Somewhat grumpy but obliging, the hedgehogs are often used for croquet games.");
        Item* rose = new Item("rose", "A rose, grown from a rose tree, which were once white but are now painted red by their gardeners (collectible).");
        Item* bottle = new Item("bottle", "A clear bottle with clear liquid inside, found sitting on top the glass table in the hall. Around the neck of the bottle is a paper label with the words 'DRINK ME', beautifully printed on it in large letters.");
        Item* cake = new Item("cake", "A tiny cake, covered in white fondant, found sitting right underneath the glass table. It is decorated with pink icing, blue, yellow, green, and red sprinkles, and a label which reads 'EAT ME'.");
        Item* flamingo = new Item("flamingo", "A pink feathered flamingo, needed to strike the hedgehog in the Queen's croquet game.");
        Item* goldenkey = new Item("golden_key", "A little golden key, found elegantly sitting on the solid glass table, next to the bottle. Perhaps it fits into an equally little keyhole.");
        Item* soup = new Item("soup", "You take a small sip. After tasting the warm liquid, you realize it's Mock Turtle Soup, made from the Mock Turtle itself. The bitter aftertaste must come from the Mock Turtles sadness and nostalgia from being away from its home by the sea (collectible).");
        Item* tart = new Item("tart", "A small treacle and pepper tart, the object of the court hearing in which many Wonderland creatures attended. The Knave of Hearts was accused of stealing the tarts by the Queen (collectible).");
        Item* jar = new Item ("jar", "an empty jar sitting on a shelf in the rabbit hole labelled, 'ORANGE MARMALADE'. To your disappointment, the jar appears to be empty (collectible).");

        rabbit = new Character("White Rabbit", "A small white rabbit with pink eyes dressed in a waistcoat and carrying a pocket watch. The rabbit is extremely punctual and perpetually in a hurry.");
        caterpillar = new Character("Caterpillar", "A blue and green striped larva who carries a calm, contemplative manner. The Caterpillar is often found smoking his hookah.");
        cat = new Character("Cheshire Cat", "A large, purple and pink striped feline with a distinctive ear-to-ear razor-sharp grin. Often gives cryptic advice or riddles. The Cheshire Cat is capable of disappearing and reappearing at will.");
        queen = new Character("Queen of Hearts", "The tall, temperamental ruler of Wonderland. Her loud, bossy commands are known to all creatures of the realm. Her favorite decree, 'OFF WITH HER HEADS!', matches the blood-red color of her heart-patterned dress. On her head sits her crown, which signifies her rule over Wonderland.");
        cards = new Character("Playing Cards", "The rest of the playing cards in Wonderland take on various roles, like gardeners, courtiers, and croquet players. Their chaotic, clumsy nature is most seen when following directions from the Queen - the one who wears The Crown.");
        self = new Character("You", "A curious and imaginative young girl with golden hair and bright blue eyes.");
        mouse = new Character("Mouse", "A timid and shy little creature, often hiding in tall grass or away from others. The mouse has a peculiar way of talking, known for its verbosity and legal terms.");
        //room connections
        home->addConnection(NORTH, rabbithole);
        rabbithole->addConnection(NORTH, hall);
        hall->addConnection(EAST, garden);
        hall->addConnection(WEST, mushroom);
        hall->addConnection(NORTH, mazeend);
        garden->addConnection(WEST, hall);
        garden -> addConnection(EAST, croquetground);
        mushroom->addConnection(EAST, hall);
        mushroom->addConnection(WEST, mazebeginning);
        mazebeginning->addConnection(EAST, mushroom);
        mazebeginning->addConnection(NORTH, cheshiretree);
        cheshiretree->addConnection(SOUTH, mazebeginning);
        cheshiretree->addConnection(EAST, mazeend);
        mazeend->addConnection(WEST, cheshiretree);
        mazeend->addConnection(SOUTH, hall);
        croquetground->addConnection(WEST, garden);

        currentLocation = home;  // Set starting location

        // Store all the created items in the respective location's items vector
        rabbithole->addItem(jar);
        rabbithole->addItem(tart);
        hall->addItem(bottle);
        hall->addItem(cake);
        hall->addItem(goldenkey);
        garden->addItem(hedgehog);
        mazebeginning->addItem(soup);
        mazeend->addItem(flamingo);
        croquetground->addItem(rose);
        croquetground->addItem(crown);

        //Add each character to their appropriate location
        home->addCharacter(rabbit);
        garden->addCharacter(mouse);
        cheshiretree->addCharacter(cat);
        mushroom->addCharacter(caterpillar);
        croquetground->addCharacter(queen);
        croquetground->addCharacter(cards);

        //Introduction and welcome message

        typewrite("Welcome to Alice's Adventures in Textland! ");
        cout << endl;
        typewrite("In this game you are playing as Alice, a young girl trying to navigate through a wonderous land.");
        cout << endl;
        typewrite("Your goal is to explore, collect items and collectibles, and beat the Queen of Hearts in Croquet!");
        cout << endl;
        typewrite("The text commands are listed below.");
        cout << endl << endl;
        menu();

        typewrite("Good luck on your adventures! Remember, if you need help, type a '?'.");
        cout << endl << endl << endl;

        this_thread::sleep_for(chrono::milliseconds(5555));

        typewrite("You awake next to your sister, who is reading the most boring book in the world (there is not a single picture in that text-riddled book, why would anybody get entertainment out of a bunch of boring words and lines?). Slightly dazed and confused from waking up, you look around:");
        cout << endl << endl;

        currentLocation->look();
        event();
    }

    void playGame() {
        string userInput;
        char choice;

        do {
            // user input
            cout << "> ";
            cin >> userInput;
            choice = tolower(userInput[0]);

            switch (choice) {
            case 'n':
            move(NORTH);
            break;

            case 'e':
            move(EAST);
            break;

            case 's':
            move(SOUTH);
            break;

            case 'w':
            move(WEST);
            break;

            case 'l':
            currentLocation->look(); 
            break;


            case 't':
            takeItem();
            break;

            case 'o':
            observeItem();
            break;

            case 'u':
            useItem();
            break;

            case 'i':
            inventory.typewriteItems();
            break;

            case '?':
            menu(); 
            break;

            default:
            if (choice != 'q'){
                typewrite("Invalid command. Enter ? to view the command menu");
                cout << endl;
                break;
                }
                }
                } while (choice != 'q');
                }

    ~Game() {
        // Free memory for locations
        for (Location* location : locations) {
            delete location;
        }

        // Free memory for items and characters
        for (Item* item : inventory.inv_items) {
            delete item;
        }
        for (Character* character : allCharacters) {
        delete character;
    }
    }

};

int main() {
     Game game;
    game.initializeGame();
    game.playGame();

    return 0;
}