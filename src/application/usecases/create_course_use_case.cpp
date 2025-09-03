#include "create_course_use_case.h"

CreateCourseUseCase::CreateCourseUseCase(ICourseRepository &repo)
    : courseRepository(repo) {}

int CreateCourseUseCase::execute(const CreateCourseCommand &request)
{
    Course course(0, request.title, request.description, request.teacherId);
    int id = courseRepository.save(course);
    return id;
}