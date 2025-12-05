#include <cassert>
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

static auto parse_str(string_view spos) -> uint64_t {
  constexpr uint64_t TEN{10};
  uint64_t init{0};
  for (auto const &ch : spos) {

    init = (init * TEN) + static_cast<uint64_t>(ch - '0');
  }

  return init;
}

static auto is_invalid(uint64_t num, size_t rep) -> bool {
  const auto s{std::to_string(num)};
  const size_t len{s.length()};
  string reconstructed;
  reconstructed.reserve(21); // UINT64_MAX=20 chars.
  for (size_t i = 2; i <= rep; ++i) {
    if (len % i == 0) {
      const auto part = string_view(s).substr(0, len / i);
      reconstructed.clear();
      for (size_t j = 0; j < i; ++j) {
        reconstructed += part;
      }
      if (s == reconstructed) {
        return true;
      }
    }
  }
  return false;
}

static auto identify_invalid(string_view line, size_t rep) -> uint64_t {

  auto delimiter_pos = line.find('-');

  auto first_id = parse_str(line.substr(0, delimiter_pos));
  auto second_id = parse_str(line.substr(delimiter_pos + 1));
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
  std::cout << format("Full total part1: {}", totalp1) << "\n";

  auto totalp2 = process_file("./aoc_inputs/day2.txt", 10);
  std::cout << format("Full total part2: {}", totalp2) << "\n";

  assert(totalp1 == 23534117921);
  assert(totalp2 == 31755323497);

  return 0;
}
