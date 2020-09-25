/*
    Finnick Lakeotes, 5004855838, Assignment 11
    To explore and use recursion with examples
    Input: simple input file
    Output: display of found data
*/

#include <iostream>
using namespace std;
//CS 202 AST 11
//Skeleton program by Jorge Fonseca
bool elementPresent(int[], int, int);
void reverseDisplay(int);
void reverse(int[], int, int);
bool isPalindrome(int[], int, int);
void printArray(int[], int);

int main(int argc, char* argv[]) {
  int n, x, y;
  cin >> n;
  int *a;
  a = new int[n];
  for(int i=0;i<n;i++) cin >> a[i];
  cin >> x;
  cin >> y;
  cout << n << " Integer Array:\n";
  printArray(a,n);
  cout << "\nReverse of Given Array:" << endl;
  reverse(a, 0, n);
  printArray(a,n);
  cout << "\n\nis " << x << " present in given array?\n";
  if(elementPresent(a, n, x)) cout << "Aye, Aye Captain!\n";
  else cout << "That's a negative, Captain!\n";
  cout << "\nGiven Integer is: " << y;
  cout << "\nReverse: ";
  reverseDisplay(y);
  cout << "\n\nIs given array a palindrome?\n";
  if(isPalindrome(a, 0, n)) cout << "Afirmative, Captain!\n";
  else cout << "Does not look like it, Captain!\n";
  cout << "\nIs 2 3 5 3 2 a palindrome?\n";
  int b[5] = { 2, 3, 5, 3, 2};
  if(isPalindrome(b, 0, 5)) cout << "Afirmative, Captain!";
  else cout << "Does not look like it, Captain!";
  cout << endl;
  return 0;
}
void printArray(int a[], int n) {
  if(n > 0) {
    printArray(a, n-1); //tail
    cout << a[n-1] << " "; //head
  }
}

//Your Code Here (For all four functions)

/*
    elementPresent: checks to see if int is in array
    parameters: array, size, and int to search
    return value: true if found, false if not
*/
bool elementPresent(int a[], int n, int x){

    if(a[n] == x)
        return true;
        //returns as soon as found
    else{
        if(n == 0)
            return false;
            //if entire array is processed and not found, is false
        elementPresent(a, n-1, x);
        //recalls if entire array is not checked yet
    }
}

/*
    reverseDisplay: reverses int and displays
    parameters: int to process
    return value: none
*/
void reverseDisplay(int x){
  
    int ans = 0;
    //hold var

    ans = x%10;
    cout << ans;
    x -=ans;
    if(x == 0)
        return;
    //if no int left to process, returns
    x = x/10;
    reverseDisplay(x);
    //recalls if data left to process
}

/*
    reverse: reverses the indices in array
    parameters: array, start and endpoint
    return value: none
*/
void reverse(int a[], int left, int right){

    int hold = 0;

    if(right-1 <= left)
        return;
    else{
        hold = a[right-1];
        a[right-1] = a[left];
        a[left] = hold;
        right--;
        left++;
        reverse(a, left, right);
        //swaps, changes indices, then recalls
    }
}

/*
    isPalindrome: checks to see if arr is a palindrome    
    parameters: array, starting point and end point
    return value: true if palindrome, false if not
*/
bool isPalindrome(int a[], int left, int right){

    if(right-1 == left){
        if(a[right-1] == a[left])
            return true;
            //if all the way through, palindrome
    }

    if(a[right-1] == a[left]){
        right--;
        left++;
        isPalindrome(a, left, right);
        //changes points and recalls
    }
    else{
        //if not palindrome return false
        return false;
    }
}
