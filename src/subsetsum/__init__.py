from typing import List

import _subsetsum as _cpp


def solutions(nums: List[int], target: int):
    solver = _cpp.Solver(nums, target)

    if not solver.hasSolution():
        return
        yield

    solver.initSolutionIterator()
    solution = solver.getNextSolution()
    while solution:
        yield solution
        solution = solver.getNextSolution()


def has_solution(nums: List[int], target: int):
    return _cpp.Solver(nums, target).hasSolution()
