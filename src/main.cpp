#include <format>
#include <fstream>
#include <iostream>
#include <string_view>

auto parse_line(std::string_view spos) -> int {
  constexpr int TEN{10};
  // L= negative R= positive
  auto left_rotation = spos[0] == 'L';
  auto multiplier = 1 - (2 * static_cast<int>(left_rotation));

  auto value = spos.substr(1, spos.length());
  int init = 0;
  for (auto const &ch : value) {
    init = (init * TEN) + static_cast<int>(ch - '0');
  }

  return multiplier * init;
}

auto process_file_part1(const std::string &filename) -> int {
  constexpr int START{50};
  constexpr int ONEHUN{100};
  int counter = 0;
  int start_pos = START;
  std::string line;
  std::fstream file(filename);
  while (std::getline(file, line)) {

    auto parsed_val = parse_line(std::string_view(line));
    auto is_negative = parsed_val < 0;
    auto useval = ONEHUN * (static_cast<int>(is_negative)); // make branchless
    start_pos = (useval + (((start_pos + parsed_val)))) % ONEHUN;
    counter += static_cast<int>(start_pos == 0); // annoying branchless tricks
  }

  return counter;
}

auto process_file_part2(const std::string &filename) -> int {
  constexpr int START{50};
  constexpr int ONEHUN{100};
  int counter = 0;
  int start_pos = START;
  std::string line;
  std::fstream file(filename);
  while (std::getline(file, line)) {

    auto parsed_val = parse_line(std::string_view(line));
    auto is_left = static_cast<int>(parsed_val < 0);
    int count = parsed_val - (2 * parsed_val * is_left);

    int full_rotations = count / ONEHUN;
    counter += full_rotations;
    count = count % ONEHUN;
    // so many tricks here again
    auto direction_mult = 1 - (2 * is_left);
    auto next_pos = start_pos + (count * direction_mult);
    auto left_wrap = static_cast<int>(next_pos < 0);
    auto right_wrap = static_cast<int>(next_pos >= ONEHUN);
    auto start_nonzero = static_cast<int>(start_pos > 0);
    auto not_exact_hundred = static_cast<int>(next_pos != ONEHUN);
    counter += (is_left * left_wrap * start_nonzero) +
               ((1 - is_left) * right_wrap * not_exact_hundred);
    start_pos = ((next_pos % ONEHUN) + ONEHUN) % ONEHUN;

    counter += static_cast<int>(start_pos == 0);
  }

  return counter;
}

auto main() -> int {

  auto ans1 = process_file_part2("./aoc_inputs/day1.txt");

  auto ans2 = process_file_part2("./aoc_inputs/day1.txt");
  std::cout << std::format("the solution to p1 is {} solution to part2 is {}",
                           ans1, ans2)
            << "\n";

  return 0;
}
