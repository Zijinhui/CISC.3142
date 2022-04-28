#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

class Reader {
public:
    // Instance variables
    string studentId, courseNum, instructorId, termId, sectionId, grade;
    vector<string>vStudentId;
    vector<string>vCourseNum;
    vector<string>vInstructorId;
    vector<string>vTermId;
    vector<string>vSectionId;
    vector<string>vGrade;
    vector<string>files;

    vector<Student>studentStru;

    // Function declaration of input() to input info
    void input();

    // Function declaration of output()
    int output();
};

void Reader::input() {
    files.push_back("..\data\1115.csv");
    files.push_back("..\data\3115.csv");
    files.push_back("..\data\3130.csv");
    
    for(int j=0; j<files.size();j++) {
        
        struct Student stu;
        struct Course course;
        struct Instructor ins;
        struct Term term;

        ifstream file;
        file.open(files[j].c_str());

        if (!file.fail()) {
            string line;
        
            // skip the first line
            getline(file, line);

            //while the end of file is NOT reached
            while(getline(file, line)) {
                stringstream eachLine(line);
               
                // Fields: studentId, courseNum, instructorId, termId, sectionId, grade
                getline(eachLine, studentId, ',');
                vStudentId.push_back(studentId);
            
                getline(eachLine, courseNum, ',');
                vCourseNum.push_back(courseNum);

                getline(eachLine, instructorId, ',');
                vInstructorId.push_back(instructorId);

                getline(eachLine, termId, ',');
                vTermId.push_back(termId);
                 
                 // Check the section term base on the given code list
                 if (termId=="T04"||termId=="T08"||termId=="T12"||termId=="T16"||termId=="T20"||termId=="T23"){
                            term.displayName = "Fall";
                        } else {
                            term.displayName = "Spring";
                        }

                getline(eachLine, sectionId, ',');
                vSectionId.push_back(sectionId);

                getline(eachLine, grade, '\n');
                vGrade.push_back(grade);

                //import current line into Student Struct
                stu.id = studentId;

                course.courseNumber = courseNum;
                course.sectionCode = sectionId;
                stu.stu_course = course;

                stu.grade = grade;

                ins.id = instructorId;
                ins.course = courseNum;
                stu.stu_ins = ins;

                term.id = sectionId;
                stu.stu_term = term;
                studentStru.push_back(stu);
            }

            file.close();
        } else {
            printf("Unable to open file\n");
        }
    }
}

