# computer_science
Algorithms, data structures, solutions to competitive programming tasks in c++ and more.

Project does not follow any specific curriculum, but rather is used for revision general computer science
knowledge, with main focus on algorithms and c++ language.

Under construction.

## Algorithms
Implementation of some algorithms in c++ 17. Usually as general as possible. Solutions are self made, no AI - thus code documentation might be partial. Of course AI ***was*** used for learning.

| Algorithm                | Implemented         | Where in `Algorithms` | Some leetcode problems |
| ------------------------ | ------------------- | --------------------- | ---------------------- |
| RMQ                      | Yes                 | `rmq/rmq.h`           | -                      |
| LCA (linear)             | Yes                 | `graph/graph.h`       | -                      |
| FifoMax (Sliding Window) | Yes                 | `fifo_max/fifo_max.h` | 239, 3578              |
| LifoMax                  | Yes                 | `lifo_max/lifo_max.h` | 155                    |
| Trie                     | Yes (only problems) | -                     | 30                     |
| Backtracking             | Yes (only problems) | -                     | 39, 40, 46, 47         |
| DFS connected components | Yes (only problems) | -                     | 827                    |
| Greedy                   | Yes (only problems) | -                     | 45, 53                 |
| Divide and conquer       | Yes (only problems) | -                     | 53, 56                 |
| Fast exponentation       | Yes (only problems) | -                     | 50                     |
| KMP, LPS                 | Yes (only problems) | -                     | 30                     |
| Dynamic programming      | Yes (only problems) | -                     | 3578, 44               |
| Red-black tree           | Not yet (but used)  | -                     | 56                     |
| AVL tree                 | Not yet             | -                     | 56                     |
| Lazy segment tree        | Not yet             | -                     | 56                     |

<!-- In c++ 20 we could use `require` and `concept` for easier definition of templates. -->

## leetcode
`leetcode` contains solutions to some tasks from [leetcode] problems dataset. Each solution present has passed the leetcode tests. `leetcode/testing_environment` contains example of testing custom Trie.

[leetcode]: https://leetcode.com/problemset/

## Current TODO
Algorithms: lazy segment tree (could be used in 56), red-black tree, AVL, topological sort, dijkstra, 2-SAT solver, Find&Union, suffix tree, lcp, copy implementation of kmp, Trie, LPS from solutions and generalize.

Check true implementation of set (which is stated to be red-black tree on cppreference), maybe step by step tutorial.

More graph tests.

<!-- maybe_unused, unique_ptr, -->
<!-- c++20: <=>, required, concept. -->

## Tests remarks
To compile majority of the tests  in folder `Algorithms/tests`, use commented command in the test. 
For example for `test_fifo_max.cpp`:
```
g++ -std=c++17 -Wall -Wextra -pedantic test_fifo_max.cpp -o bin/test_fifo_max
```
These executables will be saved in `bin` folder.

Currently exceptions are `test_rmq.cpp` and `test_lca.cpp`. They use module [argparse], thus I have decided to use cmake (check `Algorithms/tests/CMakeLists.txt`). Compilation:
```
cmake -S . -B build
cmake --build build
```
Executables for these tests are saved in `build` folder.

Both folders `bin` and `build` are hidden (check `.gitignore`).

Tests use data from folder `Algorithms/tests/dataset`. Example tests are provided.

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
- nested template: `Algorithms/tests/utility_test/utility_test.h::VectorT`
- constexpr: `Algorithms/tests/utility_test/utility_test.h::readVector`
- using: `Algorithms/graph/graph.h::Graph`
- const referenced structure binding: `Algorithms/graph/graph.tpp::isProperTree` 
- all_of: `Algorithms/graph/graph.tpp::isProperTree`
- optional: `Algorithms/graph/graph.tpp::LCA::rmq`

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