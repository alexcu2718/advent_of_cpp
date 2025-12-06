#include <cstddef>
#include <format>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
/*
--- Day 4: Printing Department ---

You ride the escalator down to the printing department. They're clearly getting
ready for Christmas; they have lots of large rolls of paper everywhere, and
there's even a massive printer in the corner (to handle the really big print
jobs).

Decorating here will be easy: they can make their own decorations. What you
really need is a way to get further into the North Pole base while the elevators
are offline.

"Actually, maybe we can help with that," one of the Elves replies when you ask
for help. "We're pretty sure there's a cafeteria on the other side of the back
wall. If we could break through the wall, you'd be able to keep moving. It's too
bad all of our forklifts are so busy moving those big rolls of paper around."

If you can optimize the work the forklifts are doing, maybe they would have time
to spare to break through the wall.

The rolls of paper (@) are arranged on a large grid; the Elves even have a
helpful diagram (your puzzle input) indicating where everything is located.

For example:

..@@.@@@@.
@@@.@.@.@@
@@@@@.@.@@
@.@@@@..@.
@@.@@@@.@@
.@@@@@@@.@
.@.@.@.@@@
@.@@@.@@@@
.@@@@@@@@.
@.@.@@@.@.

The forklifts can only access a roll of paper if there are fewer than four rolls
of paper in the eight adjacent positions. If you can figure out which rolls of
paper the forklifts can access, they'll spend less time looking and more time
breaking down the wall to the cafeteria.

In this example, there are 13 rolls of paper that can be accessed by a forklift
(marked with x):

..xx.xx@x.
x@@.@.@.@@
@@@@@.x.@@
@.@@@@..@.
x@.@@@@.@x
.@@@@@@@.@
.@.@.@.@@@
x.@@@.@@@@
.@@@@@@@@.
x.x.@@@.x.

Consider your complete diagram of the paper roll locations. How many rolls of
paper can be accessed by a forklift?

To begin, get your puzzle input.
*/
using std::format;
using std::ifstream;
using std::string;
using std::vector;

using Matrix = vector<vector<char>>;

static auto check_matrix(const Matrix &matrix) -> int {

  auto rows = matrix.size();
  auto cols = matrix[0].size();

  int found{0};

  for (size_t i = 1; i < rows - 1; i++) {
    for (size_t j = 1; j < cols - 1; j++) {
      if (matrix[i][j] == '@') {

        auto check_n = static_cast<int>(matrix[i - 1][j] == '@');
        auto check_s = static_cast<int>(matrix[i + 1][j] == '@');
        auto check_w = static_cast<int>(matrix[i][j - 1] == '@');
        auto check_e = static_cast<int>(matrix[i][j + 1] == '@');
        auto check_nw = static_cast<int>(matrix[i - 1][j - 1] == '@');
        auto check_ne = static_cast<int>(matrix[i - 1][j + 1] == '@');
        auto check_sw = static_cast<int>(matrix[i + 1][j - 1] == '@');
        auto check_se = static_cast<int>(matrix[i + 1][j + 1] == '@');
        auto sum = check_n + check_s + check_w + check_e + check_nw + check_ne +
                   check_sw + check_se;
        if (sum < 4) {
          found += 1;
        }
      }
    }
  }

  return found;
}

static auto read_matrix(const string &filename) -> int {
  ifstream inputFile(filename);

  Matrix matrix;
  string line;
  // pad the matrix with '.' above/below/to both sides so we dont need to
  // special case anything  in the index checks:)
  while (std::getline(inputFile, line)) {
    vector<char> row;
    row.push_back('.');
    row.insert(row.end(), line.begin(), line.end());
    row.push_back('.');
    matrix.push_back(row);
  }

  const size_t width = matrix[0].size();
  const vector<char> border_row(width, '.');
  matrix.insert(matrix.begin(), border_row);
  matrix.push_back(border_row);

  return check_matrix(matrix);
}

auto main() -> int {
  const auto sample = read_matrix("./aoc_inputs/day4_sample.txt");
  const auto part1 = read_matrix("./aoc_inputs/day4.txt");
  std::cout << format("found {} available in sample \nfound {} available to "
                      "move in part1",
                      sample, part1)
            << "\n";

  // part1 IS NOT 1417 ites less

  return 0;
}