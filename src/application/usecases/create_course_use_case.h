#include "include/application/usecases/create_course_use_case.h"
#include "include/application/repositories/course_repository.h"
#include "include/domain/services/id_generator.h"

class CreateCourseUseCase : public ICreateCourseUseCase
{
private:
    ICourseRepository &courseRepository;
    IdGenerator &idGenerator;

public:
    explicit CreateCourseUseCase(ICourseRepository &repo, IdGenerator &gen);
    int execute(const CreateCourseCommand &request) override;
};