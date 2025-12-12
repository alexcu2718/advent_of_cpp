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

static auto parse_str(string_view spos) -> IntType {
  constexpr IntType TEN{10};
  IntType init{0};
  for (auto const ch : spos) {

    init = (init * TEN) + static_cast<IntType>(ch - '0');
  }

  return init;
}

static auto is_invalid(uint64_t num, size_t rep) -> bool {

  uint64_t temp = num;
  size_t len = 1;
  while (temp >= 10) {
    len++;
    temp /= 10;
  }

  for (size_t i = 2; i <= rep; ++i) {
    if (len % i == 0) {
      const size_t part_len = len / i;

      uint64_t power_of_10 = 1;
      for (size_t k = 0; k < len - part_len; ++k) {
        power_of_10 *= 10;
      }
      const uint64_t pattern = num / power_of_10;

      uint64_t reconstructed = 0;
      uint64_t pattern_power = 1;
      for (size_t k = 0; k < part_len; ++k) {
        pattern_power *= 10;
      }

      for (size_t j = 0; j < i; ++j) {
        reconstructed = (reconstructed * pattern_power) + pattern;
      }

      if (num == reconstructed) {
        return true;
      }
    }
  }
  return false;
}
static auto identify_invalid(string_view line, size_t rep) -> uint64_t {

  auto delimiter_pos = line.find('-');

  auto first_id = parse_str<uint64_t>(line.substr(0, delimiter_pos));
  auto second_id = parse_str<uint64_t>(line.substr(delimiter_pos + 1));
  uint64_t total{0};
  for (uint64_t i = first_id; i <= second_id; i++) {
    if (is_invalid(i, rep)) {
      total += i;
    }
  }
  return total;
}

static auto process_file(const string &filename, size_t rep) -> uint64_t {

  string line;
  ifstream file(filename);
  uint64_t full_total{0};
  while (std::getline(file, line, ',')) {

    full_total += identify_invalid(string_view(line), rep);
  }

  return full_total;
}

auto main() -> int {

  auto totalp1 = process_file("./aoc_inputs/day2.txt", 2);
  std::cout << format("Full total part1: {}\n", totalp1);

  auto totalp2 = process_file("./aoc_inputs/day2.txt", 10);
  std::cout << format("Full total part2: {}\n", totalp2);

  assert(totalp1 == 23534117921);
  assert(totalp2 == 31755323497);

  return 0;
}
