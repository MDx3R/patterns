#include "application/usecases/grade_enrollment_use_case.h"
#include "application/repositories/course_repository.h"

class GradeEnrollmentUseCase : public IGradeEnrollmentUseCase
{
private:
    ICourseRepository &courseRepository;

public:
    explicit GradeEnrollmentUseCase(ICourseRepository &repo);
    void execute(const GradeEnrollmentCommand &request) override;
};
