#include <cstddef>
#include <format>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

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
        found += static_cast<int>(sum < 4);
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
    row.reserve(line.length() + 2);
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

  return 0;
}