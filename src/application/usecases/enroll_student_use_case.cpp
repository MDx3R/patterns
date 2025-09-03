#include "enroll_student_use_case.h"

EnrollStudentUseCase::EnrollStudentUseCase(ICourseRepository &repo)
    : courseRepository(repo) {}

int EnrollStudentUseCase::execute(const EnrollStudentCommand &request)
{
    Course course = courseRepository.getById(request.courseId);
    course.addEnrollment(Enrollment(0, request.studentId, course.getId()));
    courseRepository.save(course);
    return 0; // TODO: EnrollmentID
}
