#include "get_course_use_case_impl.h"

GetCourseUseCase::GetCourseUseCase(ICourseRepository &repo)
    : courseRepository(repo) {}

CourseDTO GetCourseUseCase::execute(int courseId)
{
    Course course = courseRepository.getById(courseId);
    return CourseDTO(course);
}