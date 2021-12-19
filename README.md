# subsetsum

The `subsetsum` Python module can enumerate all combinations within a list of integers which sums to a specific value. It works for both negative and positive `target` sum values, as well as negative, positive, and repeating values in the list of input numbers. `subsetsum` can also quickly answer whether or not _there exists_ a subset of integers in the input list which sums to `target`.

## Installation

```
pip install subsetsum
```

## Example usage

```
import subsetsum

target = 0
nums = [-2, -1, 0, 1, 2]

has_solution = subsetsum.has_solution(nums, target)
print(f"Can {nums} sum to {target}? {has_solution}")

for solution in subsetsum.solutions(nums, target):
    # `solution` contains indices of elements in `nums`
    subset = [nums[i] for i in solution]
    sum_value = sum(subset)
    print(f"{subset} sums to {sum_value}")
```

## API

```
import subsetsum


subsetsum.has_solution(nums: List[int], target: int) -> bool:
    Determines if there is a subset of `nums` which sums to
        `target`. If `nums` is empty, the result is always False.

    Args:
        nums (List[int]): A list of integers (positive or negative)
            for the SUBSET-SUM problem
        target (int): The target value (positive or negative) which
            will be used in the SUBSET-SUM problem

    Returns:
        bool: True if there exists a subset of `nums` which sums to
            `target`, otherwise false


subsetsum.solutions(nums: List[int], target: int) -> Iterator[List[int]]:
    Enumerates all solutions to SUBSET-SUM. If `nums` is empty,
    no solutions will be generated.

    Args:
        nums (List[int]): A list of integers (positive or negative)
            from which subsets will be generated
        target (int): The target value (positive or negative) for the
            sum of each subset

    Returns:
        Iterable: An iterator over the set of solutions, where each
            solution is a list of integers that index into the original
            list `nums` to form a subset
```
