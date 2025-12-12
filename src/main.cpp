#include <cassert>
#include <cctype>
#include <concepts>
#include <cstddef>
#include <cstdint>
#include <format>
#include <fstream>
#include <iostream>
#include <ranges>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

using std::format;
using std::ifstream;
using std::string;
using std::string_view;
using std::vector;

using Matrix = vector<vector<string>>;

template <typename IntType>
  requires std::integral<IntType>
static auto parse_str(string_view spos) -> IntType {
  constexpr IntType TEN{10};

  IntType init{0};
  for (auto const ch : spos) {
    init = (init * TEN) + static_cast<IntType>(ch - '0');
  }

  return init;
}

static auto read_file(const string &filename) -> Matrix {
  namespace views = std::views;

  ifstream inputFile(filename);
  Matrix result;

  for (string line; std::getline(inputFile, line);) {
    // remove starting all spaces, make a vector of vector of strings (probably
    // shitty solution but eh)
    auto words =
        line | // pipe operator my beloved
        views::drop_while([](char c) -> auto { return std::isspace(c); }) |

        views::reverse |
        views::drop_while([](char c) -> auto { return std::isspace(c); }) |
        views::reverse | views::split(' ') |
        views::filter(
            [](auto &&word_range) -> auto { return !word_range.empty(); }) |

        views::transform([](auto &&word_range) -> auto {
          return string(word_range.begin(), word_range.end());
        });

    vector<string> line_words;
    for (auto &&word : words) {
      line_words.push_back(std::move(word));
    }
    result.push_back(std::move(line_words));
  }

  return result;
}

static auto calculate(const Matrix &matrix)
    -> uint64_t { // this better not overflow!
  uint64_t grand_total{0};
  auto rows = matrix.size();
  auto cols = matrix[0].size();

  size_t col = 0;
  while (col < cols) {
    const size_t start_col = col;
    const size_t end_col = col;

    vector<uint64_t> numbers;
    for (size_t c = start_col; c <= end_col; ++c) {
      for (size_t r = 0; r < rows - 1; ++r) {
        numbers.push_back(parse_str<uint64_t>(matrix[r][c]));
      }
    }
    const char op = matrix[rows - 1][end_col][0];

    uint64_t result = (op == '+') ? 0 : 1;
    for (auto n : numbers) {
      if (op == '+') {
        result += n;
      } else if (op == '*') {
        result *= n;
      }
    }
    grand_total += result;

    col = end_col + 1;
  }
  return grand_total;
}
auto main() -> int {

  auto result_sample = read_file("./aoc_inputs/day6_sample.txt");
  auto calc_sample = calculate(result_sample);
  auto result_part1 = read_file("./aoc_inputs/day6.txt");
  auto calc_p1 = calculate(result_part1);

  std::cout << format("the answer for sample is {}, the answer for p1 is {}\n",
                      calc_sample, calc_p1);
  // Now i see day6 p2 and im ill and lazy. sigh.

  return 0;
}