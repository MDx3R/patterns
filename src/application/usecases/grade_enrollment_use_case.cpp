#include "grade_enrollment_use_case_impl.h"

GradeEnrollmentUseCase::GradeEnrollmentUseCase(ICourseRepository &repo)
    : courseRepository(repo) {}

void GradeEnrollmentUseCase::execute(const GradeEnrollmentCommand &request)
{
    std::time_t now = std::time(nullptr);
    Course course = courseRepository.getById(request.courseId);
    Grade grade(0, request.gradeValue, now, request.teacherId);
    course.gradeEnrollment(request.enrollmentId, grade);
}
