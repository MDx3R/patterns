#include <iostream>

#include "domain/services/id_generator.h"
#include "domain/services/clock.h"
#include "application/usecases/create_course_use_case_impl.h"
#include "application/usecases/enroll_student_use_case_impl.h"
#include "application/usecases/grade_enrollment_use_case_impl.h"
#include "infrastructure/dispatcher/dispatcher.h"
#include "infrastructure/repositories/inmemory_course_repository.h"
#include "infrastructure/repositories/inmemory_enrollment_repository.h"

int main()
{
    // Common
    auto idGenerator = IdGenerator();
    auto clock = SystemClock();

    // Создаём репозитории
    auto enrollmentRepo = InMemoryEnrollmentRepository();
    auto courseRepo = InMemoryCourseRepository(enrollmentRepo);

    // Создаём use case
    auto createCourseUC = CreateCourseUseCase(courseRepo, idGenerator);
    auto enrollStudentUC = EnrollStudentUseCase(courseRepo, idGenerator);
    auto gradeEnrollmentUC = GradeEnrollmentUseCase(courseRepo, clock);

    // Создаём Dispatcher и запускаем
    Dispatcher dispatcher(createCourseUC, enrollStudentUC, gradeEnrollmentUC);
    dispatcher.start();

    return 0;
}
