#include <string>
#include <domain/entity/grade.h>

struct GradeEnrollmentCommand
{
    int courseId;
    int enrollmentId;
    int teacherId;
    domain::Grade::GradeEnum gradeValue;
};

class IGradeEnrollmentUseCase
{
public:
    virtual ~IGradeEnrollmentUseCase() = default;
    virtual void execute(const GradeEnrollmentCommand &request) = 0;
};
