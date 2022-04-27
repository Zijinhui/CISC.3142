
#include "user.h"
#include "readerAndWriter.h"
#include "aggregation.h"
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    Reader obj;
    obj.input();
    printf("%d\n",obj.vStudentId.size());
    printf("%d\n", obj.studentStru.size());

    // get unique instructors
    vector<string>instructor = obj.vInstructorId;
    vector<string>::iterator i;
    std::sort(instructor.begin(), instructor.end());
    i = std::unique(instructor.begin(),instructor.begin() + instructor.size());
    instructor.resize(std::distance(instructor.begin(), i));

    //rate(instructor,obj.studentStru);
    //wRate(instructor,obj.studentStru);

    // get unique courNum
    vector<string>courseNum = obj.vCourseNum;
    vector<string>::iterator c;
    std::sort(courseNum.begin(), courseNum.end());
    c = std::unique(courseNum.begin(),courseNum.begin() + courseNum.size());
    courseNum.resize(std::distance(courseNum.begin(), c));    


    courseRate(courseNum,obj.studentStru);
    return 0;
}