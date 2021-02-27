

/* 
//  Dictionary
//
//  Created by Truman Tang and Adele Wu on 10/1/20.
// 
 */


#include <fstream>
#include <iostream>
#include <string>
#include <filesystem>
#include <vector>
#include <iomanip>
#include <algorithm>


using namespace std;

class Dictionary
{
private:
    string word;
    vector<string> partOfSpeeches;
    vector<string> definitions;

public:
    int getNumberOfDefinitions()
    {
        return definitions.size();
    }

    void setWord(string word)
    {
        this->word = word;
    }

    void setPoSAndDefinition(string pos, string definition)
    {
        partOfSpeeches.push_back(pos);
        definitions.push_back(definition);
    }

    string getWord()
    {
        return word;
    }
    string getPartOfSpeech(int index)
    {
        return partOfSpeeches.at(index);
    }
    string getDefinition(int index)
    {
        return definitions.at(index);
    }

};

vector<string> getPoSAndDefinition(string substring, string delimiterSpliter)
{
    vector<string> vectorPoSAndDefinition;
    string partOfSpeech;
    string definition;
    int indexOfDelimiter = substring.find(delimiterSpliter);

    partOfSpeech = substring.substr(0, indexOfDelimiter); //find the partOfSpeech
    definition = substring.substr(indexOfDelimiter + delimiterSpliter.size(), substring.size()); // find the definition

    vectorPoSAndDefinition.push_back(partOfSpeech); //puts part of speech in the vector first
    vectorPoSAndDefinition.push_back(definition); //puts definition in the vector

    return vectorPoSAndDefinition;
}

vector<string> partOfSpeech(vector<string> output, vector<string> temporary, string secondWord) //gets the same part of speech 
{
    for (auto i : output)       
    {
        auto k = i; //use a temporary variable because i will erase part of i if leave it as i
        string delimiter = "]: "; 
        string word = k.substr(0, k.find('['));
        k.erase(0, k.find('[') + 1); //erases the first word
        string PoS = k.substr(0, k.find(']'));// grab the isolated second word
        if (PoS.compare(secondWord) == 0)
        {
            temporary.push_back(i);
        }
    }
    output = temporary;
    return output;
}
vector<string> reverse(vector<string> output) //reverse the vector 
{
    reverse(output.begin(), output.end());      
    return output;
}
vector<string> distinct(vector<string> output, vector<string> temporary) // gets rid of duplicates
{
    auto ip = unique(output.begin(), output.end());      
    output = vector<string>(output.begin(), ip);
    for (auto& i : output)
    {
        temporary.push_back(i);
    }
    output = temporary;
    return output;
}
void printError(bool requestPoS, string secondWord, string thirdWord, string fourthWord) //prints the errors
{
    string errorMsg;
    if ((requestPoS != true) && (secondWord != "reverse") && (secondWord != "distinct") && (secondWord != "")) //error message for 2nd parameter
    {
        errorMsg = "<The entered 2nd parameter '";
        cout << setw(8) << "|" << endl;
        cout << setw(36) << errorMsg << secondWord << "' is NOT a part of speech.> " << endl <<
            setw(36) << errorMsg << secondWord << "' is NOT 'distinct'.>" << endl <<
            setw(36) << errorMsg << secondWord << "' is NOT 'reverse'.>" << endl <<
            setw(36) << errorMsg << secondWord << "' was disregarded.>" << endl <<
            setw(82) << "<The 2nd parameter should be a part of speech or 'distinct' or 'reverse'.>" << endl;
        cout << setw(8) << "|" << endl;
    }

    if ((thirdWord != "reverse") && (thirdWord != "distinct") && (thirdWord != "")) //error message for 3rd parameter
    {
        errorMsg = "<The entered 3rd parameter '";
        cout << setw(8) << "|" << endl;
        cout << setw(36) << errorMsg << thirdWord << "' is NOT 'distinct'.>" << endl <<
            setw(36) << errorMsg << thirdWord << "' is NOT 'reverse'.>" << endl <<
            setw(36) << errorMsg << thirdWord << "' was disregarded.>" << endl <<
            setw(62) << "<The 3rd parameter should be 'distinct' or 'reverse'.>" << endl;
        cout << setw(8) << "|" << endl;
    }

    if ((fourthWord != "reverse") && (fourthWord != "distinct") && (fourthWord != "")) //error message for 4th parameter
    {
        errorMsg = "<The entered 4th parameter '";
        cout << setw(8) << "|" << endl;
        cout << setw(36) << errorMsg << fourthWord << "' is NOT 'reverse'.>" << endl <<
            setw(36) << errorMsg << fourthWord << "' was disregarded.>" << endl <<
            setw(48) << "<The 4th parameter should be 'reverse'.>" << endl;
        cout << setw(8) << "|" << endl;
    }
}

void printHelpMenu() //menu to help users
{
    cout << setw(8) << "|" << endl;
    cout << setw(39) << "PARAMETER HOW-TO, please enter:" << endl <<
        setw(66) << "1. A search key -then  2. An optional part of speech -then" << endl <<
        setw(64) << "3. An optional 'distinct' -then 4. An optional 'reverse'" << endl;
    cout << setw(8) << "|" << endl;
}


int main()
{
    cout << "! Opening data file... " << filesystem::current_path() << endl;
    ifstream infile;

    infile.open("Data.CS.SFSU.txt");  //into file
    if (!infile.is_open())      // if cant open txt file
    {
        cout << "<!>ERROR<!> ===> File could not be opened." << endl;
        cout << "<!>ERROR<!> ===> Provided file path: " << filesystem::current_path() << endl;
        cout << "<!>Enter the CORRECT data file path: ./Data.CS.SFSU.txt" << endl;
    }

    string currentLine, word;  // variable for currentLine and word
    string delimiter_line = "|"; //variable to we use to parse the txt file for the line
    string delimiter_arrow = " -=>> "; //variable to we use to parse the txt file for the arrow
    int numOfKeyWords = 0; // variable for how many keyWords in txt file
    int numOfDefWords = 0; // variable for how many definition Words in txt file

    cout << "! Loading data..." << endl;

    vector<Dictionary> vectorOfDictionaries;
    while (getline(infile, currentLine))
    {
        Dictionary dictionary;      // Make Dictionary

        int currentStringPosition = 0;      // variable for initial string position

        int currentDelimiterPosition = currentLine.find(delimiter_line);        // variable for initial delimiter position

        word = currentLine.substr(0, currentDelimiterPosition);     // grabs the word

        dictionary.setWord(word);       // Add word to dictionary
        numOfKeyWords++;

        while (currentDelimiterPosition < currentLine.size())
        {
            currentStringPosition = currentDelimiterPosition + 1;       // get current string position

            currentDelimiterPosition = currentLine.find(delimiter_line, currentStringPosition);     // get current delimiter position

            // At the end of the string.
            if (currentDelimiterPosition == -1)
            {
                currentDelimiterPosition = currentLine.size(); 
            };

            string currentSubstring = currentLine.substr(currentStringPosition, currentDelimiterPosition - currentStringPosition); // (- currentStringPosition) to account for the substring positioning

            vector<string> pair = getPoSAndDefinition(currentSubstring, delimiter_arrow); //grab the part of speech and definition to store them in the dictionary

            dictionary.setPoSAndDefinition(pair.at(0), pair.at(1));

            // If you are at the end of the current line then get out
            if (currentDelimiterPosition == currentLine.size() - 1)
            {
                break;
            }
            numOfDefWords++;
        }

        // Add current dictionary to vector of dictionaries
        vectorOfDictionaries.push_back(dictionary); 
    }

    cout << "! Loading Complete..." << endl;
    cout << "! Closing data file... ./Data.CS.SFSU.txt" << endl;
    cout << "-----DICTIONARY 340 C++-----" << endl;
    cout << "----- Keywords: " << numOfKeyWords << endl;
    cout << "----- Definitions: " << numOfDefWords << endl;

    int searchNumber = 0;   //counts which search number we are on
    bool quit = false;  //see when to stop the program
    string input; //user input

    do {
        searchNumber++;
        cout << "Search [" << searchNumber << "]: ";
        getline(cin, input); // user input with mulitple lines 

        int userLength = input.length();

        //makes all character of user's input to lowercase
        for (int i = 0; i < userLength; i++) 
        {
            input[i] = tolower(input[i]);
        }

        // parsing user input by space
        char space = ' ';
        string Word = input.substr(0, input.find(space));     // gets first Word
        input.erase(0, input.find(space));

        input = input.substr(input.find(space) + 1);
        string secondWord = input.substr(0, input.find(space));  // gets second word
        input.erase(0, input.find(space));

        input = input.substr(input.find(space) + 1);
        string thirdWord = input.substr(0, input.find(space)); // gets third word
        input.erase(0, input.find(space));

        input = input.substr(input.find(space) + 1);
        string fourthWord = input.substr(0, input.find(space)); // gets fourth word
        input.erase(0, input.find(space));

        string fifthWord = input.substr(input.find(space) + 1); // gets fifth word to determine out of bounds
        input.erase(0, input.find(space));                      //input is now empty

        vector<string> output;  //the output vector string
        vector<string> temporary; // temporary vector string
        bool requestPoS = false; //see if part of speech is called
        bool requestDistinct = false; //see if distinct is called
        bool requestReverse = false; //see if reverse is called
        
        vector<string> pos = { "noun", "verb", "adjective", "adverb", "pronoun", "preposition", "conjunction", "interjection" }; //shows all the case of Part of speech

        if ((secondWord != "") && (thirdWord != "") && (fourthWord != "") && (fifthWord != ""))
        {
            printHelpMenu();
        }
        else if (Word == "!q") // ends program and program makes all string lowercase at first
        {
            
            quit = true;
        }
        else
        {
            for (auto i : vectorOfDictionaries)     // regular
            {
                if (Word == i.getWord())
                {
                    for (int j = 0; j < i.getNumberOfDefinitions(); j++)
                    {
                        output.push_back(i.getWord() + " [" + i.getPartOfSpeech(j) + "]: " + i.getDefinition(j));
                    }
                }
            }

            sort(output.begin(), output.end()); //sorts the vector
            for (int i = 0; i < pos.size(); i++) //go through the pos vector to compare with our second wor
            {
                if (secondWord.compare(pos[i]) == 0)
                {
                    requestPoS = true;
                }
            }
            if (secondWord == "distinct" || thirdWord == "distinct") // cases for distinct
            {
                requestDistinct = true;
                output = distinct(output, temporary);
            }
            if (secondWord == "reverse" || thirdWord == "reverse" || fourthWord == "reverse") // cases for reverse
            {
                requestReverse = true;
                output = reverse(output);
            }
            if (requestPoS == true)
            {
                output = partOfSpeech(output, temporary, secondWord);
            }

            printError(requestPoS, secondWord, thirdWord, fourthWord);

            bool hasWord = false;
            for (auto& i : output) //if the word contains any digit capitalize all the characters
            {
                if (find_if(Word.begin(), Word.end(), ::isdigit) != Word.end())
                {
                    for (int character = 0; character < Word.size(); character++)
                    {
                        i[character] = toupper(i[character]);
                    }

                }

                i[0] = toupper(i[0]); // always going to capitalize teh first letter

                if (Word.find(i)) // see if the there is a word in the dictionary
                {
                    hasWord = true;
                }
            }
            if (hasWord) //checks to see if there is a word
            {

                cout << setw(8) << "|" << endl;

                for (int i = 0; i < output.size(); i++) 
                {
                    int spacing = output[i].size() + 8; //gets the proper spacing for the output
                    cout << setw(spacing) << output[i] << endl;  //prints the dicitonary
                }
                cout << setw(8) << "|" << endl;
            }
            else if ((Word == "!help") || (Word == "")) //get the menu
            {
                printHelpMenu();
            }
            else // word is not found in dictionary
            {
                cout << setw(8) << "|" << endl;
                cout << setw(69) << "<NOT FOUND> To be considered for the next release. Thank you." << endl;
                cout << setw(8) << "|" << endl;
                printHelpMenu();
            }
        }
    }

    while (!quit);

    if (quit)
    {
        cout << endl << "-----THANK YOU-----" << endl;
    }
}


