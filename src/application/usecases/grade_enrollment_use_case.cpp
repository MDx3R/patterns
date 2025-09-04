#include "grade_enrollment_use_case_impl.h"

GradeEnrollmentUseCase::GradeEnrollmentUseCase(ICourseRepository &repo, IClock &clock)
    : courseRepository(repo), clock(clock) {}

void GradeEnrollmentUseCase::execute(const GradeEnrollmentCommand &request)
{
    std::time_t now = clock.now();
    Course course = courseRepository.getById(request.courseId);
    Grade grade(0, request.gradeValue, now, request.teacherId);
    course.gradeEnrollment(request.enrollmentId, grade);
    courseRepository.save(course);
}
