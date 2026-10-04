# computer_science
Algorithms, data structures, solutions to competitive programming tasks in c++ and more.

Project does not follow any specific curriculum, but rather is used for revision general computer science
knowledge, with main focus on algorithms and c++ language.

Under construction.

## Algorithms
Implementation of some algorithms in c++ 17. Usually as general as possible. Solutions are self made, no AI - thus code documentation might be partial. Of course AI *was* used for learning.

Algorithms and example problems:
- Dynamic programming: 3578, 44
- Fifo Max (Sliding Window): 3578, 239
- Lifo Max: 155
- Backtracking: 39, 40, 46, 47
- DFS: 827 (connected components)
- Greedy: 45, 53
- Divide and conquer: 53
- Fast exponentation: 50
- Divide and conquer: 56
- Self-balancing BST: 56
- Lazy segment tree: 56 (not yet implemented)

<!-- In c++ 20 we could use `require` and `concept` for easier definition of templates. -->

## leetcode
`leetcode` contains solutions to some tasks from [leetcode] problems dataset. Each solution present has passed the leetcode tests. `leetcode/testing_environment` contains example of testing custom Trie.

[leetcode]: https://leetcode.com/problemset/

## Current TODO
lca, lazy segment tree (could be used in 56), red-black tree, AVL, topological sort, dijkstra, 2-SAT solver, Find&Union, suffix tree, lcp, copy implementation of kmp, Trie, LPS from solutions and generalize.

Check true implementation of set (which is stated to be red-black tree on cppreference).

## Tests remarks
To compile majority of the tests  in folder `Algorithms/tests`, use commented command in the test. 
For example for `test_fifo_max.cpp`:
```
g++ -std=c++17 -Wall -Wextra -pedantic test_fifo_max.cpp -o bin/test_fifo_max
```
These executables will be saved in `bin` folder.

Currently exception is `test_rmq.cpp`. It uses module [argparse], thus I have decided to use cmake (check `Algorithms/tests/CMakeLists.txt`). Compilation:
```
cmake -S . -B build
cmake --build build
```
Executable for this test is saved in `build` folder.

Both folders `bin` and `build` are hidden (check `.gitignore`).

Tests use data in folder `Algorithms/tests/dataset`. Example tests are provided.

[argparse]: (https://github.com/p-ranav/argparse/tree/master#requiring-optional-arguments)

# Examples of c++
Functions/structures and example problems/algorithms (problem mentioned by a leetcode number, algorithm described by name):
- transform: 51
- lambda function: 51
- array: 49
- deque: 239, algorithm FifoMax
- stack: 155
- tie: 53
- operator overloading: 54
- template: 54, each algorithm
- using: `Algorithms/graph/graph.h::Graph`
- const referenced structure binding: `Algorithms/graph/graph.tpp::isProperTree` 
- all_of: `Algorithms/graph/graph.tpp::isProperTree`

Useful classes:
- Point in geometry: 54

# Some computer science knowledge QA
- *Function parameters vs function arguments?*: 
    Function arguments are values we pass to the function during the function call, whereas
    function parameters are defined variables in the function head.
- *Class vs struct in c++?*:
    In class everything is on default private, whereas in struct everything is on default public.
- *What is RVO?* - Return Value Optimization, compiler optimization that involves eliminating the
   temporary object created to hold a function's return value. More: [Copy Elision Wikipedia], [Copy Elision sigcpp] and especially [RVO medium]
- *What is move constructor?*: special constructor that transfer ownership of the resources. More:
    [Move geeksforgeeks].
- *lvalue vs prvalue?*: lvalue have memory address accessible in program, and prvalue is pure temporary object without memory address. More: [lvalues and rvalues Microsoft], [lvalues and rvalues cppreference].


[Copy Elision Wikipedia]: (https://en.wikipedia.org/wiki/Copy_elision)
[Copy Elision sigcpp]: (https://sigcpp.github.io/2020/06/08/return-value-optimization)
[RVO medium]: (https://medium.com/@sagarmadala/cpp-rvo-return-value-optimization-b6f468057298)
[Move geeksforgeeks]: (https://www.geeksforgeeks.org/cpp/move-constructors-in-c-with-examples/)
[lvalues and rvalues Microsoft]: (https://learn.microsoft.com/pl-pl/cpp/cpp/lvalues-and-rvalues-visual-cpp?view=msvc-170)
[lvalues and rvalues cppreference]: (https://en.cppreference.com/cpp/language/value_category)


<!-- For JJK fans: 48 leetcode -->