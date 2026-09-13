#include <algorithm>
#include <cctype>
#include <iomanip>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

struct Course {
    std::string name;
    std::string gradeInput;
    double gradePoints;
    double creditHours;
};

std::string toUpper(std::string value) {
    std::transform(value.begin(), value.end(), value.begin(), [](unsigned char c) {
        return static_cast<char>(std::toupper(c));
    });
    return value;
}

void clearInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

bool letterToPoints(const std::string& letter, double& points) {
    const std::string grade = toUpper(letter);
    if (grade == "A+" || grade == "A") {
        points = 4.0;
        return true;
    }
    if (grade == "A-") {
        points = 3.7;
        return true;
    }
    if (grade == "B+") {
        points = 3.3;
        return true;
    }
    if (grade == "B") {
        points = 3.0;
        return true;
    }
    if (grade == "B-") {
        points = 2.7;
        return true;
    }
    if (grade == "C+") {
        points = 2.3;
        return true;
    }
    if (grade == "C") {
        points = 2.0;
        return true;
    }
    if (grade == "C-") {
        points = 1.7;
        return true;
    }
    if (grade == "D+") {
        points = 1.3;
        return true;
    }
    if (grade == "D") {
        points = 1.0;
        return true;
    }
    if (grade == "D-") {
        points = 0.7;
        return true;
    }
    if (grade == "F") {
        points = 0.0;
        return true;
    }
    return false;
}

bool parseGrade(const std::string& input, double& points) {
    if (letterToPoints(input, points)) {
        return true;
    }

    try {
        size_t pos = 0;
        const double numeric = std::stod(input, &pos);
        if (pos != input.size()) {
            return false;
        }
        if (numeric < 0.0 || numeric > 4.0) {
            return false;
        }
        points = numeric;
        return true;
    } catch (...) {
        return false;
    }
}

int readPositiveInt(const std::string& prompt) {
    int value = 0;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value && value > 0) {
            clearInput();
            return value;
        }
        std::cout << "Invalid input. Please enter a positive whole number.\n";
        clearInput();
    }
}

double readNonNegativeDouble(const std::string& prompt) {
    double value = 0.0;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value && value >= 0.0) {
            clearInput();
            return value;
        }
        std::cout << "Invalid input. Please enter a number that is 0 or greater.\n";
        clearInput();
    }
}

double readCreditHours(const std::string& prompt) {
    double value = 0.0;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value && value > 0.0) {
            clearInput();
            return value;
        }
        std::cout << "Invalid input. Credit hours must be greater than 0.\n";
        clearInput();
    }
}

double readPreviousCgpa() {
    double value = 0.0;
    while (true) {
        std::cout << "Enter previous CGPA (0 if this is the first semester): ";
        if (std::cin >> value && value >= 0.0 && value <= 4.0) {
            clearInput();
            return value;
        }
        std::cout << "Invalid input. CGPA must be between 0.0 and 4.0.\n";
        clearInput();
    }
}

int main() {
    std::cout << "=====================================\n";
    std::cout << "         CGPA Calculator\n";
    std::cout << "=====================================\n";
    std::cout << "Accepted grades: A+, A, A-, B+, B, B-, C+, C, C-, D+, D, D-, F\n";
    std::cout << "You may also enter numeric grade points from 0.0 to 4.0.\n\n";

    const int courseCount = readPositiveInt("Enter the number of courses this semester: ");
    std::vector<Course> courses;
    courses.reserve(static_cast<std::size_t>(courseCount));

    double semesterCredits = 0.0;
    double semesterGradePoints = 0.0;

    for (int i = 1; i <= courseCount; ++i) {
        Course course;
        std::cout << "\n--- Course " << i << " ---\n";

        std::cout << "Course name: ";
        std::getline(std::cin, course.name);
        if (course.name.empty()) {
            course.name = "Course " + std::to_string(i);
        }

        while (true) {
            std::cout << "Grade: ";
            std::getline(std::cin, course.gradeInput);
            if (parseGrade(course.gradeInput, course.gradePoints)) {
                break;
            }
            std::cout << "Invalid grade. Use a letter grade or a value from 0.0 to 4.0.\n";
        }

        course.creditHours = readCreditHours("Credit hours: ");
        semesterCredits += course.creditHours;
        semesterGradePoints += course.gradePoints * course.creditHours;
        courses.push_back(course);
    }

    const double semesterGpa = semesterGradePoints / semesterCredits;

    std::cout << "\n--- Previous academic record ---\n";
    const double previousCgpa = readPreviousCgpa();
    const double previousCredits = readNonNegativeDouble(
        "Enter previous total credit hours (0 if first semester): ");

    const double overallCredits = previousCredits + semesterCredits;
    const double overallGradePoints =
        (previousCgpa * previousCredits) + semesterGradePoints;
    const double overallCgpa =
        overallCredits > 0.0 ? overallGradePoints / overallCredits : 0.0;

    std::cout << "\n=====================================\n";
    std::cout << "         Semester Report\n";
    std::cout << "=====================================\n";
    std::cout << std::left << std::setw(22) << "Course"
              << std::setw(12) << "Grade"
              << std::setw(12) << "Points"
              << std::setw(12) << "Credits"
              << "Grade Pts\n";
    std::cout << "--------------------------------------------------------------\n";

    std::cout << std::fixed << std::setprecision(2);
    for (const Course& course : courses) {
        std::cout << std::left << std::setw(22) << course.name
                  << std::setw(12) << course.gradeInput
                  << std::setw(12) << course.gradePoints
                  << std::setw(12) << course.creditHours
                  << (course.gradePoints * course.creditHours) << "\n";
    }

    std::cout << "--------------------------------------------------------------\n";
    std::cout << "Semester credits:      " << semesterCredits << "\n";
    std::cout << "Semester grade points: " << semesterGradePoints << "\n";
    std::cout << "Semester GPA:          " << semesterGpa << "\n";
    std::cout << "Previous CGPA:         " << previousCgpa << "\n";
    std::cout << "Previous credits:      " << previousCredits << "\n";
    std::cout << "Overall credits:       " << overallCredits << "\n";
    std::cout << "Final CGPA:            " << overallCgpa << "\n";
    std::cout << "=====================================\n";

    return 0;
}
