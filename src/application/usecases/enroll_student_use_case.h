#include "include/application/usecases/enroll_student_use_case.h"
#include "include/application/repositories/course_repository.h"
#include "include/domain/services/id_generator.h"

class EnrollStudentUseCase : public IEnrollStudentUseCase
{
private:
    ICourseRepository &courseRepository;
    IdGenerator &idGenerator;

public:
    explicit EnrollStudentUseCase(ICourseRepository &repo, IdGenerator &gen);
    int execute(const EnrollStudentCommand &request) override;
};
