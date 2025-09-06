#include <memory>
#include "application/usecases/create_course_use_case.h"
#include "application/repositories/course_repository.h"
#include "domain/services/id_generator.h"

class CreateCourseUseCase : public ICreateCourseUseCase
{
private:
    std::shared_ptr<ICourseRepository> courseRepository;
    std::shared_ptr<IIdGenerator> idGenerator;

public:
    explicit CreateCourseUseCase(std::shared_ptr<ICourseRepository> repo, std::shared_ptr<IIdGenerator> gen);
    int execute(const CreateCourseCommand &request) override;
};