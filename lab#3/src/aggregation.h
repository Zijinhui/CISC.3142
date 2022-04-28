
#include <vector>
#include <string>
#include <iostream>
#include <cmath>
using namespace std;

int passNum=0;
int totalStu=0;

void rate(vector<string>& uniqueInstructor, vector<Student>& student) {
    ofstream passRateFile;
    passRateFile.open("../output/passRate.txt");
    passRateFile << "Instructor\t" << " Rate\n";
    for(int i=0; i<uniqueInstructor.size();i++) {
        for(int j=0; j<student.size();j++) {

            // if the student takes this instructor's class
            if(uniqueInstructor[i] == student[j].stu_ins.id) {
                totalStu++;

                // Assume the grade under 'C' is consider fail
                if(student[j].grade =="A+"||student[j].grade =="A"||student[j].grade =="A-"||student[j].grade =="B+"||student[j].grade =="B"||student[j].grade =="B-"||student[j].grade =="C+"||student[j].grade =="C") {
                    passNum++;
                }
            }
        }
        passRateFile << "\t" <<uniqueInstructor[i].c_str() << "\t\t " <<ceil((float)passNum/totalStu*10000)/100 << "%" << endl;
    }   
    passRateFile.close();  
}

void wRate(vector<string>& uniqueInstructor, vector<Student>& student) {

    ofstream wRateFile;
    wRateFile.open("../output/wRate.txt");

    wRateFile << "Instructor\t" << "WRate\n";
    for(int i=0; i<uniqueInstructor.size();i++) {
        for(int j=0; j<student.size();j++) {

            // if the student takes this instructor's class
            if(uniqueInstructor[i] == student[j].stu_ins.id) {
                totalStu++;

                // Assume the grade under 'C' is consider fail
                if(student[j].grade =="W"||student[j].grade =="WU"||student[j].grade =="WD") {
                    passNum++;
                }
            }
        }
        wRateFile << " " << uniqueInstructor[i].c_str() << "\t\t" << ceil((float)passNum/totalStu*10000)/100<< "%" << endl;
    }
    wRateFile.close();  
}


void courseRate(vector<string>&courseNum,vector<Student>& student) {
    ofstream courseRateFile;
    courseRateFile.open("../output/courseRate.txt");

    courseRateFile << "Course Number\t" << "Fall Rate\t" << "Spring Rate\n";
    int totalCourse=0;
    int fallNum=0;
    int springNum=0;
    for(int i=0; i<courseNum.size(); i++) {
        for(int j=0; j<student.size();j++) {
            
            //same course number 
            if(courseNum[i]==student[j].stu_course.courseNumber) {
                totalCourse++;
                //Fall term
                if(student[j].stu_term.displayName=="Fall"){
                    fallNum++;          
                }
                //Spring term
                if(student[j].stu_term.displayName=="Spring"){
                    springNum++;
                }
            }
        }
        courseRateFile << "\t" << courseNum[i].c_str() << "\t\t" << ceil((float)fallNum/totalCourse*10000)/100 << "%\t\t  " <<ceil((float)springNum/totalCourse*10000)/100 << "%" <<endl;
    }
    courseRateFile.close();
}
    
