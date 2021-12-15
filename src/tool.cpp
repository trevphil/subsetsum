#include <vector>
#include <iostream>

#include "subsetsum.hpp"

/*
g++ tool.cpp subsetsum.cpp -o tool -std=c++17 -Wall -Werror
*/

void printVec(const std::vector<int>& v) {
  const int n = static_cast<int>(v.size());
  std::cout << "[ ";
  for (int i = 0; i < n; ++i) {
    std::cout << v[i] << (i == n - 1 ? " ]" : ", ");
  }
}

int main(int argc, char** argv) {
  const int target = std::stoi(argv[1]);
  std::vector<int> nums;
  for (int i = 2; i < argc; ++i) {
    nums.emplace_back(std::stoi(argv[i]));
  }

  std::cout << "target = " << target << std::endl;
  printVec(nums);
  std::cout << std::endl << "------" << std::endl;

  subsetsum::Solver solver(nums, target);
  solver.initSolutionIterator();

  std::vector<int> solution = solver.getNextSolution();
  while (solution.size() > 0) {
    std::vector<int> subset;
    int sum = 0;
    for (int index : solution) {
      subset.push_back(nums[index]);
      sum += nums[index];
    }

    printVec(subset);
    std::cout << " = " << sum << std::endl;

    solution = solver.getNextSolution();
  }

  return 0;
}
