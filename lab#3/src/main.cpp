#include "readerAndWriter.h"
using namespace std; 

//extern vector<string> vStudentId; 

int main() {
    Reader obj;
    obj.input();
    printf("%lu\n",obj.vStudentId.size());
    printf("%lu\n", obj.studentStru.size());
    //get unique students
    // vector<string>student = obj.vStudentId;
    // vector<string>::iterator s;
    // std::sort(student.begin(), student.end());
    // s = std::unique(student.begin(),student.begin() + student.size());
    // student.resize(std::distance(student.begin(), s));

    // for(int i=0; i<student.size();i++) {
    //     printf("%s\n", student[i].c_str());
    // }

    // vector<Student>studentStru;
    // for(int j=0; j<obj.vStudentId.size(); j++) {
    //     struct Student stu;
    //     struct Course course;
    //     struct Instructor instructor;
    //     struct Term term;

    //     course.courseNumber = obj.courseNum[j];
    //     course.sectionCode = obj.sectionId[j];

    //     stu.id = obj.vStudentId[j];
    //     stu.Course = course;
    //     stu.grade = obj.vGrade[j];
    //     studentStru.push_back(s);
    // }
    // printf("%s",studentStru[0].id.c_str());

    // vector<Instructor>instructor;
    // vector<Term>term;
    // vector<Course>course;

    //std::sort(student.begin(), student.end());

    //get unique students
    vector<string>instructor = obj.vInstructorId;
    vector<string>::iterator i;
    std::sort(instructor.begin(), instructor.end());
    i = std::unique(instructor.begin(),instructor.begin() + instructor.size());
    instructor.resize(std::distance(instructor.begin(), i));

    for(int i=0; i<instructor.size();i++) {
        printf("%s\n", instructor[i].c_str());
    }

    // for(int i=0; i<obj.studentStru.size(); i++) {
        
    // }

    return 0;
}