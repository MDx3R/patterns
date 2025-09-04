#include "application/usecases/grade_enrollment_use_case.h"
#include "application/repositories/course_repository.h"
#include "domain/services/clock.h"

class GradeEnrollmentUseCase : public IGradeEnrollmentUseCase
{
private:
    ICourseRepository &courseRepository;
    IClock &clock;

public:
    explicit GradeEnrollmentUseCase(ICourseRepository &repo, IClock &clock);
    void execute(const GradeEnrollmentCommand &request) override;
};
