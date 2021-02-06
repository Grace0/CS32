//
//  linear.cpp
//  homework3
//
//  Created by Grace Kwak on 2/4/21.
//

#include <iostream>
#include <cassert>

using namespace std;

bool somePredicate(double x) {
    return x > 10;
}

// Return true if the somePredicate function returns true for at
// least one of the array elements, false otherwise.
bool anyTrue(const double a[], int n)
{
    
    if (n <= 0) { //don't need to do recursion if there's no elements in the arr
        return false;
    }
    
    //goes backwards
    if (somePredicate(a[n-1])) {
        return true;
    }
    
    if (n == 1) { //we haven't found any
        return false;
    }
    
    return anyTrue(a, n-1);
}

// Return the number of elements in the array for which the
// somePredicate function returns true.
int countTrue(const double a[], int n)
{
    if (n == 0) {
        return 0;
    }
    if (n == 1) {
        return somePredicate(a[0]); //returning a bool as an int will give 0 or 1
    }
    
    int first = countTrue(a, n/2);
    int second = countTrue(a+n/2, n-n/2);
    return first + second;
}

// Return the subscript of the first element in the array for which
// the somePredicate function returns true.  If there is no such
// element, return -1.
int firstTrue(const double a[], int n)
{
  return -999;  // This is incorrect.
}

// Return the subscript of the largest element in the array (i.e.,
// return the smallest subscript m such that a[m] >= a[k] for all
// k from 0 to n-1).  If the function is told to examine no
// elements, return -1.
int positionOfMax(const double a[], int n)
{
  return -999;  // This is incorrect.
}

// If all n1 elements of a1 appear in the n2 element array a2, in
// the same order (though not necessarily consecutively), then
// return true; otherwise (i.e., if the array a1 is not a
// not-necessarily-contiguous subsequence of a2), return false.
// (Of course, if a1 is empty (i.e., n1 is 0), return true.)
// For example, if a2 is the 7 element array
//    10 50 40 20 50 40 30
// then the function should return true if a1 is
//    50 20 30
// or
//    50 40 40
// and it should return false if a1 is
//    50 30 20
// or
//    10 20 20
bool isIn(const double a1[], int n1, const double a2[], int n2)
{
  return false;  // This is not always correct.
}

int main() {
   
    const double arr[10] = { 3.4, 0.0, -4.0, 20.338, 5.987, 599.9, 6.0, 8.0, 10.9, -4987};
    int n = 10;
    
    assert(anyTrue(arr, n) == true);
    assert(anyTrue(arr, 3) == false);
    
    assert(countTrue(arr, 3) == 0);
    assert(countTrue(arr, 7) == 2);
    assert(countTrue(arr, 4) == 1);
    cout << "Passed all tests" << endl;
    
}
