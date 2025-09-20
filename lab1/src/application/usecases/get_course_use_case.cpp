#include "get_course_use_case_impl.h"

GetCourseUseCase::GetCourseUseCase(std::shared_ptr<ICourseRepository> repo)
    : courseRepository(repo) {}

CourseDTO GetCourseUseCase::execute(int courseId)
{
    Course course = courseRepository->getById(courseId);
    return CourseDTO(course);
}