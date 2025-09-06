#include "create_course_use_case_impl.h"

CreateCourseUseCase::CreateCourseUseCase(std::shared_ptr<ICourseRepository> repo, std::shared_ptr<IIdGenerator> gen)
    : courseRepository(repo), idGenerator(gen) {}

int CreateCourseUseCase::execute(const CreateCourseCommand &request)
{
    Course course(idGenerator->getNext(), request.title, request.description, request.teacherId);
    courseRepository->save(course);
    return course.getId();
}