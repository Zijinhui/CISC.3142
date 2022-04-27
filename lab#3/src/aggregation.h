
#include <vector>
#include <string>
using namespace std;

int passNum=0;
int totalStu=0;

void rate(vector<string>& uniqueInstructor, vector<Student>& student) {
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
        printf("%s %.2f\n",uniqueInstructor[i].c_str(), (float)passNum/totalStu);
    }  
}

void wRate(vector<string>& uniqueInstructor, vector<Student>& student) {
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
        printf("%s %.2f\n",uniqueInstructor[i].c_str(), (float)passNum/totalStu);
    }  
}


void courseRate(vector<string>&courseNum,vector<Student>& student) {
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
        printf("%d %d  %d\n",fallNum, springNum, totalCourse);
        printf("%s Fall: %f  Spring: %f \n",courseNum[i].c_str(), (float)fallNum/totalCourse,(float)springNum/totalCourse);
    }
}
    
