#include "create_course_use_case_impl.h"

CreateCourseUseCase::CreateCourseUseCase(ICourseRepository &repo, IIdGenerator &gen)
    : courseRepository(repo), idGenerator(gen) {}

int CreateCourseUseCase::execute(const CreateCourseCommand &request)
{
    Course course(idGenerator.getNext(), request.title, request.description, request.teacherId);
    courseRepository.save(course);
    return course.getId();
}