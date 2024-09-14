/**

*proj4.cpp

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

*Due Time: 11:59PM, Sunday, 6/30, 2024

*Time of Last Modification: 11:40PM, Sunday, 6/30, 2024

*Description:
Progam uses a BFS approach to calculate the minimum number of chess knight moves it takes to go from one point to another, on a grid spanning a-h horizontally and 8-1 vertically.

*/
#include <iostream>
#include <fstream>
#include <queue>
#include <unordered_map>
#include <vector>
#include <string>

using namespace std;

/**
 * Structure to store a position on the chessboard
 */
struct Position {
  int x, y;
  Position(int x = 0, int y = 0) : x(x), y(y) {}
};

/**
 * Function to convert a chessboard position in algebraic notation to Position
 * @param pos - a string representing a chessboard position in algebraic notation
 * @return - a Position object representing the chessboard position
 */
Position algebraicToPosition(const string &pos) {
  return Position(pos[0] - 'a', pos[1] - '1');
}
/**
 * Function to check if a position is inside the chessboard
 * @param pos - position to check
 * @return true if position is inside the chessboard, false otherwise
*/
bool isInsideBoard(const Position &pos) {
  return pos.x >= 0 && pos.x < 8 && pos.y >= 0 && pos.y < 8;
}

/**
 * Function to find the minimum knight moves using BFS
 * @param start starting position
 * @param end ending position
 * @return minimum number of moves
*/
int minKnightMoves(const Position &start, const Position &end) {
  if (start.x == end.x && start.y == end.y) return 0;

  vector<Position> directions = {
    {2, 1}, {1, 2}, {-1, 2}, {-2, 1},{-2, -1}, {-1, -2}, {1, -2}, {2, -1}
  };

  queue<Position> q;
  unordered_map<int, unordered_map<int, bool>> visited;

  q.push(start);
  visited[start.x][start.y] = true;
  int moves = 0;

  while (!q.empty()) {
    int size = q.size();
    moves++;
    for (int i = 0; i < size; ++i) {
      Position current = q.front();
      q.pop();

      for (const auto &dir : directions) {
        Position next(current.x + dir.x, current.y + dir.y);
        if (next.x == end.x && next.y == end.y) 
          return moves;
        if (isInsideBoard(next) && !visited[next.x][next.y]) {
          q.push(next);
          visited[next.x][next.y] = true;
        }
      }//end for 2
    }//end for 1
  }//end while
  return -1; //Should never reach here for valid input
}
/**
 * Main function to read input from proj4in.txt, process the data, and write the output to console
 * @return int Exit status
 */
int main() {
  ifstream inputFile("proj4in.txt");
  if (!inputFile) {
    cerr << "Error opening the file." << endl;
    return 1;
  }

  vector<pair<string, string>> testCases;
  string start, end;

  //Read each line from the file
  while (inputFile >> start >> end) {
    testCases.emplace_back(start, end);
  }

  inputFile.close(); //Close the file after reading

  for (const auto &testCase : testCases) {
    Position startPos = algebraicToPosition(testCase.first);
    Position endPos = algebraicToPosition(testCase.second);
    int moves = minKnightMoves(startPos, endPos);
    cout << "To get from " << testCase.first << " to " << testCase.second << " takes " << moves << " knight moves." << endl;
  }

  return 0;
}

/* Sample Outputs
--Input 1:

e2 e4
a1 b2
b2 c3
a1 h8
a1 h7
h8 a1
b1 c3
f6 f6

--Output 1:
To get from e2 to e4 takes 2 knight moves.
To get from a1 to b2 takes 4 knight moves.
To get from b2 to c3 takes 2 knight moves.
To get from a1 to h8 takes 6 knight moves.
To get from a1 to h7 takes 5 knight moves.
To get from h8 to a1 takes 6 knight moves.
To get from b1 to c3 takes 1 knight moves.
To get from f6 to f6 takes 0 knight moves.

--Input 2:
d4 f5
g1 h3
h1 g3
c4 e5
b7 c5

--Output 2:
To get from d4 to f5 takes 1 knight moves.
To get from g1 to h3 takes 1 knight moves.
To get from h1 to g3 takes 1 knight moves.
To get from c4 to e5 takes 1 knight moves.
To get from b7 to c5 takes 1 knight moves.

--Input 2:
a8 h1

--Output 2:
To get from a8 to h1 takes 6 knight moves.
*/




