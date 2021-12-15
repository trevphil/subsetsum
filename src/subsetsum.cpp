#include <utility>
#include <algorithm>

#include "subsetsum.hpp"

namespace subsetsum {

std::vector<int> mutatingArgsort(std::vector<int>& a) {
  const int n = static_cast<int>(a.size());
  std::vector<std::pair<int, int>> a_indexed(n);
  std::vector<int> indices(n);

  for (int i = 0; i < n; ++i) {
    a_indexed[i] = {a[i], i};
  }
  std::stable_sort(a_indexed.begin(), a_indexed.end(),
    [](const std::pair<int, int>& x, const std::pair<int, int>& y) {
      return x.first < y.first;
  });
  for (int i = 0; i < n; ++i) {
    a[i] = a_indexed[i].first;
    indices[i] = a_indexed[i].second;
  }

  return indices;
}

Solver::Solver(const std::vector<int>& nums, int target)
    : nums_(nums), target_(target), has_sol_(true), dp_(nullptr) {
  n_ = static_cast<int>(nums_.size());
  if (n_ == 0) {
    has_sol_ = false;
    return;
  }

  if (target_ < 0) {
    flipSign();
  }

  const std::vector<int> indices = mutatingArgsort(nums_);

  int negative_sum = 0;
  int positive_sum = 0;

  for (int i = 0; i < n_; ++i) {
    remapping_[i] = indices[i];
    if (nums_[i] < 0) {
      negative_sum += nums_[i];
    } else {
      positive_sum += nums_[i];
    }
  }

  if (target_ < negative_sum || target_ > positive_sum) {
    has_sol_ = false;
    return;
  }

  a_ = negative_sum;
  b_ = target_;
  nrows_ = n_;
  ncols_ = b_ - a_ + 1;
  dp_ = new uint8_t[nrows_ * ncols_];
  fillDPTable();
  if (!dp_[nrows_ * ncols_ - 1]) {
    has_sol_ = false;
  }
}

Solver::~Solver() {
  if (dp_ != nullptr) {
    delete dp_;
  }
}

void Solver::flipSign() {
  target_ *= -1;
  for (int i = 0; i < n_; ++i) {
    nums_[i] *= -1;
  }
}

void Solver::fillDPTable() {
  // Fill the first row of "dp_"
  for (int j = 0; j < ncols_; ++j) {
    dp_[j] = nums_[0] == (a_ + j);
  }
  // Fill the remaining rows of "dp_"
  for (int i = 1; i < nrows_; ++i) {
    for (int j = 0; j < ncols_; ++j) {
      const int cur = i * ncols_ + j;
      const int prev = (i - 1) * ncols_ + j;
      const int s = a_ + j;
      dp_[cur] = dp_[prev] || nums_[i] == s;
      if (!dp_[cur]) {
        const int next_col = s - nums_[i] - a_;
        if (0 <= next_col && next_col < ncols_) {
          dp_[cur] = dp_[prev - j + next_col];
        }
      }
    }
  }
}

std::vector<int> Solver::genSolution(const QueueItem& item) const {
  const int n = static_cast<int>(item.take.size());
  std::vector<int> sol(n);
  for (int i = 0; i < n; ++i) {
    sol[i] = remapping_.at(item.take.at(i));
  }
  std::sort(sol.begin(), sol.end());
  return sol;
}

void Solver::initSolutionIterator() {
  if (has_sol_) {
    const std::vector<int> take = {nrows_ - 1};
    const int togo = target_ - nums_[nrows_ - 1];
    queue_ = {QueueItem(nrows_ - 1, ncols_ - 1, take, togo)};
  }
}

std::vector<int> Solver::getNextSolution() {
  if (!has_sol_) {
    return {};
  }

  while (queue_.size() > 0) {
    const QueueItem item(queue_.back());
    queue_.pop_back();

    const int row = item.row;
    const int col = item.col;

    if (row > 0 && dp_[(row - 1) * ncols_ + col]) {
      std::vector<int> take = item.take;
      take[take.size() - 1] = row - 1;
      const int togo = item.togo + nums_[row] - nums_[row - 1];
      queue_.emplace_back(row - 1, col, take, togo);
    }

    const int next_col = col - nums_[row];
    if (row > 0 && 0 <= next_col && next_col < ncols_) {
      if (dp_[(row - 1) * ncols_ + next_col]) {
        std::vector<int> take = item.take;
        take.emplace_back(row - 1);
        const int togo = item.togo - nums_[row - 1];
        queue_.emplace_back(row - 1, next_col, take, togo);
      }
    }

    if (item.togo == 0) {
      return genSolution(item);
    }
  }

  return {};
}

}  // end namespace subsetsum
