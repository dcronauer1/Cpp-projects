/**

*proj2.cpp

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

*Due Time: 11:59PM, Sunday, 6/09, 2024

*Time of Last Modification: 6:00PM, Monday, 6/3, 2024

*Description:
Program takes in a user input of n parenthesis pairs, and outputs all possible pairs of valid parenthesis combinations.
*/
#include <iostream>
#include <vector>
#include <math.h>

using namespace std;


/**
 * This function recursively generates all valid combinations of parentheses for a given number of pairs. Each starting combination will be generated (such as "((..."), and checked if more open or closed paranthesis can be added. if more can be, it will call itself and repeat the check. After that it will terminate itself.
 *
 * @param n The number of parenthesis pairs
 * @param open The number of open parenthesis added so far
 * @param close The number of close parenthesis added so far
 * @param current The current string being processed
 * @param result The vector to store the valid combinations, passed by reference
 */
void generateParenthesis(int n, int open, int close, string current, vector<string>& result) {
    
    // If the current string has reached the maximum length, add it to the result
    if (current.length() == 2 * n) {
        result.push_back(current);
        return;
    }

    // If an open parenthesis can be added, add it and recurse.
    if (open < n) {
        generateParenthesis(n, open + 1, close, current + '(', result);
    }

    // If a close parenthesis can be added, add it and recurse
    if (close < open) {
        generateParenthesis(n, open, close + 1, current + ')', result);
    }
    // If a recursive call reaches the end, then no more valid combinations could be made from that current combination. ie recursive calls are self terminating
}

/**
 * This function initializes the generation of all valid combinations of parentheses for a given number of pairs by calling the recursive 'generateParenthesis' function.
 *
 * @param n The number of parenthesis pairs
 * @return A vector containing all valid combinations of parentheses
 */
vector<string> generateParenthesisInitializer(int n) {
    vector<string> result;
    generateParenthesis(n, 0, 0, "", result);
    return result;
}

/**
 * This function takes user input for the number of parenthesis pairs and generates all possible valid combinations of parentheses.
 * @return int Exit status
 */
int main() {
    int n;
    cout << "Enter number of pairs: ";
    cin >> n;
    vector<string> result = generateParenthesisInitializer(n);

    for (const string& combination : result) {

        cout << combination << endl; //output result
    }
    return 0;
}

/* Sample Outputs
--Output1:
Enter number of pairs: 3
((()))
(()())
(())()
()(())
()()()

--Output2:
Enter number of pairs: 2
(())
()()

--Output3:
Enter number of pairs: 4
(((())))
((()()))
((())())
((()))()
(()(()))
(()()())
(()())()
(())(())
(())()()
()((()))
()(()())
()(())()
()()(())
()()()()


*/