
//#include "user.h"
#include "readerAndWriter.h"
//#include "aggregation.h"
#include <algorithm>
#include <vector>
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

    //rate(instructor,stu);

    return 0;
}