# CS 3251: Intermediate Software Design
## Programming Assignment 3 - A More Complex Data Type

### Assignment Objectives
- Start to build up a more complex program
  - Implement first design pattern - iterator
  - Carefully manage dynamic memory
  - Grow complexity of the project
- Advance Our C++ Knowledge
  - Use templates to build a generic data structure
  - Utilize type traits for generic containers
  - Leverage simple classes with composition for memory management
- More advanced toolchain
  - Much larger file/LoC count
  - More complex CMake setup

### Patterns Explored
- [Iterator pattern](https://en.wikipedia.org/wiki/Iterator_pattern)

# Assignment Overview

This assignment focuses on building a more complex and useful data structure.  You are going to build an templatized linear data structure that can grow its underlying dynamic memory array as elements are added to it.

As always, you have been provided with several source files to start with that you need to add code to:

* `include/array_list.h`
* `include/array_list_iter.h`

These files are incomplete and your job is to finish them so that your classes pass all the automated tests.

Additionally, there are a couple of classes you will use, but you should **not** modify:

* `include/allocation_tracker.h`
* `include/scoped_array.h`
* `src/allocation_tracker.cpp`
 
Finally, you are given several files for building and testing which you should **not** modify:

* `tests/main.cpp`
* `tests/array.cpp`
* `tests/iter.cpp`
* `tests/const_iter.cpp`
* `.github/workflows/build.yml`
* `.github/workflows/linter.sh`
* `.clang-format`
* `.gitignore`
* `CMakeLists.txt`
* `README.md`

The files _array_list.h_ and _array_list_iter.h_ contain some code and many comments that outline portions of the expected functionality - the full behavior for these classes are covered in the testing fiiles.  Your task is to implement the remaining details for all the classes and methods needed in _array_list.h_ and _array_list_iter.h_. You should use the _scoped_array.h_ class supplied in this repository - do not use your submission from last homework.  But, do compare it to your solution from the previous assignment if you would like to.

## Hints on How to Get Started

1. Start with implementing just the ArrayList class - do the iterators once you get the ArrayList class working as expected.
2. Review what we discussed in class about the Iterator Pattern, and look [here](https://en.wikipedia.org/wiki/Iterator_pattern).
3. Start small.  Maybe try temporarily commenting out most of the test files.  Remember, you'll need to reload your Cmake if you change these files - and DO NOT commit these changes.
4. Comment out as much as needed throughout the code and focus on getting one test to pass.  Then slowly expand as your knowledge and confidence grows.  Again, make sure to only add/commit/push those changes you mean to.

## Reminders

* Ensure that your name, vunetid, email address, and the honor code appear in the header comments of all files that you have altered.

* Do not alter any of the project files!  Work only on those files specified above.  You must use the supplied `CMakeLists.txt` file as is.

* All students are required to abide by the CS 3251 coding standard, [available on the course web page](https://vuse-cs3251.github.io/style-guidelines/) and provided to you on the first day of class. Points will be deducted for not following the coding standard.

* For full credit, your program must compile with a recent version of `clang` or `gcc` and run successfully with the CI platform.
  * The CI build *will* fail if your code is not properly formatted. **This is by design.** If your code is compiling and running successfully, but the build is failing, then your build is most likely failing because your code is not passing the linter. This can be confirmed by checking if a command involving `linter` or `clang-format` in the CI build output log has an exit code of 1.

* Your program(s) should always have an exit code of 0.  A non-zero exit code (generally indicative of a segmentation fault or some other system error) is reason to worry and must be corrected for full points.

* When submitting the assignment, all files that are provided to you, plus your solution files have been submitted. All files necessary to compile and run your program must reside in the GitHub.com repository. 
