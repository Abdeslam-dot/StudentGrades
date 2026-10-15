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

## Speed analysis — v0.2 (`std::vector`)

Test PC: Linux, 2 vCPU, g++ 13 `-O2`. Times are in seconds.

| Records | Read | Sort | Split | Write 2 files | **Total** |
|---:|---:|---:|---:|---:|---:|
| 1 000 | 0.0021 | 0.0002 | 0.0002 | 0.0008 | **0.0033** |
| 10 000 | 0.0255 | 0.0041 | 0.0025 | 0.0059 | **0.0380** |
| 100 000 | 0.3204 | 0.0632 | 0.0280 | 0.0557 | **0.4673** |
| 1 000 000 | 2.5176 | 0.9693 | 0.4274 | 0.6157 | **4.5301** |
| 10 000 000 | 28.5089 | 9.7847 | 3.0467 | 5.3214 | **46.6617** |

**Conclusions:**
- Time grows almost linearly with the number of students.
- Reading the file is the slowest step (about 60 % of the total), because every line has to be parsed.
- Sorting comes second and grows a bit faster than linearly (O(n log n)).
- Splitting and writing are comparatively cheap.
