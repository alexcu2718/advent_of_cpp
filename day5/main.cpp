#include <algorithm>
#include <array>
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <format>
#include <fstream>
#include <iostream>
#include <string>
#include <string_view>
#include <utility>
#include <vector>
using std::array;
using std::format;
using std::ifstream;
using std::pair;
using std::string;
using std::string_view;
using std::vector;

using IngredientList = pair<vector<array<uint64_t, 2>>, vector<uint64_t>>;

static auto parse_str(string_view spos) -> uint64_t {
  constexpr int TEN{10};

  uint64_t init{0};
  for (auto const &ch : spos) {
    init = (init * TEN) + static_cast<uint64_t>(ch - '0');
  }

  return init;
}

static auto read_file(const string &filename) -> IngredientList {
  ifstream inputFile(filename);

  vector<array<uint64_t, 2>> id_range;
  vector<uint64_t> available_ids;
  string line;

  bool passed_newline = false;
  while (std::getline(inputFile, line)) {

    if (!passed_newline) {
      if (line.empty()) {
        passed_newline = true;
        continue;
      }

      auto hyphen_pos = line.find('-');
      auto id_start = parse_str(string_view(line).substr(0, hyphen_pos));
      auto id_end = parse_str(string_view(line).substr(hyphen_pos + 1));
      assert(id_start <= id_end);
      auto newpair = array{id_start, id_end};
      id_range.push_back(newpair);
    } else {

      available_ids.push_back(parse_str(string_view(line)));
    }
  }

  return std::make_pair(id_range, available_ids);
}

static auto find_ingredients(const IngredientList &list) -> uint64_t {

  auto idranges = list.first;

  auto available_ingredients = list.second;
  uint64_t start = 0;
  // probably inefficient but I dont know a better algorithm
  for (auto const &ingred : available_ingredients) {
    for (auto const &avail : idranges) {
      if (avail[0] <= ingred && ingred <= avail[1]) {
        start++;
        break;
      }
    }
  }
  return start;
}

static auto count_fresh_ids(const IngredientList &list) -> uint64_t {
  auto idranges = list.first;

  std::ranges::sort(idranges, {}, [](const array<uint64_t, 2> &range) -> auto {
    return range[0];
  });

  uint64_t total_count = 0;
  uint64_t current_start = idranges[0][0];
  uint64_t current_end = idranges[0][1];

  for (size_t i = 1; i < idranges.size(); ++i) {
    const uint64_t next_start = idranges[i][0];
    const uint64_t next_end = idranges[i][1];

    if (next_start <= current_end + 1) {
      current_end = std::max(current_end, next_end);
    } else {
      total_count += (current_end - current_start + 1);
      current_start = next_start;
      current_end = next_end;
    }
  }

  total_count += (current_end - current_start + 1);

  return total_count;
}

auto main() -> int {

  auto sample_results = read_file("./aoc_inputs/day5_sample.txt");
  auto sample_p2 = count_fresh_ids(sample_results);
  std::cout << format("Sample P2 result: {}\n", sample_p2);
  assert(sample_p2 == 14);

  auto results = read_file("./aoc_inputs/day5.txt");

  auto get_results_p1 = find_ingredients(results);

  std::cout << format("The available ingredients for P1 are {}\n",
                      get_results_p1);
  assert(get_results_p1 == 733);

  auto get_results_p2 = count_fresh_ids(results);
  std::cout << format("The total fresh ingredient IDs for P2 are {}\n",
                      get_results_p2);

  assert(get_results_p2 == 345821388687084);

  return 0;
}