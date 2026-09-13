# CGPA Calculator

A command-line C++ program that calculates semester GPA and overall CGPA from course grades and credit hours.

## Features

- Asks how many courses were taken this semester
- For each course, takes the course name, grade, and credit hours
- Converts letter grades to grade points and totals credits and grade points
- Computes semester GPA
- Uses previous CGPA and previous credit hours to compute overall CGPA
- Prints a table of individual course results plus the final CGPA
- Rejects invalid input and asks again

## Grade Scale

| Grade | Points |
| ----- | ------ |
| A+ / A | 4.0 |
| A- | 3.7 |
| B+ | 3.3 |
| B | 3.0 |
| B- | 2.7 |
| C+ | 2.3 |
| C | 2.0 |
| C- | 1.7 |
| D+ | 1.3 |
| D | 1.0 |
| D- | 0.7 |
| F | 0.0 |

Numeric grade points from `0.0` to `4.0` are also accepted.

## How It Is Calculated

```
semester GPA = total (grade points × credit hours) / total semester credits
overall CGPA = (previous CGPA × previous credits + this semester grade points) / total credits
```

If this is the first semester, enter `0` for previous CGPA and previous credits.

## Build

Requires a C++17 compiler (`clang++` or `g++`).

```bash
make
```

Or compile directly:

```bash
clang++ -std=c++17 -Wall -Wextra -o cgpa_calculator cgpa_calculator.cpp
```

## Run

```bash
./cgpa_calculator
```

## Example

```
Enter the number of courses this semester: 3
Course name: Calculus
Grade: A
Credit hours: 3
...
Semester GPA:          3.47
Final CGPA:            3.49
```
