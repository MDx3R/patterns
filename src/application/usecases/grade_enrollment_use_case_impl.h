#include "application/usecases/grade_enrollment_use_case.h"
#include "application/repositories/course_repository.h"
#include "domain/services/clock.h"

class GradeEnrollmentUseCase : public IGradeEnrollmentUseCase
{
private:
    std::shared_ptr<ICourseRepository> courseRepository;
    std::shared_ptr<IClock> clock;

public:
    explicit GradeEnrollmentUseCase(std::shared_ptr<ICourseRepository> repo, std::shared_ptr<IClock> clock);
    void execute(const GradeEnrollmentCommand &request) override;
};
