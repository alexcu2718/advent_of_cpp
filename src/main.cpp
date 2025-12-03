#include <cstddef>
#include <cstdint>
#include <format>
#include <fstream>
#include <iostream>
#include <string>
#include <string_view>

static auto parse_str(std::string_view spos) -> uint64_t {
  constexpr uint64_t TEN{10};
  uint64_t init{0};
  for (auto const &ch : spos) {

    init = (init * TEN) + static_cast<uint64_t>(ch - '0');
  }

  return init;
}

static auto is_invalid(uint64_t num) -> bool {
  const std::string s = std::format("{}", num);
  const size_t len = s.length();

  for (size_t i = 2; i <= 2; ++i) {
    if (len % i == 0) {
      const std::string part = s.substr(0, len / i);
      std::string reconstructed;
      for (size_t j = 0; j < i; ++j) {
        reconstructed += part;
      }
      return s == reconstructed;
    }
  }
  return false;
}

static auto identify_invalid(std::string_view line) -> uint64_t {

  auto delimiter_pos = line.find('-');

  auto first_id = parse_str(line.substr(0, delimiter_pos));
  auto second_id = parse_str(line.substr(delimiter_pos + 1));
  uint64_t total{0};
  for (uint64_t i = first_id; i <= second_id; i++) {
    if (is_invalid(i)) {
      total += i;
    }
  }
  return total;
}

static auto process_file(const std::string &filename) -> uint64_t {

  std::string line;
  std::fstream file(filename);
  uint64_t full_total{0};
  while (std::getline(file, line, ',')) {

    full_total += identify_invalid(std::string_view(line));
  }

  return full_total;
}

auto main() -> int {

  auto total = process_file("./aoc_inputs/day2.txt");
  std::cout << std::format("Full total: {}", total) << "\n";

  return 0;
}
