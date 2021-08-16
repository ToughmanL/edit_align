
#include <iostream>
#include <string>
#include "edit-distance.h"

int main() {
  std::vector<std::string> a(3), b(3);
  a[0] = "asf";
  a[1] = "asf";
  a[2] = "asf";
  b[0] = "asf";
  b[1] = "abf";

  std::string eps_symbol = "unknow";
  std::vector<std::pair<std::string, std::string> > output;
  EditAlign edit_test;
  edit_test.LevenshteinAlignment(a, b, eps_symbol, &output);
  std::cout << output.size() << std::endl;
  for (int i = 0; i < output.size(); i++) {
    std::cout << output[i].first << " " << output[i].second << std::endl;
  }
  return 0;
}

