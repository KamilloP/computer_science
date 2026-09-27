This is based on task `hard/030_substring_with_concatenation_of_all_words`. Compile example test with:
```
g++ -std=c++17 -Wall -Wextra -pedantic \
    test.cpp \
    solution/trie/trie.cpp \
    solution/solution.cpp \
    -o test
```
Then we pass list of number identifiers of the tests to check if solution outputs are the same as expected. For example `./test 0` takes input `0.in` and compares if it is the same as defined in `0.out`.