//
//  main.cpp
//  proj 4
//
//  Created by Swetha S on 5/2/22.

//all functions that return an int must return −1 if they are passed any bad arguments (e.g. a negative array size, or a position that would require looking at the contents of an element past the last element we're interested in)

#include <iostream>
#include <array>
#include <iostream>
#include <string>
#include <cassert>
using namespace std;

//returns the number of strings in the array that are equal to target
// if n is negative, returns -1
int enumerate(const string a[], int n, string target){
    int count = 0;
    if (n<0)
        return -1;
    for (int i = 0; i < n; i++ ){
        if (a[i] == target){
            count++;
        }
    }
    return count;
}

//returns the position of a string in the array that is equal to target
// if there is more than one string, return the first
// return -1 if there is no such string or n is negative
int findMatch(const string a[], int n, string target){
    if (n<0)
        return -1;
    for (int i = 0; i < n; i++ ){
        if (a[i] == target){
            return i;
        }
    }
    return -1;
}
// finds the earliest occurance in a of one or more consecutive strings that are equal to target
// sets begin to pos of first occurence of target
// sets end to last occurence of target
// returns true
// if there is no such string or n is negative, returns false, leaves begin and end unchanged
bool findRun(const string a[], int n, string target, int& begin, int& end){
    if (n<0)
        return false;
    for (int i = 0; i < n; i++ ){
        if (a[i] == target){
//            cerr << "i is " << i << endl;
            begin = i;
            for (int j = begin; j < n ; j++){
                if (a[j] == target){
//                    cerr << "j is " << j << endl;
                    end = j;
                }
                else{
                    return true;
                }
            }
        }
    }
    return false;
}

// returns the position of a string in a so that string is <= every string in a
// if there is more than one, return the first
// returns -1 if n = 0 or is negative
int findMin(const string a[], int n){
    if (n==0 || n<0){
        return -1;
    }
    string min = a[0];
    int pos = 0;
    for (int i = 0; i < n; i++ ){
        if (a[i]<min){
            pos = i;
            min = a[i];
        }
    }
    return pos;
}

// eliminates the value at pos by copying all elements after it one place to the left
// puts eliminated value into the last known position
// returns the original position of the item that was moved to the end
// returns -1 if n is negative, pos is negative, or pos is greater than n-1
int moveToEnd(string a[], int n, int pos){
    if (n <0)
        return -1;
    if (pos < 0)
        return -1;
    if (pos > (n-1))
        return -1;
    int ogPos = pos;
    string temp = a[pos];
    for (int i = pos; i < n-1 ; i++){
        a[i] = a[i+1];
    }
    a[n-1] = temp;
    return ogPos;
}

// eliminates the value at pos by copying all elements before it one place to the right
// puts eliminated value into first position
// returns original position of the item that was moved to the beginning
// returns -1 if n is negative, pos is negative, or pos is greater than n-1
int moveToBeginning(string a[], int n, int pos){
    if (n <0)
        return -1;
    if (pos < 0)
        return -1;
    if (pos > (n-1))
        return -1;
    int ogPos = pos;
    string temp = a[pos];
    for (int i = pos; i > 0; i--){
        a[i] = a[i-1];
    }
    a[0] = temp;
    return ogPos;
}

// returns the position of the first corresponding elements of a1 and a2 that are not equal
// if arrays are equal until one or both run out, return lower/equal of n1 and n2
// return -1 if n1 or n2 are negative
int findDifference(const string a1[], int n1, const string a2[], int n2){
    if (n1 < 0 || n2 < 0){
        return -1;
    }
    int n;
    if (n1<n2)
        n = n1;
    else
        n = n2;
    for (int i = 0; i < n; i++){
        if (a1[i] != a2[i]){
            return i;
        }
    }
    return n;
}

// for every sequence of consecutive items in a, retain only one item of that sequence
// returns the number of retained items
// returns -1 if n is negative
int removeDups(string a[], int n){
    if (n < 0)
        return -1;
    if (n==0){
        return 0;
    }
    int j = 1;
    for (int i = 0; i < n-1; i++){
        if (a[i] != a[i+1]){
            a[j] = a[i+1];
            j++;
        }
    }
    
    return j;
}

// if all n2 elements of a2 appear in a1, in the same order, return true
// if a1 does not so include a2, return false
// returns false if n1 or n2 are negative, or if n2 is greater than n1
bool subsequence(const string a1[], int n1, const string a2[], int n2){
    if (n1 < 0 || n2 < 0){
        return false;
    }
    if (n2 > n1){
        return false;
    }
    if (n2 == 0){
        return true;
    }
    int j = 0;
    for (int i = 0; i < n1 ; i++){
            if (a1[i] == a2[j]){
                j++;
                if (j == n2)
                    return true;
            }
    }
    return false;
}

// returns true if a is in non decreasing order
// returns false if a is not in non decreasing order
bool isNondecreasing (const string a[], int n){
    for (int i = 0; i < n-1 ; i++){
        if (a[i] > a[i+1]){
            return false;
        }
    }
    return true;
}

// places in result all the elements of a1 and a2, arranged in nondecreasing order
// returns the number of elements placed
// returns -1 if result would have more than max elements or if a1/a2 are not in nondecreasing order or if
// n1 or n2 are negative
int makeMerger(const string a1[], int n1, const string a2[], int n2, string result[], int max){
    if (n1 < 0 || n2 < 0)
        return -1;
    if ((n1 + n2) > max){
        return -1;
    }
    if (!(isNondecreasing(a1, n1)) || !(isNondecreasing(a2, n2))){
        return -1;
    }
    
    int i= 0;
    int j = 0;
    int k = 0;
    
    while (i < n1 && j < n2){
        if (a1[i] < a2[j] || a1[i] == a2[j]){
            result[k] = a1[i];
            k++;
            i++;
        }
        if (a2[j] < a1[i]){
            result[k] = a2[j];
            k++;
            j++;
        }
    }
    
    while (i < n1){
        result[k] = a1[i];
        k++;
        i++;
    }
    
    while (j < n2){
        result[k] = a2[j];
        k++;
        j++;
    }
    
    return (n1 + n2);
}

// rearranges array so the elements whose value is <divider come before all the other elements
// and all the elements >divider come after all the other elements
// returns the position of the first element that is not <divider, or n if there are no such elements
// returns -1 if n is negative
int divide(string a[], int n, string divider){
    if (n<0){
        return -1;
    }
    string temp = "";
    
    for (int i = 0; i < n; i++){
        for (int j = i+1; j < n; j++){
            if (a[i] > a[j]){
                temp = a[i];
                a[i] = a[j];
                a[j] = temp;
            }
        }
    }
    
    for (int i = 0; i < n; i++){
        if (!(a[i] < divider)){
            return i;
        }
    }
    
    return n;
}

int main() {
//    string a[6] = {
//        "red", "green", "purple", "yellow", "purple", ""
//    };
//    cout << enumerate(a, -3, "blue") << endl;  //-1
//    cout << enumerate(a, 0, "blue") << endl;   // 0
//    cout << enumerate(a, 6, "red") << endl;   // 1
//    cout << enumerate(a, 5, "purple") << endl;  // 2
//    cout << enumerate(a, 5, "") << endl; // 0
//    cout << enumerate(a, 6, "") << endl; // 1
//    cout << endl;
//
//    cout << findMatch(a, -5, "red") << endl; // -1
//    cout << findMatch(a, 0, "red") << endl;  // -1
//    cout << findMatch(a, 6, "red") << endl; // 0
//    cout << findMatch(a, 6, "") << endl; // 5
//    cout << findMatch(a, 6, "purple") << endl; // 2
//    cout << findMatch(a, 6, "blue") << endl; // -1
//    cout << endl;
//
//    string c[9] = {"green", "blue", "red", "red", "pink", "pink", "pink", "red", "red"};
//    int b = 0;
//    int e = 2;
//
//
//    cout << findRun(c, -3, "red", b, e) <<  b << e << endl; //002
//    cout << findRun(c, 0, "red", b, e) <<  b << e << endl; //002
//    cout << findRun(c, 3, "blue", b, e) <<  b << e << endl; //111
//    cout << findRun(c, 9, "red", b, e) <<  b << e << endl; //123
//    cout << findRun(c, 9, "violet", b, e) <<  b << e << endl; //023
//    cout << endl;
//
//    string d[9] = {"green", "blue", "red", "blue", "pink", "pink", "pink", "red", "red"};
//    cout << findMin(d, -3) << endl; // -1
//    cout << findMin(d, 0) << endl; // -1
//    cout << findMin(d, 3) << endl; // 1
//    cout << findMin(d, 4) << endl; // 1
//    cout << endl;
//
//    cout << moveToEnd(d, -3, 0) << endl; // -1
//    for (int i =0; i< 9; i++){  // green, blue, red, blue, pink, pink, pink, red, red,
//        cout << d[i] << ", ";
//    }
//    cout << endl;
//    cout << moveToEnd(d, 2, -3) << endl; //-1
//    for (int i =0; i< 9; i++){  // green, blue, red, blue, pink, pink, pink, red, red,
//        cout << d[i] << ", ";
//    }
//    cout << endl;
//    cout << moveToEnd(d, 3, 3) << endl; //-1
//    for (int i =0; i< 9; i++){   // green, blue, red, blue, pink, pink, pink, red, red,
//        cout << d[i] << ", ";
//    }
//    cout << endl;
//    cout << moveToEnd(d, 3, 0) << endl; //0
//    for (int i =0; i< 9; i++){ // blue, red, green, blue, pink, pink, pink, red, red,
//        cout << d[i] << ", ";
//    }
//    cout << endl;
//    cout << moveToEnd(d, 0, 0) << endl;  //-1
//    for (int i =0; i< 9; i++){  // blue, red, green, blue, pink, pink, pink, red, red,
//        cout << d[i] << ", ";
//    }
//    cout << endl;
//    cout << moveToEnd(d, 6, 5) << endl; // 5
//    for (int i =0; i< 9; i++){  // blue, red, green, blue, pink, pink, pink, red, red,
//        cout << d[i] << ", ";
//    }
//    cout << endl;
//    cout << moveToEnd(d, 9, 0) << endl; //0
//    for (int i =0; i< 9; i++){ // red, green, blue, pink, pink, pink, red, red, blue,
//        cout << d[i] << ", ";
//    }
//    cout << endl;
//    cout << moveToEnd(d, 9, 3) << endl; //3
//    for (int i =0; i< 9; i++){ //red, green, blue, pink, pink, red, red, blue, pink,
//        cout << d[i] << ", ";
//    }
//    cout << endl;
//    cout << endl;
//
//    cout << moveToBeginning(d, -3, 0) << endl; // -1
//    for (int i =0; i< 9; i++){  // red, green, blue, pink, pink, red, red, blue, pink,
//        cout << d[i] << ", ";
//    }
//    cout << endl;
//    cout << moveToBeginning(d, 2, -3) << endl; //-1
//    for (int i =0; i< 9; i++){  // red, green, blue, pink, pink, red, red, blue, pink,
//        cout << d[i] << ", ";
//    }
//    cout << endl;
//    cout << moveToBeginning(d, 3, 3) << endl; //-1
//    for (int i =0; i< 9; i++){   // red, green, blue, pink, pink, red, red, blue, pink,
//        cout << d[i] << ", ";
//    }
//    cout << endl;
//    cout << moveToBeginning(d, 3, 0) << endl; //0
//    for (int i =0; i< 9; i++){ //red, green, blue, pink, pink, red, red, blue, pink,
//        cout << d[i] << ", ";
//    }
//    cout << endl;
//    cout << moveToBeginning(d, 0, 0) << endl;  //-1
//    for (int i =0; i< 9; i++){  // red, green, blue, pink, pink, red, red, blue, pink,
//        cout << d[i] << ", ";
//    }
//    cout << endl;
//    cout << moveToBeginning(d, 6, 5) << endl; // 5
//    for (int i =0; i< 9; i++){  // red, red, green, blue, pink, pink, red, blue, pink,
//        cout << d[i] << ", ";
//    }
//    cout << endl;
//    cout << moveToBeginning(d, 9, 0) << endl; //0
//    for (int i =0; i< 9; i++){ // red, red, green, blue, pink, pink, red, blue, pink,
//        cout << d[i] << ", ";
//    }
//    cout << endl;
//    cout << moveToBeginning(d, 9, 3) << endl; //3
//    for (int i =0; i< 9; i++){ //red, green, blue, pink, pink, red, red, blue, pink,
//        cout << d[i] << ", ";
//    }
//    cout << endl;
//    cout << endl;
//
//    string a1[4] = {"green", "red", "blue", "purple"};
//    string a2[4] = {"green", "red", "blue", "yellow"};
//
//    cout << findDifference(a1, -3, a2, 3) << endl; //-1
//    cout << findDifference(a1, 3, a2, -3) << endl; //-1
//    cout << findDifference(a1, 0, a2, 3) << endl; //0
//    cout << findDifference(a1, 3, a2, 0) << endl; // 0
//    cout << findDifference(a1, 0, a2, 0) << endl; // 0
//    cout << findDifference(a1, 3, a2, 3) << endl; // 3
//    cout << findDifference(a1, 4, a2, 3) << endl; // 3
//    cout << findDifference(a1, 3, a2, 4) << endl; // 3
//    cout << findDifference(a1, 4, a2, 4) << endl; // 3
//    cout << endl;
//
//    string f[11] = {"red", "green", "blue", "purple", "purple", "red", "red", "red", "blue", "green", "green"};
//    cout << removeDups(f, -3) << endl; //-1
//    for (int i =0; i< 11; i++){  // "red", "green", "blue", "purple", "purple", "red", "red", "red", "blue", "green", "green"
//        cout << f[i] << ", ";
//    }
//    cout << endl;
//    string g[11] = {"red", "green", "blue", "purple", "purple", "red", "red", "red", "blue", "green", "green"};
//    cout << removeDups(g, 0) << endl; //0
//    for (int i =0; i< 11; i++){  // "red", "green", "blue", "purple", "purple", "red", "red", "red", "blue", "green", "green"
//        cout << g[i] << ", ";
//    }
//    cout << endl;
//    string h[11] = {"red", "green", "blue", "purple", "purple", "red", "red", "red", "blue", "green", "green"};
//    cout << removeDups(h, 4) << endl;
//    for (int i =0; i< 11; i++){  // red, green, blue, purple, purple, red, red, red, blue, green, green,
//        cout << h[i] << ", ";
//    }
//    cout << endl;
//    string j[11] = {"red", "green", "blue", "purple", "purple", "red", "red", "red", "blue", "green", "green"};
//    cout << removeDups(j, 8) << endl; // 5
//    for (int i =0; i< 11; i++){  // red, green, blue, purple, red, red, red, red, blue, green, green,
//    }
//    cout << endl;
//    string k[11] = {"red", "green", "blue", "purple", "purple", "red", "red", "red", "blue", "green", "green"};
//    cout << removeDups(k, 11) << endl; // 7
//    for (int i =0; i< 11; i++){  // red, green, blue, purple, red, blue, green, red, blue, green, green,
//        cout << k[i] << ", ";
//    }
//    cout << endl;
//    cout << endl;
//
//    string big[10] = { "elena", "john", "amy", "ketanji", "neil", "amy" };
//string little1[10] = { "john", "ketanji", "neil" };
//string little2[10] = { "amy", "john" };
//string little3[10] = { "john", "amy", "amy" };
//string little4[10] = { "john", "john", "amy" };
//
//    cout << subsequence(big, 0, little4, 3) << endl; // 0
//    cout << subsequence(big, 3, little4, 0) << endl; // 1
//    cout << subsequence(big, 0, little4, 0) << endl; // 1
//    cout << subsequence(big, 6, little1, 3) << endl; // 1
//    cout << subsequence(big, 6, little2, 2) << endl; // 0
//    cout << subsequence(big, 6, little3, 3) << endl; // 1
//    cout << subsequence(big, 6, little4, 3) << endl; //0
//    cout << endl;
//
//    string s1[3] = {"c", "b" , "a"};
//    string s2[3] = {"a", "a", "b"};
//    string s3[3] = {"b", "b", "c"};
//    string z[6] = { };
//
//    cout << makeMerger(s1, 3, s2, 3, z, 6) << endl;
//    for (int i =0; i< 6; i++){ //-1
//        cout << z[i] << ", "; // , , , , , ,
//    }
//    cout << endl;
//    cout << makeMerger(s2, 3, s1, 3, z, 6) << endl; // -1
//    for (int i =0; i< 6; i++){ // , , , , , ,
//        cout << z[i] << ", ";
//    }
//    cout << endl;
//    cout << makeMerger(s2, 3, s3, 3, z, 5) << endl; // -1
//    for (int i =0; i< 6; i++){ // , , , , , ,
//        cout << z[i] << ", ";
//    }
//    cout << endl;
//    cout << makeMerger(s2, -2, s3, -3, z, 6) << endl;
//    for (int i =0; i< 6; i++){
//        cout << z[i] << ", ";
//    }
//    cout << endl;
//    cout << makeMerger(s2, 3, s3, -3, z, 6) << endl;
//    for (int i =0; i< 6; i++){
//        cout << z[i] << ", ";
//    }
//    cout << endl;
//    cout << makeMerger(s2, 0, s3, 3, z, 6) << endl; // 3
//    for (int i =0; i< 6; i++){ // b, b, c, , , ,
//        cout << z[i] << ", ";
//    }
//    cout << endl;
//    cout << makeMerger(s2, 3, s3, 0, z, 6) << endl; // 3
//    for (int i =0; i< 6; i++){ // a, a, b, , , ,
//        cout << z[i] << ", ";
//    }
//    cout << endl;
//    cout << makeMerger(s2, 0, s3, 0, z, 0) << endl; // 0
//    for (int i =0; i< 6; i++){// a, a, b, , , ,
//        cout << z[i] << ", ";
//    }
//    cout << endl;
//    cout << makeMerger(s2, 3, s3, 3, z, 6) << endl;  // 6
//    for (int i =0; i< 6; i++){ // a, a, b, b, b, c,
//        cout << z[i] << ", ";
//    }
//    cout << endl;
//    cout << endl;
//
//    string r[5] = {"a", "c", "d", "b", "b"};
//    string r2[5] = {"e", "f", "q", "b", "i"};
//    string mTest = "m";
//    string aTest = "a";
//    string bTest = "b";
//    string gTest = "g";
//
//    cout << divide(r, 5, mTest) << endl; // 5
//    for (int i =0; i< 5; i++){ //a, b, b, c, d,
//        cout << r[i] << ", ";
//    }
//    cout << endl;
//    cout << divide(r2, 5, aTest) << endl;
//    for (int i =0; i< 5; i++){ //0
//        cout << r2[i] << ", "; // b, e, f, i, q,
//    }
//    cout << endl;
//    string r3[5] = {"a", "c", "d", "b", "b"};
//    cout << divide(r3, 5, bTest) << endl;
//    for (int i =0; i< 5; i++){ // 1
//        cout << r3[i] << ", "; // a, b, b, c, d,
//    }
//    cout << endl;
//    string r4[5] = {"e", "f", "q", "b", "i"};
//    cout << divide(r4, 5, gTest) << endl; // 3
//    for (int i =0; i< 5; i++){// b, e, f, i, q,
//        cout << r4[i] << ", ";
//    }
//    cout << endl;
//    cout << endl;
    
    string h[7] = { "neil", "sonia", "john", "amy", "", "elena", "john" };
           assert(enumerate(h, 7, "john") == 2);
           assert(enumerate(h, 7, "") == 1);
           assert(enumerate(h, 7, "brett") == 0);
           assert(enumerate(h, 0, "john") == 0);
           assert(findMatch(h, 7, "john") == 2);
           assert(findMatch(h, 2, "john") == -1);
           int bg;
           int en;
           assert(findRun(h, 7, "amy", bg, en) && bg == 3 && en == 3);

           string g[4] = { "neil", "sonia", "amy", "elena" };
           assert(findMin(g, 4) == 2);
           assert(findDifference(h, 4, g, 4) == 2);
           assert(subsequence(h, 7, g, 4));
           assert(moveToEnd(g, 4, 1) == 1 && g[1] == "amy" && g[3] == "sonia");
       
           string f[4] = { "elena", "amy", "sonia", "john" };
           assert(moveToBeginning(f, 4, 2) == 2 && f[0] == "sonia" && f[2] == "amy");
       
           string e[5] = { "elena", "elena", "elena", "sonia", "sonia" };
           assert(removeDups(e, 5) == 2 && e[1] == "sonia");
       
           string x[4] = { "john", "john", "samuel", "sonia" };
           string y[4] = { "amy", "elena", "john", "ketanji" };
           string z[10];
           assert(makeMerger(x, 4, y, 4, z, 10) == 8 && z[5] == "ketanji");
       
           assert(divide(h, 7, "john") == 3);

           cout << "All tests succeeded" << endl;
    
    return 0;
}
