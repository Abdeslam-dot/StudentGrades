# StudentGrades

This is my project for the Systems Programming course. It's a small C++ console program that calculates students' final grades from their homework and exam scores.

## What it does

You can enter students by hand, generate random scores, or load them from a file (`Students.txt`). The program then works out each student's final grade and prints everything in a table.

You choose whether the homework part uses the average or the median.

## How the grade is calculated

$$
Final\ points = 0.4 \times (Average\ of\ HW \mid Median\ of\ HW) + 0.6 \times Exam
$$

So homework counts for 40% and the exam counts for 60%.

## Notes

- Student data is stored in a `Person` class, which follows the rule of three
- Homework results are kept in a `std::vector`, so there can be any number of them
- Work is done on the `v0.1` branch
