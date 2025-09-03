#include "grade_enrollment_use_case.h"

GradeEnrollmentUseCase::GradeEnrollmentUseCase(ICourseRepository &repo)
    : courseRepository(repo) {}

void GradeEnrollmentUseCase::execute(const GradeEnrollmentCommand &request)
{
    std::time_t now = std::time(nullptr);
    Course course = courseRepository.getById(request.courseId);
    course.gradeEnrollment(request.enrollmentId, Grade(0, request.gradeValue, now, request.teacherId));
}
