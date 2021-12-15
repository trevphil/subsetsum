from collections import defaultdict

import subsetsum


class TestSubsetSum:
    def test_empty_input(self):
        assert not subsetsum.has_solution([], 0)
        solutions = list(subsetsum.solutions([], 0))
        assert len(solutions) == 0

    def test_valid_single_input(self):
        assert subsetsum.has_solution([1], 1)
        solutions = list(subsetsum.solutions([1], 1))
        assert len(solutions) == 1
        assert solutions[0] == [0]

    def test_no_solution(self):
        assert not subsetsum.has_solution([1], 0)
        solutions = list(subsetsum.solutions([1], 0))
        assert len(solutions) == 0

    def check_results(self, nums, expected, solutions):
        counts = defaultdict(lambda: 0)
        for subset in expected:
            key = tuple(sorted(subset))
            counts[key] += 1

        for solution in solutions:
            subset = [nums[i] for i in solution]
            key = tuple(sorted(subset))
            counts[key] -= 1

        for key, count in counts.items():
            assert count == 0, f"{key} : {count}"

    def test_solutions(self):
        nums = [-2, 2, -1, 1, 0]
        target = 0
        solutions = list(subsetsum.solutions(nums, target))
        expected = [
            (-2, 2),
            (-2, 0, 2),
            (-1, 1),
            (-1, 0, 1),
            (-2, -1, 0, 1, 2),
            (-2, -1, 1, 2),
            (0,),
        ]
        self.check_results(nums, expected, solutions)

    def test_repeating_numbers(self):
        nums = [-1, -1, 0, 1, 1]
        target = 0
        solutions = list(subsetsum.solutions(nums, target))
        expected = [
            (0,),
            (-1, 1),
            (-1, 1),
            (-1, 1),
            (-1, 1),
            (-1, 0, 1),
            (-1, 0, 1),
            (-1, 0, 1),
            (-1, 0, 1),
            (-1, -1, 1, 1),
            (-1, -1, 0, 1, 1),
        ]
        self.check_results(nums, expected, solutions)

    def test_target_too_high(self):
        nums = [-3, -5, 0, 4, 3]
        target = 8
        assert not subsetsum.has_solution(nums, target)
        solutions = list(subsetsum.solutions(nums, target))
        assert len(solutions) == 0

    def test_target_too_low(self):
        nums = [-3, -5, 0, 4, 3]
        target = -9
        assert not subsetsum.has_solution(nums, target)
        solutions = list(subsetsum.solutions(nums, target))
        assert len(solutions) == 0

    def test_max_target(self):
        nums = [-1, -1, 1, 1]
        target = 2
        solutions = list(subsetsum.solutions(nums, target))
        expected = [(1, 1)]
        self.check_results(nums, expected, solutions)

    def test_min_target(self):
        nums = [-1, -1, 1, 1]
        target = -2
        solutions = list(subsetsum.solutions(nums, target))
        expected = [(-1, -1)]
        self.check_results(nums, expected, solutions)

    def test_combinatorial(self):
        nums = [0] * 10
        target = 0
        solutions = list(subsetsum.solutions(nums, target))
        num_solutions = len(solutions)
        assert num_solutions == (1 << 10) - 1

    def test_correct_sum(self):
        data = [
            ([-1, -2, -3], (-6, -4)),
            ([3, 2, 1], (4, 6)),
            ([0, -3, 3, 2, -2, -1, 1], (-6, 6)),
        ]
        for item in data:
            self.has_correct_sum(item)

    def has_correct_sum(self, data):
        nums, bounds = data
        for t in range(bounds[0], bounds[1] + 1):
            solutions = list(subsetsum.solutions(nums, t))
            assert len(solutions) > 0, f"No solution : {nums} : {t}"
            for solution in solutions:
                subset = [nums[i] for i in solution]
                total = sum(subset)
                assert total == t, f"Wrong solution : {subset} : {total} != {t}"


if __name__ == "__main__":
    test_obj = TestSubsetSum()
    tests = [getattr(test_obj, fn) for fn in dir(test_obj) if fn.startswith("test")]
    num_passed = 0
    for test_fn in tests:
        test_fn()
        num_passed += 1
    print(f"{num_passed} tests passed.")
