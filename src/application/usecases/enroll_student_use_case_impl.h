#include "application/usecases/enroll_student_use_case.h"
#include "application/repositories/course_repository.h"
#include "domain/services/id_generator.h"

class EnrollStudentUseCase : public IEnrollStudentUseCase
{
private:
    ICourseRepository &courseRepository;
    IIdGenerator &idGenerator;

public:
    explicit EnrollStudentUseCase(ICourseRepository &repo, IIdGenerator &gen);
    int execute(const EnrollStudentCommand &request) override;
};
