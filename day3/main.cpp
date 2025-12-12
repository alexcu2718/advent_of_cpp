#include <algorithm>
#include <cassert>
#include <concepts>
#include <cstddef>
#include <cstdint>
#include <format>
#include <fstream>
#include <iostream>
#include <string>
#include <string_view>
using std::format;
using std::ifstream;
using std::string;
using std::string_view;

template <typename IntType>
  requires std::integral<IntType>
static auto parse_char(string_view spos) -> IntType {
  constexpr IntType TEN{10};

  IntType init{0};
  for (auto const &ch : spos) {
    init = (init * TEN) + static_cast<IntType>(ch - '0');
  }

  return init;
}

static auto get_max(string_view str, size_t length) -> uint64_t {
  const size_t n = str.length();
  length = std::min(length, n);

  string result;
  result.reserve(length);
  size_t start = 0;

  for (size_t i = 0; i < length; ++i) {

    const size_t end = n - (length - i - 1);
    const auto *max_it =
        std::ranges::max_element(str.begin() + start, str.begin() + end);

    result += *max_it;
    start = (max_it - str.begin()) + 1;
  }

  return parse_char<uint64_t>(string_view(result));
}

static auto process_file(const string &filename, size_t length) -> uint64_t {

  string line;
  ifstream file(filename);
  uint64_t full_total{0};

  while (std::getline(file, line)) {
    full_total += get_max(string_view(line), length);
  }

  return full_total;
}

auto main() -> int {

  auto totalp1 = process_file("./aoc_inputs/day3.txt", 2);
  auto totalp2 = process_file("./aoc_inputs/day3.txt", 12);
  std::cout << format(
      "Full total part1: {} \n and the answer for part 2 is {}\n", totalp1,
      totalp2);
  assert(totalp1 == 17031);
  assert(totalp2 == 168575096286051);

  return 0;
}
