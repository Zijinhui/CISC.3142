#include <string>
using namespace std;

struct Instructor {
    string id;
    string course;
};

struct Term {
    string id;
    string displayName;
};

struct Course {
    string courseNumber;
    string sectionCode;
};

struct Student {
    string id;
    struct Course stu_course;
    string grade;
    struct Instructor stu_ins;
    struct Term stu_term;
};