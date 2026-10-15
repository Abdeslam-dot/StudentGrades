# StudentGrades

This is my project for the Systems Programming course. It's a small C++ console program that calculates students' final grades from their homework and exam scores.

## What it does

You can enter students by hand, generate random scores, or load them from a file (`Students.txt`). The program then works out each student's final grade and prints everything in a table.

## How the grade is calculated

$$
Final\ points = 0.4 \times (Average\ of\ HW \mid Median\ of\ HW) + 0.6 \times Exam
$$

So homework counts for 40% and the exam counts for 60%.

## Project structure (since v0.2)

| File | Content |
|---|---|
| `Person.h` / `Person.cpp` | `Person` class (rule of three, `>>` / `<<` overloads, average / median, final grades) |
| `StudentFiles.h` / `StudentFiles.cpp` | Generating, reading, sorting, splitting and writing student files |
| `Timer.h` | `Timer` class (`std::chrono::high_resolution_clock`) for measuring time |
| `main.cpp` | Menu |

## Exception handling (since v0.2)

- File does not exist / cannot be created → `std::runtime_error`
- Bad line in a file (missing name or grades) → `std::invalid_argument`
- Grade outside 0–10 → `std::out_of_range`
- No homework results (average / median impossible) → `std::domain_error`
- Letters typed where a number is expected → `std::invalid_argument`

All of them are caught in `main` with `try { ... } catch (const exception& e)`, so the program prints a message instead of crashing.

## Build & run

```bash
g++ -std=c++17 -O2 main.cpp Person.cpp StudentFiles.cpp -o app
./app
```

Menu:
1. Enter data manually
2. Generate random scores
3. Read data from file
4. **Generate test files**: `students1000.txt` … `students10000000.txt`, named `Name1 Surname1`, `Name2 Surname2`, …, with 10 homework and 1 exam each
5. **Speed analysis**: read → sort by final points → split into **failed** (< 5.0) and **passed** (≥ 5.0) → write `..._failed.txt` and `..._passed.txt`, timing every step

## v0.25: `std::vector` vs `std::list` vs `std::deque`

The file functions in `StudentFiles.h` are templates, so the same code works with all three containers. Option 5 asks which container to test.

`std::list` has no random-access iterators, so it uses `list::sort()`. `std::vector` and `std::deque` use `std::sort`.

Test PC: Linux, 2 vCPU, g++ 13 `-O2`. Times are in seconds.

### Reading from file
| Records | vector | list | deque |
|---:|---:|---:|---:|
| 1 000 | 0.0026 | 0.0026 | 0.0026 |
| 10 000 | 0.0285 | 0.0216 | 0.0202 |
| 100 000 | 0.4522 | 0.3063 | 0.3308 |
| 1 000 000 | 3.0584 | 2.2596 | 2.6442 |
| 10 000 000 | 26.9038 | 26.6543 | 29.9347 |

### Sorting
| Records | vector | list | deque |
|---:|---:|---:|---:|
| 1 000 | 0.0003 | 0.0001 | 0.0010 |
| 10 000 | 0.0037 | 0.0026 | 0.0040 |
| 100 000 | 0.0958 | 0.0732 | 0.0699 |
| 1 000 000 | 0.8792 | 1.3816 | 1.0615 |
| 10 000 000 | 9.6344 | 19.0773 | 11.2997 |

### Splitting into failed / passed
| Records | vector | list | deque |
|---:|---:|---:|---:|
| 1 000 | 0.0002 | 0.0002 | 0.0001 |
| 10 000 | 0.0022 | 0.0037 | 0.0006 |
| 100 000 | 0.0355 | 0.0511 | 0.0166 |
| 1 000 000 | 0.3316 | 0.5289 | 0.2169 |
| 10 000 000 | 3.0962 | 5.0272 | 1.9055 |

### Writing two files
| Records | vector | list | deque |
|---:|---:|---:|---:|
| 1 000 | 0.0008 | 0.0007 | 0.0006 |
| 10 000 | 0.0054 | 0.0052 | 0.0077 |
| 100 000 | 0.0622 | 0.0935 | 0.1013 |
| 1 000 000 | 0.5871 | 0.7925 | 0.9178 |
| 10 000 000 | 4.8886 | 6.1886 | 6.1170 |

### Total
| Records | vector | list | deque |
|---:|---:|---:|---:|
| 1 000 | 0.0038 | 0.0036 | 0.0044 |
| 10 000 | 0.0399 | 0.0331 | 0.0326 |
| 100 000 | 0.6458 | 0.5242 | 0.5187 |
| 1 000 000 | 4.8563 | 4.9627 | 4.8406 |
| 10 000 000 | **44.5230** | **56.9474** | **49.2571** |

**Conclusions:**
- Up to 100 000 students, the container makes almost no difference.
- **Reading:** the time is dominated by parsing the file, so all three containers are similar.
- **Sorting:** `list` is about 2× slower than `vector` on 10 M records. Its elements are scattered in memory, which uses the CPU cache poorly. `vector` is the fastest because its memory is contiguous.
- **Splitting:** `deque` is the fastest because `push_back` never moves existing elements. `vector` sometimes reallocates and copies everything. `list` allocates a node for every student.
- **Overall:** `vector` was the fastest on the biggest file and is the best general choice. `list` was clearly the slowest for this task.
