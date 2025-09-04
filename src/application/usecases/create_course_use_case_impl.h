#include "application/usecases/create_course_use_case.h"
#include "application/repositories/course_repository.h"
#include "domain/services/id_generator.h"

class CreateCourseUseCase : public ICreateCourseUseCase
{
private:
    ICourseRepository &courseRepository;
    IIdGenerator &idGenerator;

public:
    explicit CreateCourseUseCase(ICourseRepository &repo, IIdGenerator &gen);
    int execute(const CreateCourseCommand &request) override;
};