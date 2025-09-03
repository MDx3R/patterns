#include "include/application/usecases/enroll_student_use_case.h"
#include "include/application/repositories/course_repository.h"

class EnrollStudentUseCase : public IEnrollStudentUseCase
{
private:
    ICourseRepository &courseRepository;

public:
    explicit EnrollStudentUseCase(ICourseRepository &repo);
    int execute(const EnrollStudentCommand &request) override;
};
