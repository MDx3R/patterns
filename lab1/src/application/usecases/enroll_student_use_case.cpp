#include "enroll_student_use_case_impl.h"

EnrollStudentUseCase::EnrollStudentUseCase(std::shared_ptr<ICourseRepository> repo, std::shared_ptr<IIdGenerator> gen)
    : courseRepository(repo), idGenerator(gen) {}

int EnrollStudentUseCase::execute(const EnrollStudentCommand &request)
{
    Course course = courseRepository->getById(request.courseId);
    Enrollment enrollement(idGenerator->getNext(), request.studentId, course.getId());
    course.addEnrollment(enrollement);
    courseRepository->save(course);
    return enrollement.getId();
}
