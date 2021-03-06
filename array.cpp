//  array.cpp
//  proj4
//
//  Created by Monica Bellare on 11/2/18.
//  Copyright © 2018 Monica Bellare. All rights reserved.

#include <iostream>
#include <string>
#include <cassert>
using namespace std;

int appendToAll(string a[], int n, string value) {
    if(n<0) // returns -1 for any potential errors OR if n is 0
        return -1;
    for(int i = 0; i < n; i++) {
        a[i] += value; // adds value to first n elements in array
    }
    return n; // returns n for no errors (incl. array size of 0 OR n is 0)
}

int lookup(const string a[], int n, string target) {
    if(n<0)
        return -1;
    for(int i = 0; i < n; i++) {
        if(a[i]==target) {
            return i; // returns index of first instance of a string that matches target
        }
    }
    return -1; // returns -1 if there is no instance of target (incl. n is 0)
}

int positionOfMax(const string a[], int n) {
    if(n<0)
        return -1;
    if(n==0)
        return -1;
    int latest = 0; // variable to store smallest instance of string >= every other string
    for(int i = 1; i < n; i++) {
        if(a[i] > a[latest]) {
            latest = i; // updates latest if there is a "greater" string (alphabetically), however, if there is an identical one, latest doesn't change
        }
    }
    return latest;
}

int rotateLeft(string a[], int n, int pos) {
    if(n<0)
        return -1;
    if(pos<0)
        return -1;
    if(pos >= n)
        return -1;
    string str = a[pos];
    for(int i = pos; i < n-1; i++) {
        a[i] = a[i+1];
    }
    a[n-1] = str;
    return pos; // returns original position of the word
}

int countRuns(const string a[], int n) {
    if(n<0)
        return -1;
    int count = 0;
    int i = 0;
    while(i < n) {
        while(i < n-1 && (a[i] == a[i+1])) {
            i++;
        }
        count++;
        i++;
    }
    return count; // returns count of consecutive identical item sequences
}

int flip(string a[], int n) {
    if(n<0)
        return -1;
    string holder[1000]; // declaring string array to hold the changed string
    for(int i = 0; i < n; i++) {
        holder[i] = a[i]; // initializing with current a[] elements
    }
    for(int i = n; i < 1000; i++) {
        holder[i] = ""; // initializing remaining indexes with empty strings
    }
    int m = n-1;
    for(int i = 0; i < n; i++) {
        holder[m] = a[i]; // flipping by adding in opposite order to holder[]
        m--;
    }
    for(int i = 0; i < n; i++) {
        a[i] = holder[i]; // changing original array to store elements in holder[] order
    }
    return n;
}

int differ(const string a1[], int n1, const string a2[], int n2) {
    if(n1 < 0 || n2 < 0) // error if either of the arrays OR both of the arrays have lengths less than 0
        return -1;
    int n; // declaring variable to hold the size of the smaller array/check point
    if(n1 <= n2) // if n1 == n2, n can just be set to n1 (so used <=)
        n = n1;
    else // case only if n2 < n1
        n = n2;
    for(int i = 0; i < n; i++) {
        if(a1[i] != a2[i])
            return i;
    }
    return n;
}

int subsequence(const string a1[], int n1, const string a2[], int n2) {
    if(n1 < 0 || n2 < 0) // error if either of the arrays OR both of the arrays have lengths less than 0
        return -1;
    if(n2 > n1) // error if second array is longer than first
        return -1;
    if(n2 == 0) // returns 0 if n1 or n2 are 0 (since n2 can't be greater than n1)
        return 0;
    
    int holder[1000]; // array to hold all indexes in a1 that equal a2[0]
    for(int i = 0; i < 1000; i++) {
        holder[i] = -1; // initializes all values in holder[] to -1
    }
    int h = 0;
    
    for(int i = 0; i < n1; i++) {
        if(a1[i] == a2[0]) {
            holder[h] = i;
            h++;
        }
    }
    
    if(holder[0] == -1)
        return -1; // return -1 if there are no instanes of a2[0] in a1[]
    
    int instances = 0; // variable to hold the number of instances of a2[0] in a1[]
    for(int i = 0; i < 1000; i ++) {
        if(holder[i] != -1)
            instances++; // initializes "instances" with number of instances of a2[0] in a1[]
    }
    
    for(int i = 0; i < instances; i++) {
        int count = 0;
        int j = 0;
        int k = holder[i];
        while((k < n1) && (j < n2) && (a1[k] == a2[j])) {
            count++;
            k++;
            j++;
        }
        if(count == n2)
            return holder[i];
    }
    return -1; // returns -1 if there is no matching subsequence of a2[] in a1[]
}

int lookupAny(const string a1[], int n1, const string a2[], int n2) {
    if(n1 < 0 || n2 < 0) // error if either of the arrays have lengths less than 0
        return -1;
    for(int i = 0; i < n1; i ++) {
        for(int j = 0; j < n2; j++) {
            if(a1[i] == a2[j])
                return i; // returns first instance of a2[] index in a1[]
        }
    }
    return -1; // returns -1 if there is no index of a2[] that matches one in a1[] (INCL. IF n1 OR n2 are 0)
}

int divide(string a[], int n, string divider) {
    if(n < 0)
        return -1;
    int count = 0; // variable to store # of times through if statement
    for(int i = 0; i < n; i++) {
        if((count < n) && (a[i] > divider)) {
            rotateLeft(a, n, i); // moves element to end of array if it's > divider
            i--; // to ensure the element that just moved to prevoious spot isn't skipped
            count++; // to prevent a never-ending loop
        }
    }
    
    int firstGreater = 0; // variable to hold first index of element > divider
    for(int i = 0; i < n; i++) {
        if(a[i] > divider) {
            firstGreater = i;
            break;
        }
    }
    
    int countEqual = 0; // variable to store the number of elements that equal divider
    for(int i = 0; i < n; i++) {
        if(a[i] == divider)
            countEqual++;
    }
    
    count = 0; // variable to store # of times through if statement
    for(int i = 0; i < firstGreater; i++) {
        if((count <= countEqual) && (a[i] == divider)) {
            rotateLeft(a, firstGreater, i); // moves element to last spot before elements > divider
            i--;
            count++;
        }
    }
    
    for(int i = 0; i < n; i++) {
        if(!(a[i] < divider))
            return i;
    }
    return n;
}

int main() {
    // TEST CASES
    //appendToAll()
    string a[6] = {"Summer", "Ellie", "Emma", "Olivia", "Hannah", "Dylan"};
    string a2[0] = {}; // empty array
    assert(appendToAll(a,2," :)")==2); // n less than array length
    assert(appendToAll(a,6,".")==6); // n is length of array
    assert(appendToAll(a,-9,"!")==-1); // negative n value
    assert(appendToAll(a,0,"!")==0); // n = 0
    assert(appendToAll(a2,0,"!")==0); // n = 0, which is length of array
    
    //lookup()
    string b[5] = {"", "tree", "water", "plant", "tree"}; // array with one empty string and two of the same element
    assert(lookup(b,5,"tree")==1); // looking for word with two instances in array (but only returns first)
    assert(lookup(b,3,"plant")==-1); // looking through first 3 elements for a string that is in the 4th element
    assert(lookup(b,2,"")==0); // looking for empty string in first 2 elements
    assert(lookup(b,-2,"water")==-1); // negative n value
    assert(lookup(b,0,"water")==-1); // n = 0
    assert(lookup(b,5,"green")==-1); // looking for string not present
    assert(lookup(b,4,"Plant")==-1); // looing for string with different capitlization
    
    //positionOfMax()
    const string c[8] = {"", "1", "banana", "apple", "orange", "carrot", "edamame", "Orange"}; // array with empty string, number strings, two of same element BUT different capitalizations, two of same element
    assert(positionOfMax(c,8)==4); // regular test (lowercase is considered greater than uppercase when compared in arrays), returns 1st max. position
    assert(positionOfMax(c,2)==1); // checking first 2 elements (number strings considered greater than empty strings)
    assert(positionOfMax(c,4)==2); // checking first 4 elements
    assert(positionOfMax(c,1)==0); // n = 1
    assert(positionOfMax(c,0)==-1); // n = 0
    assert(positionOfMax(c,-3)==-1); // n < 0
    
    //rotateLeft()
    string d[6] = {"Hello,", "my", "name", "is", "Monica", "."};
    assert(rotateLeft(d,-2, 1)==-1); // n < 0
    assert(rotateLeft(d,2, -1)==-1); // pos < 0
    assert(rotateLeft(d,6, 2)==2); // normal run, new array should be in order: "Hello," "my" "is" "Monica" "." "name"
    assert(rotateLeft(d,3, 1)==1); // n < array length
    assert(rotateLeft(d,6, 5)==5); // pos is last element --> array should not change
    assert(rotateLeft(d,6, 8)==-1); // pos > n
    assert(rotateLeft(d,3, 4)==-1); // pos > n but still an element in the array (still an error)
    assert(rotateLeft(d,0, 0)==-1); // n = 0
    assert(rotateLeft(d,6, 0)==0); // pos = 0
    
    //countRuns()
    const string e[8] = {"hello", "hello", "bye", "hi", "bye", "bye", "bye", "welcome"}; // array with two sets of 2-or-more consecutive identical strings; "bye" is repeated as an individual string and as a 3-consecutive identical string
    assert(countRuns(e, 8)==5); // normal total number of consecutive identical strings
    assert(countRuns(e, 5)==4); // n < array length
    assert(countRuns(e, 0)==0); // n = 0
    assert(countRuns(e, -2)==-1); // n < 0
    
    //flip()
    string f[5] = {"this", "is", "a", "test", "!"};
    assert(flip(f, 5)==5); // normal run; flipped array should be "!", "test", "a", "is", "this"
    assert(flip(f, 0)==0); // n = 0
    assert(flip(f, -6)==-1); // n < 0
    assert(flip(f, 3)==3); // n < array length, and therefore only flips first 3 elements w/ each other
    
    //differ()
    string g[7] = {"banana", "pineapple", "grape", "apple", "kiwi", "strawberry", "melon"};
    string g2[4] = {"banana", "pineapple", "grape", "cantaloupe"};
    string g3[2] = {"pineapple", "melon"};
    assert(differ(g, -1, g2, 4) == -1); // n1 < 0
    assert(differ(g, 7, g2, -1) == -1); // n2 < 0
    assert(differ(g, -1, g2, -1) == -1); // n1 < 0 & n2 < 0
    assert(differ(g, 7, g2, 4) == 3); // normal case; first instance of different strings is @ index 3
    assert(differ(g, 3, g2, 2) == 2); // n1 & n2 are less than their respective arrays' lengths
    assert(differ(g, 3, g2, 4) == 3); // n1 < n2
    assert(differ(g, 0, g2, 0) == 0); // n1 & n2 both equal 0
    assert(differ(g2, 4, g3, 2) == 0); // first elements are different even though an element in g3[] is in g2[]
    
    //subsequence()
    string h[7] = {"banana", "pineapple", "grape", "apple", "kiwi", "strawberry", "melon"};
    string h2[3] = {"grape", "apple", "kiwi"};
    string h3[2] = {"pineapple", "strawberry"};
    string h4[7] = {"banana", "pineapple", "strawberry", "apple", "pineapple", "strawberry", "melon"};
    assert(subsequence(h, -1, h2, 3) == -1); // n1 < 0
    assert(subsequence(h, 7, h2, -1) == -1); // n2 < 0
    assert(subsequence(h, -1, h2, -1) == -1); // n1 < 0 & n2 < 0
    assert(subsequence(h, 2, h2, 3) == -1); // n2 > n1
    assert(subsequence(h, 7, h2, 3) == 2); // normal case; first index of subsequence in h is 2
    assert(subsequence(h, 4, h2, 2) == 2); // n1 & n2 are less than their respective arrays' lengths, but index is the same
    assert(subsequence(h, 7, h2, 1) == 2); // 1 string subsequence
    assert(subsequence(h, 0, h2, 0) == 0); // n1 & n2 both equal 0
    assert(subsequence(h, 7, h2, 0) == 0); // n2 = 0
    assert(subsequence(h4, 7, h3, 2) == 1); // two instances of h3 in h4
    
    //lookupAny()
    string i[7] = {"banana", "pineapple", "grape", "apple", "kiwi", "strawberry", "melon"};
    string i2[4] = {"strawberry", "apple", "grape", "kiwi"};
    string i3[2] = {"banana", "melon"};
    assert(lookupAny(i, -7, i2, 4) == -1); // n1 < 0
    assert(lookupAny(i, 7, i2, -4) == -1); // n2 < 0
    assert(lookupAny(i, 0, i2, 4) == -1); // n1 = 0
    assert(lookupAny(i, 7, i2, 0) == -1); // n2 = 0
    assert(lookupAny(i, 0, i2, 0) == -1); // n1 & n2 both equal 0
    assert(lookupAny(i, 7, i2, 4) == 2); // normal case; first index of i2[] element in i[] is 2
    assert(lookupAny(i, 1, i2, 1) == -1); // n1 & n2 are both 1
    assert(lookupAny(i, 6, i2, 1) == 5); // n2 = 1
    assert(lookupAny(i2, 4, i3, 2) == -1); // no element of i3[] is in i2[]
    
    //divide()
    string j[5] = {"coyote", "elephant", "walrus", "animal", "cactus"};
    string j1[7] = {"coyote", "elephant", "Elephant", "walrus", "elephant", "", "animal"};
    assert(divide(j, 4, "deer") == 2); // n < array length
    assert(divide(j, 5, "cedar") == 2);  //  normal case
    assert(divide(j, 5, "a") == 0); // all elements > divider
    assert(divide(j, 5, "zoo") == 5);  //  all elements are < divider
    assert(divide(j, -2, "deer") == -1);  //  n < 0
    assert(divide(j, 0, "deer") == 0);  //  n = 0
    assert(divide(j1, 7, "elephant") == 4); // multiple cases of divider in j1, so returns first case
    
    cerr << "success!" << endl;
}

