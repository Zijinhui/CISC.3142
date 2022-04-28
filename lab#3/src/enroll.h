#include <string>
using namespace std;

// calss for new student's enrollment
class Enroll{
    private:
        string emplid;
        string grade;
        string courseNum;

        public:
             Enroll(string stuId,string course){
                emplid = stuId;
                courseNum = course;
        }

        void setGrade(string g) {
            grade = g;
        }
        
        string getGrade(){
            return grade;
        }

        string getId(){
            return emplid;
        }
};