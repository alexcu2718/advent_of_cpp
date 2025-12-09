#include <array>
#include <cassert>
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
    for (auto const avail : idranges) {
      if (avail[0] <= ingred && ingred <= avail[1]) {
        start++;
        break;
      }
    }
  }
  return start;
}

auto main() -> int {

  auto results = read_file("./aoc_inputs/day5.txt");

  auto get_results = find_ingredients(results);

  std::cout << format("The available ingredients for P1 are {}\n", get_results);
  return 0;
}