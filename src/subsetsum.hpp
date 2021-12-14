#pragma once

#include <vector>
#include <map>

namespace subsetsum {

class Solver {
 public:
  Solver(const std::vector<int>& nums, int target);

  virtual ~Solver();

  inline bool hasSolution() const {
    return has_sol_;
  }

  void initSolutionIterator();

  std::vector<int> getNextSolution();

 private:
  class QueueItem {
   public:
    QueueItem(int r, int c, const std::vector<int>& i, int t)
        : row(r), col(c), take(i), togo(t) {}
    int row, col;
    std::vector<int> take;
    int togo;
  };

  void fillDPTable();

  std::vector<int> genSolution(const QueueItem& item) const;

  int n_;
  std::vector<int> nums_;
  std::map<int, int> remapping_;
  int target_;
  bool has_sol_;
  int a_, b_;
  int nrows_, ncols_;
  uint8_t* dp_;
  std::vector<QueueItem> queue_;
};

}  // end namespace subsetsum
