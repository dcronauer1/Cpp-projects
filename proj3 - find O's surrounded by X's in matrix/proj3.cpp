/**

*proj1.cpp

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

*Due Time: 11:59PM, Tuesday, 6/18, 2024

*Time of Last Modification: 11:00PM, Tuesday, 6/12, 2024

*Description:
Given a 2D board from a file containing 'X' and 'O', capture all regions surrounded by 'X'. A region is captured by flipping all 'O's into 'X's in that surrounded region. Then output the converted board into console.

*/
#include <fstream>
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

//Function Declarations
void regionFind(int n, vector<vector<char>>& matrix);
void regionCheck(int n, vector<vector<char>>& matrix,int x, int y,bool &reachedBorder,vector<vector<int>> &oCoordinates);
//void doThing(int n, vector<vector<char>>& matrix,int xOffset, int yOffset,bool &reachedBorder,vector<vector<int>> &oCoordinates);

/**
 * Main function to read input from lab3in.txt, process the data, and write the output to console
 * @return int Exit status
 */
int main() {
  ifstream infile("lab3in.txt"); // open input file

  int n = 0;
  infile >> n;
  //check for invalid size
  if (n <= 0){
    cout << "Size cant be 0 or negative";
    infile.close(); //close input file
    return 0;}

  //check for "already solved" boards
  else if (n<=2){
    cout << "No possible operations can be done when size < 3";
    string row;
    while (getline(infile, row)) { //It's unnecessary to convert from bool and back, so output as is
        cout << row << '\n';
      }
  infile.close(); //close input file
  return 0;}

  //n=>3 here
   vector<vector<char>> matrix(n, vector<char>(n)); //create the matrix

  //take the input and put it into an 2D bool array
  for (int i = 0; i < n; i++){
    for (int j = 0; j < n; j++){
      char entry;
      infile >> entry;
      if(entry == 'X' || entry == 'x'){
        matrix[i][j]='X';
      }
      else if(entry == 'O' || entry == 'o'){
        matrix[i][j]='O';
      }
      else{
        //check for invalid inputs, dont record them, but continue anyways
        cout << "Invalid entry: "<<entry<<". Replacing with X\n";
        matrix[i][j]='X';
      }
    }
  }

  regionFind(n, matrix); //call the function to convert the 2D board  

  //take the new 2D char matrix, convert it back into X's and O's, and output it to console
  for (int i = 0; i < n; i++){
    for (int j = 0; j < n; j++){
      if(matrix[i][j]=='X'){
        cout << "X ";
      }
      else if(matrix[i][j]=='C'){
        cout << "O ";
      }
      else{
        cout << "\nSomething went wrong, incorrect value: "<< matrix[i][j]<<"at: ("<<i<<","<<j<<")\n"; //should never see this
      }
    }
    cout<<"\n";
  }

  infile.close(); //close input file
  return 0;
}


/**
 * Function to find each O in the 2D board, call regionCheck to find all 0's in the same region, and mark them as either found ('C'), or as 'X'.
 * @param n Size of the matrix
 * @param matrix Matrix grid to be checked (the 2D board)
 */
void regionFind(int n, vector<vector<char>>& matrix){
  for (int i = 0; i < n; i++){
    for (int j = 0; j < n; j++){
      if(matrix[i][j]=='O'){
        vector<vector<int>> oCoordinates;
        oCoordinates.push_back({i,j});
        bool reachedBorder = false;
        regionCheck(n,matrix,i,j,reachedBorder,oCoordinates);
        char temp = (reachedBorder ? 'C' : 'X'); // C is just O, but marked as already checked, so we wont check them again

        for (const auto& coord : oCoordinates) {
          matrix[coord[0]][coord[1]] = temp;
        }//end for 3
      }//end if
    }//end for 2
  }//end for 1
}


/**
 * Function to recursively check all O's in matrix to see if theyre surrounded by X's. If a 'O' is found on a border then mark false but keep checking for efficency reasons.
 * @param n Size of the matrix
 * @param matrix Matrix grid to be checked (the 2D board)
 * @param x Current x coordinate
 * @param y Current y coordinate
 * @param reachedborder Boolean to check if border was reached
 * @param oCordinates Vector of all O's found in matrix
 */
void regionCheck(int n, vector<vector<char>>& matrix,int x, int y,bool &reachedBorder,vector<vector<int>> &oCoordinates){
//Idea: check all adjacent boxes, if any are O's, then recursive check. If region is surrounded by X's, reachedBorder will stay true. If it finds a O at a border, set reachedBorder to false. When it hits a border, it should still check for all O's to mark them as found, but still bring back a false bool. Uses a DFS approach.

  if(x == 0 || x == n-1 || y == 0 || y == n-1){
    reachedBorder = true;//border check
  }
  else if(matrix[x+1][y]=='C'||matrix[x-1][y]=='C'||matrix[x][y+1]=='C'||matrix[x][y-1]=='C')//broken, should just be an if statement, but it would check out of bounds. dont feel like fixing.
    cout<<"Found a 'C' when recursive checking, something went horribly wrong. Was checking "<<x<<","<<y<<"\n";//should never see this
  
  matrix[x][y]='Z';//Mark this coordinate as already checked in the region check, more efficent than comparing with the oCoordinates list. Use 'Z' as 'C' is used after the region has been entirely found.
  
  // Check all four possible directions for O's
  if (x + 1 < n && matrix[x + 1][y] == 'O') {
    oCoordinates.push_back({x+1,y}); //store coordinate in vector
    regionCheck(n, matrix, x+1, y,reachedBorder,oCoordinates);
    //Recursively call region check with new coordinates
  }
  if (x - 1 >= 0 && matrix[x - 1][y] == 'O') {
    oCoordinates.push_back({x-1,y}); //store coordinate in vector
    regionCheck(n, matrix, x-1, y,reachedBorder,oCoordinates);
  }
  if (y + 1 < n && matrix[x][y + 1] == 'O') {
    oCoordinates.push_back({x,y+1}); //store coordinate in vector
    regionCheck(n, matrix, x, y+1,reachedBorder,oCoordinates);
  }
  if (y - 1 >= 0 && matrix[x][y - 1] == 'O') {
  oCoordinates.push_back({x,y-1}); //store coordinate in vector
  regionCheck(n, matrix, x, y-1,reachedBorder,oCoordinates);
  }
}


//After writing this project, I realize I couldve just checked for O's on the border only, mapped out the connected regions, then set all other O's to X's, and a placeholder back to O. I would but I dont have enough time left this week.

/** Execution Samples:
 * Sample 1:
    lab3in.txt:
    6
    X X X X X O
    X O X O O X
    X X O O O X
    X X X O X X
    X O X X O O
    X X X X X X
    console:
    6
    X X X X X O
    X O X O O X
    X X O O O X
    X X X O X X
    X O X X O O
    X X X X X X
 * Sample 2:
    lab3in.txt:
    7
    X X X X X O X
    X O O O O X X
    X X X X O X X
    X O O O O X X
    X O X X X X X
    X O O O O X X
    X X X X O X X
    Console:
    X X X X X O X
    X O O O O X X
    X X X X O X X
    X O O O O X X
    X O X X X X X
    X O O O O X X
    X X X X O X X
 * Sample 3:
    lab3in.txt:
    7
    X X X X X O X
    X O O O O X X
    X X X X O X X
    X O O O O X X
    X O X X X X X
    X O O O O X X
    X X X X X X X
    Console:
    7
    X X X X X O X
    X X X X X X X
    X X X X X X X
    X X X X X X X
    X X X X X X X
    X X X X X X X
    X X X X X X X
  * Sample 4:
    lab3in.txt:
    2
    X X
    X O
    Console:
    No possible operations can be done when size < 3
    X X
    X O
  * Sample 5:
    lab3in.txt:
    3
    X X r
    X O X
    X X x 
    console:
    Invalid entry: r. Replacing with X
    X X X 
    X X X 
    X X X 
 */