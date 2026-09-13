CXX := clang++
CXXFLAGS := -std=c++17 -Wall -Wextra -Wpedantic -O2

.PHONY: all clean

all: cgpa_calculator

cgpa_calculator: cgpa_calculator.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

clean:
	rm -f cgpa_calculator
