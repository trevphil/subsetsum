# subsetsum

The `subsetsum` Python module can enumerate all combinations within a list of integers which sums to a specific value. It works for both negative and positive `target` sum values, as well as negative, positive, and repeating values in the list of input numbers. `subsetsum` can also quickly answer whether or not _there exists_ a subset of integers in the input list which sums to `target`.

## Installation

```
pip install subsetsum
```

## Example usage:

```
import subsetsum

target = 0
nums = [-2, -1, 0, 1, 2]

has_solution = subsetsum.has_solution(nums, target)
print(f"Can {nums} sum to {target}? {has_solution}")

for solution in subsetsum.solutions(nums, target):
    # `solutions` contains indices of elements in `nums`
    subset = [nums[i] for i in solution]
    sum_value = sum(subset)
    print(f"{subset} sums to {sum_value}")
```
