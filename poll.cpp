//
///Users/monicabellare/Desktop/college/CS31/proj3/proj3.xcodeproj  poll.cpp
//  proj3
//
//  Created by Monica Bellare on 10/28/18.
//  Copyright © 2018 Monica Bellare. All rights reserved.
//

#include <iostream>
#include <string>
#include <cctype>
#include <cassert>
using namespace std;

const string states = " AL AK AZ AR CA CO CT DE FL GA HI ID IL IN IA KS KY LA ME MD MA MI MN MS MO MT NE NV NH NJ NM NY NC ND OH OK OR PA RI SC SD TN TX UT VT VA WA WV WI WY";

bool instanceOf(string s) { // checks whether a string is a state code or not (this function is only called on two-character strings)
    for(int i = 0; i < s.size(); i++) {
        s[i] = toupper(s[i]);
    }
    for(int i = 1; i < states.size()-1; i+=3) {
        if(s == states.substr(i,2)) {
            return true; // returns true if the string is a state code
        }
    }
    return false; // returns false if the string is not a state code
}

bool validForecast(string s) { // makes sure individual forecast in a poll data string is valid
    if(!(instanceOf(s.substr(0, 2))))
        return false; // returns false if the first two characters are not a state code
    if(s.size() == 2)
        return true; // returns true if the entire forecast is just the state code
    if(!(isdigit(s[2])))
        return false; // returns false if the 3rd character is not a digit
    if(s.size() == 3)
        return false; // returns false if the size of the string is 3
    if(isdigit(s[s.size()-1]))
        return false; // returns false if the last element is a digit
    
    int letterCount = 0; // keeps track of number of letters (exluding state code)
    for(int i = 3; i < s.size(); i++) {
        if(isdigit(s[i])) {
            if(isdigit(s[i-1]) && isdigit(s[i-2]))
                  return false; // returns false if there are 3 or more digits in a row
        }
        else if(isalpha(s[i])) {
            letterCount++;
            if(!isdigit(s[i-1]))
                return false; // returns false if there are 2 or more letters in a row (excluding the state code)
        }
        else
            return false; // returns false if any element is something other than a letter or a number
    }
    
    if(letterCount > 0 && isalpha(s[s.size()-1])) // returns true if there are instances of letters & if the last element is a letter
        return true;
    else
        return false; // returns false otherwise
        
    // if it follows a state code --> must be comma OR number (up to two digits) OR end
    // if it follows a number (digit) --> must be ONE additional digit OR one party code
    // if it follows a party code --> must be a comma OR number (up to two digits) OR end
}


bool hasProperSyntax(string pollData) {
    if(pollData.size() == 0) // returns true if pollData is empty
        return true;
    
    for(int i = 0; i<pollData.size(); i++) { // checking if any character in pollData is something other than a letter, number, or comma (if so, returns false)
        if((!(isalpha(pollData[i]))) && (!(isdigit(pollData[i]))) && (pollData[i]!=','))
            return false;
    }
    
    int commaCount = 0;
    for(int i = 0; i < pollData.size(); i++) {
        if(pollData[i] == ',') {
            if(pollData[i-1] == ',' || i == pollData.size()-1) {
                return false; // returns false if there are two or more commas in a row OR if a comma is the last element
            }
            commaCount++; // counts number of commas in input
        }
    }
    
    if(commaCount==0)
        return (validForecast(pollData)); // considers entire input as one forecast if there are no commas
    
    int commaPlaces[10000]; // array of the indexes of commas; could not set length to var commaCount b/c Linux server gave an error
    int j = 0; // keeps track of index in commaPlaces
    for(int i = 0; i < pollData.size(); i++) {
        if(pollData[i] == ',') {
            commaPlaces[j] = i; // set 1st index of array to index of the first comma in the poll data string, 2nd to the 2nd, etc.
            j++;
        }
    }
    
    int c = 0; // keeps track of index in pollData
    for(int i = 0; i < commaCount; i++) {
        if(!validForecast(pollData.substr(c,commaPlaces[i]-c)))
            return false; // returns false if the substring between 2 commas or before the first comma is not a valid forecast
        c = commaPlaces[i]+1;
    }
    
    if(validForecast(pollData.substr(c, pollData.size()-c))) // checks if substring after the last comma is a valid forecast
        return true;
    else
        return false;
}

int tallySeats(string pollData, char party, int& seatTally) {
    if(!hasProperSyntax(pollData)) // returns 1 if pollData is not a valid poll data string
        return 1;
    if(!(isalpha(party))) // returns 2 if party is not a letter character; if party & pollData are invalid inputs, 1 will be returned
        return 2;
    for(int i = 0; i<pollData.size(); i++) {
        if(isalpha(pollData[i]))
            pollData[i] = toupper(pollData[i]); // makes all letters in poll data string uppercase for easier comparison
    }
    party = toupper(party); // makes party uppercase for easier comparison
    
    seatTally = 0; // resets to 0 regardless of initial value of variable
    
    if(pollData.size() == 0) // return 0 if pollData is empty
        return 0;
    
    for(int i = 2; i < pollData.size()-1; i++) { // ignores first two elements since they are a state code & skips last element so that there aren't errors with checking pollData[i+1]
        if(pollData[i] == party && !isalpha(pollData[i-1]) && !isalpha(pollData[i+1])) { // looks for party letters; if a letter is preceded or followed by another letter, it is a state code and should be ignored
            if(isdigit(pollData[i-2])) {
                seatTally += 10*((pollData[i-2])-'0'); // adds digit in the tenths place of a number, if it exists
            }
            seatTally += (pollData[i-1]-'0'); // adds digit in the ones place
        }
    }
    
    if(pollData[pollData.size()-1] == party) { // if the last letter in a poll data string is the party, this adds the number to seatTally
        if(isdigit(pollData[pollData.size()-3])) {
            seatTally += 10*((pollData[pollData.size()-3])-'0');
        }
        seatTally += (pollData[pollData.size()-2]-'0');
    }
    
    return 0;
}

int main()
{
    int seatTally = 9;
    assert(hasProperSyntax("CA"));
    assert(!hasProperSyntax("im"));
    assert(hasProperSyntax("me12D"));
    assert(hasProperSyntax("me1D"));
    assert(!hasProperSyntax("miu"));
    assert(!hasProperSyntax("mi8"));
    assert(hasProperSyntax("rI23r33D"));
    assert(hasProperSyntax(""));
    assert(hasProperSyntax("rI2r3D"));
    
    assert(!hasProperSyntax("ne3r00456D"));
    assert(hasProperSyntax("Ny9D,Vt*3,NJ3r") == false);
    assert(hasProperSyntax("MA9D,KS4R") && hasProperSyntax("KS4R,MA9D"));
    assert((tallySeats("ca5d,ny9r11i2d", 'd', seatTally) == 0 && seatTally==7));
    

    
}
