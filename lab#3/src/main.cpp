
#include "user.h"
#include "readerAndWriter.h"
#include "aggregation.h"
#include "enroll.h"
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    Reader obj;
    obj.input();

    // get unique instructors
    vector<string>instructor = obj.vInstructorId;
    vector<string>::iterator i;
    std::sort(instructor.begin(), instructor.end());
    i = std::unique(instructor.begin(),instructor.begin() + instructor.size());
    instructor.resize(std::distance(instructor.begin(), i));

    //pass the list of unique instructors and studentStru into rate()
    rate(instructor,obj.studentStru);
    //pass the list of unique instructors and studentStru into wRate()
    wRate(instructor,obj.studentStru);

    // get unique courNum
    vector<string>courseNum = obj.vCourseNum;
    vector<string>::iterator c;
    std::sort(courseNum.begin(), courseNum.end());
    c = std::unique(courseNum.begin(),courseNum.begin() + courseNum.size());
    courseNum.resize(std::distance(courseNum.begin(), c));    

    //pass the list of unique courseNum and studentStru into courseRate()
    courseRate(courseNum,obj.studentStru);

    // test for enrolling feature
    Enroll new_enroll("111","T16");
    new_enroll.setGrade("A");

    printf("Grade for student %s is %s\n", new_enroll.getId().c_str(), new_enroll.getGrade().c_str());

    return 0;
}