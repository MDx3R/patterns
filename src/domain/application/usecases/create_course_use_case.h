#include "include/application/usecases/create_course_use_case.h"
#include "include/application/repositories/course_repository.h"

class CreateCourseUseCase : public ICreateCourseUseCase
{
private:
    ICourseRepository &courseRepository;

public:
    explicit CreateCourseUseCase(ICourseRepository &repo);
    int execute(const CreateCourseCommand &request) override;
};