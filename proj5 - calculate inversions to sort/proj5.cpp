/**

*proj5.cpp

*Academic Integrity Statement: I certify that, while others may have assisted me
in brain storming, debugging and validating this program, the program itself is
my own work. I understand that submitting code which is the work of other
individuals is a violation of the course Academic Integrity Policy and may
result in a zero credit for the assignment, or course failure and a report to
the Academic Dishonesty Board. I also understand that if I knowingly give my
original work to another individual that it could also result in a zero credit
for the assignment, or course failure and a report to the Academic Dishonesty
Board. See Academic Integrity Procedural GuidelinesLinks to an external site.
at:
https://psbehrend.psu.edu/intranet/faculty-resources/academic-integrity/academic-integrity-procedural-guidelinesLinks
to an external site.

*Assisted by and Assisted line numbers:


*Your Name: Dominic Cronauer

*Your PSU user ID:  Dlc5994

*CMPSC465 Summer 2024

*Due Time: 11:59PM, Sunday, 7/7, 2024

*Time of Last Modification: 11:40PM, Sunday, 7/7, 2024

*Description:
Progam to calculate the number of inversions it takes to sort a given list of numbers. It can sort multiple lists of numbers at a time


*/
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

/**
 * Merges two sorted subarrays and counts inversions.
 * @param arr The main array. (passed in by reference)
 * @param temp Temporary array to assist in merging.
 * @param left Left index of the subarray.
 * @param mid Middle index of the subarray.
 * @param right Right index of the subarray.
 * @return Number of inversions in this merge step.
 */
long long merge(vector<int> &arr, vector<int> &temp, int left, int mid, int right) {
  int i = left;
  int j = mid+1;
  int k = left;
  long long inv_count = 0;

  while (i <= mid && j <= right) {
    if (arr[i] <= arr[j])
      temp[k++] = arr[i++];
    else {
      temp[k++] = arr[j++];
      inv_count += mid-i+1;
    }
  }

  while (i <= mid)
    temp[k++] = arr[i++];

  while (j <= right)
    temp[k++] = arr[j++];

  for (i = left; i <= right; i++)
    arr[i] = temp[i];

  return inv_count;
}
/**
 * Recursive function to perform merge sort and count inversions.
 * @param arr The array to be sorted.
 * @param temp Temporary array to assist in merging.
 * @param left Left index of the current subarray.
 * @param right Right index of the current subarray.
 * @return Total number of inversions in the current subarray.
 */
long long mergeSort(vector<int> &arr, vector<int> &temp, int left, int right) {
  long long inv_count = 0;
  if (left < right) {
    int mid = left + (right - left) / 2;
    inv_count += mergeSort(arr, temp, left, mid);
    inv_count += mergeSort(arr, temp, mid + 1, right);
    inv_count += merge(arr, temp, left, mid, right);
  }
  return inv_count;
}
/**
 * Counts the total number of inversions in the given array.
 * @param arr The input array.
 * @return Total number of inversions in the array.
 */
long long countInversions(vector<int> &arr) {
  vector<int> temp(arr.size());
  return mergeSort(arr, temp, 0, arr.size() - 1);
}
/**
 * Main function to read input from proj4in.txt, process the data, and write the
 * output to console
 * @return int Exit status
 */
int main() {
  ifstream infile("proj5in.txt");
  if (!infile.is_open()) { //check for file
    cerr << "Error opening input file" << endl;
    return 1;
  }

  int numTestCases;
  infile >> numTestCases;
  infile.ignore(); //consume newline

  for (int i = 0; i < numTestCases; i++) {
    string line;
    getline(infile, line);
    istringstream iss(line); //livesaver
    vector<int> sequence;
    int num;
    while (iss >> num) {
      sequence.push_back(num);
    }

    long long inversions = countInversions(sequence);
    cout << "The sequence has " << inversions << " inversions." << endl;
  }

  infile.close();
  return 0;
}


/*SAMPLE OUTPUT
--Input1:
  3
  2 4 1 3 5
  1 2 4 8 9 3 5 6
  1 20 6 4 5
  5 4 3 2 1
  21 24 55 32 1 2 5 67
--Output1:
  The sequence has 3 inversions.
  The sequence has 7 inversions.
  The sequence has 5 inversions.
  The sequence has 10 inversions.
  The sequence has 13 inversions.

*/