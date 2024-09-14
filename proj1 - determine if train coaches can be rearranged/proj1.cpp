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

*Due Time: 11:59PM, Sunday, 5/26, 2024

*Time of Last Modification: 11:40PM, Sunday, 5/26, 2024

*Description:
Program takes in a file with a ranging number of coaches at station A and
determines if the order of coaches can be arranged in order at station B, with a
stack in between. Different orders of the same length can be grouped into blocks
with eachother. The program will output "Yes" if the order is possible and "No"
if the order is not possible.

*/
#include <fstream>
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

/**
 * Function to check if it is possible to order the coaches in the
 * required order
 * @param permutation Vector representing the permutation of coach numbers
 * @return true if it is possible to order the coaches, false otherwise
 */
bool isPossibleToMarshal(vector<int> &permutation) {
  int permsize = permutation.size();

  int k = 0;
  vector<int> b;
  stack<int> s;
  int i = 1;

  // Simulating the train reorganization
  while (i <= permsize) {
    if (!s.empty() && s.top() == permutation[k]) {
      k++;
      b.push_back(s.top());
      s.pop();
      continue;
    }
    s.push(i++);
  }

  // Pop remaining coaches from the stack
  while (!s.empty()) {
    b.push_back(s.top());
    s.pop();
  }

  // Check if permutation matches forward order
  bool forwardOrder = true;
  for (int i = 0; i < permsize; ++i) {
    if (b[i] != permutation[i]) {
      forwardOrder = false;
      break;
    }
  }
  // Check if permutation matches backward order
  bool backwardOrder = true;
  for (int i = permsize - 1; i >= 0; --i) {
    if (b[i] != permutation[permsize - i - 1]) {
      backwardOrder = false;
      break;
    }
  }
  // return logic
  if (forwardOrder || backwardOrder) {
    return true;
  } else {
    return false;
  }
}

/**
 * Main function to read input from lab1in.txt, process the data, and write the output to lab1out.txt
 * @return int Exit status
 */
int main() {
  ifstream infile("lab1in.txt"); // open input and output files
  ofstream outfile("lab1out.txt");

    int n = 1;
    while (1) {
      infile >> n; // store the size(s) of the train
      if (n == 0) {
        break; // stop the program, all blocks checked (size cant be 0)
      }
      vector<int> a(n); //set vector size of block
  
    int start = 1;
    while (1) {
      infile >> start; //get the first coach number
      //cout << start << "\n"; //test code
      if (start == 0) { // stop the block
        outfile << "\n";
        break;
      }
      a[0] = start; // store the first coach number
      for (int i = 1; i < n; ++i) {
        infile >> a[i]; // store all other coach numbers from segment, stop when size n is reached
        //cout << a[i] << "\n"; //test code
      }

      if (isPossibleToMarshal(a)) { // Check if it's possible to order the coaches properly
        outfile << "Yes" << "\n";}
      else {outfile << "No" << "\n";}
    }
  }
  infile.close(); //close input and output files
  outfile.close();
  return 0;
}

/* Sample Outputs
--Input 1:

5
1 2 3 4 5
5 4 1 2 3
0
6
6 5 4 3 2 1
0
0

--Output 1:
Yes
No

Yes

--Input 2:
162
10 139 138 4 28 117 63 31 48 74 11 49 118 52 128 153 130 47 17 95 110 18 70 24
112 26 64 115 141 30 87 8 46 34 80 36 13 38 39 102 61 76 120 23 156 106 116 68
85 147 59 121 78 37 53 50 54 91 101 60 94 22 107 71 123 6 67 103 145 152 75 134
73 108 25 140 77 104 127 20 81 2 154 96 151 86 135 88 89 90 58 1 93 161 29 35 97
56 79 82 124 19 7 142 21 143 100 129 109 146 111 5 98 55 45 133 43 16 148 92 113
42 65 83 125 126 114 51 3 62 144 157 150 57 40 136 137 159 162 131 119 69 44 99
158 14 33 9 149 105 15 32 41 12 155 122 132 84 66 72 160 27 1 2 6 5 9 8 7 4 3 12
11 13 10 17 18 20 22 21 25 31 30 32 33 29 34 35 28 41 40 42 39 43 38 46 47 48 51
50 49 45 52 44 56 55 54 53 37 57 36 58 59 60 27 26 61 62 24 23 19 16 65 66 64 67
68 63 15 75 74 73 72 76 77 79 80 82 83 81 85 88 87 94 93 95 92 96 97 91 90 99
102 101 104 105 103 107 111 110 109 108 106 100 112 98 89 114 117 116 118 115
113 119 121 120 123 122 124 126 127 128 130 129 125 131 132 135 136 139 138 140
137 134 133 142 145 148 149 147 153 155 154 152 151 156 150 146 144 160 159 158
157 161 143 141 86 84 78 71 70 69 14 162 144 44 136 40 128 141 8 115 125 131 58
55 145 14 64 28 19 59 76 48 25 16 20 27 7 143 63 112 17 30 65 34 39 130 117 67
82 120 85 154 107 42 151 99 96 46 47 159 162 22 66 12 53 157 113 38 97 11 29 18
10 24 60 75 4 132 90 122 56 79 119 72 150 80 103 35 106 102 15 54 69 6 62 105 5
84 87 88 89 51 91 70 93 95 123 140 77 41 26 100 111 23 161 142 36 133 57 92 109
21 50 104 110 149 101 155 134 61 160 129 98 68 33 124 73 126 1 135 152 32 118
138 147 49 139 3 137 31 52 71 13 2 45 127 9 146 108 43 78 86 121 81 153 148 83
156 114 94 116 158 37 74 82 123 152 156 5 23 125 162 96 61 108 92 110 14 20 86
60 75 124 48 129 84 111 24 121 157 37 34 50 30 114 32 113 44 115 58 158 74 88
131 151 19 6 102 80 54 4 126 8 10 51 89 53 29 7 56 12 128 59 90 55 38 35 33 159
16 112 137 69 142 99 72 46 9 101 3 1 78 57 15 141 140 83 146 154 120 130 41 49
43 2 63 65 42 67 91 138 160 97 21 85 66 144 104 105 106 107 109 70 87 95 133 45
81 11 116 149 118 119 100 28 136 93 13 26 52 127 145 153 77 73 36 27 31 135 122
134 94 64 17 161 132 143 103 139 18 147 79 98 150 47 76 71 22 39 68 148 117 62
25 155 40 1 39 89 4 97 21 49 8 12 154 29 27 121 14 79 91 94 158 19 109 132 124
23 84 16 26 157 73 81 28 5 17 47 86 35 80 146 126 71 40 133 90 61 99 111 46 134
48 95 33 51 20 112 156 45 102 57 41 147 60 106 100 161 64 65 66 9 11 74 110 36
15 115 69 63 152 3 118 2 145 30 82 155 58 122 135 120 88 31 98 34 44 150 142 148
96 72 125 92 54 101 128 59 119 105 139 25 78 24 70 153 53 162 62 160 104 68 56
123 18 103 114 87 6 52 136 127 141 32 38 131 117 10 138 140 159 137 13 37 108
116 67 143 130 107 76 113 75 149 85 43 50 22 93 83 55 129 144 7 77 42 151 1 2 4
5 3 8 7 6 9 10 11 13 12 16 15 17 21 22 20 19 18 14 23 24 25 26 28 27 29 36 37 35
38 43 42 41 40 39 34 33 48 49 50 51 52 53 47 46 55 54 45 56 44 58 57 32 31 60 61
62 59 64 65 69 68 72 71 74 73 70 67 75 66 63 30 77 78 79 76 82 81 84 83 85 80 90
91 89 92 94 93 88 95 87 86 96 97 101 102 100 103 105 104 99 98 109 112 111 113
114 110 120 119 125 124 123 126 122 121 127 118 129 131 130 136 135 137 139 138
140 134 133 142 147 146 148 152 153 151 156 157 158 160 159 161 155 154 150 149
145 144 143 141 132 128 117 116 115 108 107 106 162 2 3 1 6 5 7 8 9 14 17 16 19
18 26 25 24 27 29 28 23 30 31 22 34 37 38 39 40 36 42 41 43 44 45 35 46 33 32 47
21 20 15 13 12 48 11 50 52 53 51 49 10 4 55 56 54 58 60 61 59 62 57 64 63 65 66
69 70 71 68 67 76 77 75 79 82 81 80 78 83 74 84 73 85 87 86 88 72 89 90 91 93 92
98 97 101 102 100 99 96 103 104 111 112 113 110 109 108 114 117 122 125 124 127
131 132 130 137 136 138 140 143 145 152 151 150 149 148 153 147 154 146 155 144
142 157 156 141 139 135 159 158 161 160 134 133 129 128 126 123 121 120 119 118
116 115 107 106 105 95 94 162
0
0


--Output 2:
No
Yes
No
No
No
Yes
Yes
*/