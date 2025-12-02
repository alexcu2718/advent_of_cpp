#include <iostream>
#include <format>
#include <cassert>
#include <string_view>
#include <vector>
#include <fstream>

auto read_file(const std::string& filename)->std::vector<std::string> {
    std::ifstream file(filename);

    std::string line;
    std::vector<std::string> vec{};

    while (std::getline(file, line)) {
        vec.push_back(line);
    }

    file.close();
    return vec;
}


auto parse_line(std::string_view spos)->int{

        //L= negative R= positive
        auto left_rotation=spos[0]=='L';
        auto multiplier = 1 - (2 * static_cast<int>(left_rotation));

          auto value=spos.substr(1,spos.length());
          int init=0;
          for(auto const& ch:value){
            init = init * 10 + static_cast<int>(ch - '0');


          }

          return multiplier*(init % 100);
}


auto process_file(const std::string& filename)->int{
  int counter=0;
  int start_pos=50;
  auto file_contents=read_file(filename);
  for (auto const& val:file_contents){

      auto parsed_val=parse_line(val);
      auto is_negative=parsed_val<0;
      auto useval=100*(static_cast<int>(is_negative)); //make branchless
      start_pos=(useval+(((start_pos+parsed_val) % 100)))%100;
      counter+=static_cast<int>(start_pos==0); //annoying branchless tricks
  }

  return counter;

}



auto main()->int {


    auto ans=process_file("./aoc_inputs/day1.txt");
    std::cout<<std::format("{}",ans)<<"\n";



    return 0;
}
