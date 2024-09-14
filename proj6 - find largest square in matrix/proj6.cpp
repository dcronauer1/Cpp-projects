/**

*proj6.cpp

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

*Due Time: 11:59PM, Sunday, 7/14, 2024

*Time of Last Modification: 4:50PM, Wednesday, 7/10, 2024

*Description:
program to find the largest square containing all 1s in a matrix using dynamic
programming. Space and time efficency per matrix is O(n*m). Could have a space
efficency of O(m) but I'm lazy.
*/
#include <algorithm>
#include <fstream>
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

/**
 * Function to find the largest square of 1's in a matrix
 * @param infile
 * @param n rows
 * @param m columns
 * @return max area of 1's in matrix. if -1 then error
 */
int largestArea(ifstream &infile, int n, int m) {
  int maxSide = 0;
  // create the matrix
  vector<vector<int>> data(n, vector<int>(m, 0));
  int temp;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      infile >> temp;

      if (temp == 1) {
        if (i == 0 || j == 0) { // first row or column
          data[i][j] = 1;
        } else { // dynamically count
          data[i][j] =
              min({data[i - 1][j], data[i][j - 1], data[i - 1][j - 1]}) + 1;
        }
        maxSide = max(maxSide, data[i][j]); // update maxSide
      }

      else if (temp == 0) // 0 so its always a 0
        data[i][j] = 0;

      else {
        cout << "Invalid Entry (row,c):" << i + 1 << "," << j + 1;
        return -1; // end program execution
      }
    }
  }
  return maxSide * maxSide;
}

/**
 * Main function to read input from labin.txt and process data
 * @return int Exit status
 */
int main() {
  ifstream infile("input.txt"); // open input file
  if (!infile) {
    cerr << "Error opening the file." << endl;
    return 1;
  }

  int n = 0, m = 0;
  // runs until size 0 or end of file.
  while (infile >> n) {
    infile >> m;
    // check for invalid size
    if (n <= 0 || m <= 0) {
      // not "invalid" because input is supposed to end with 0
      cout << "Size 0, ending program";
      infile.close(); // close input file
      return 0;       // end program, either at end or bad size (gigo)
    }
    // reusing m here, can't cause problems
    m = largestArea(infile, n, m);
    if (m < 0)
      break; // end program, invalid entry
    cout << "Max Area: " << m << endl;
  }

  infile.close(); // close input file
  return 0;
}

/* Sample Output
--Input:
4 5
1 0 1 0 0
1 0 1 1 1
1 1 1 1 1
1 0 0 1 0

5 7
1 0 1 0 0 1 1
1 0 1 1 1 1 1
1 1 1 1 1 0 1
1 0 1 1 1 0 1
1 0 1 0 1 0 1

10 7
1 0 1 0 0 1 1
1 0 1 1 1 1 1
0 1 1 1 1 0 1
1 0 1 1 1 1 1
1 0 1 1 1 1 1
1 1 1 0 0 1 1
1 0 1 1 1 1 1
0 1 1 1 1 0 1
1 0 1 1 1 0 1
1 0 1 0 1 0 1

10 10
1 0 1 0 0 1 1 1 0 1
1 0 1 1 0 1 1 1 0 1
1 0 1 1 1 1 1 1 0 1
1 0 1 1 1 1 1 1 0 1
1 0 1 1 1 1 1 1 0 1
1 0 1 1 1 1 1 1 0 1
1 0 1 0 0 1 1 1 0 1
1 0 1 0 0 1 1 1 0 1
1 0 1 0 0 1 1 1 0 1
1 0 1 0 0 1 1 1 0 1

10 10
1 0 1 0 0 1 1 1 0 1
1 0 1 1 1 1 1 1 0 1
1 0 1 1 1 1 1 1 0 1
1 0 1 1 1 1 1 1 0 1
1 0 1 1 1 1 1 1 0 1
1 0 1 1 1 1 1 1 0 1
1 0 1 0 0 1 1 1 0 1
1 0 1 0 0 1 1 1 0 1
1 0 1 0 0 1 1 1 0 1
1 0 1 0 0 1 1 1 0 1

0
--Output:
Max Area: 4
Max Area: 9
Max Area: 9
Max Area: 16
Max Area: 25
Size 0, ending program

--Input 2:
4 5
1 0 1 0 0
1 0 1 1 1
1 1 1 1 1
1 0 0 1 0

5 7
1 0 1 0 0 1 1
1 0 1 3 1 1 1
1 1 1 1 1 0 1
1 0 1 1 1 0 1
1 0 1 0 1 0 1

0
--Output 2:
Max Area: 4
Invalid Entry (row,c):2,4

--Input 3:
3 3
1 1 1
1 1 1
1 1 0
--Output 3:
Max Area: 4

*/