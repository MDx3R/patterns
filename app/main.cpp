#include <iostream>
#include <memory>

#include "domain/services/id_generator.h"
#include "domain/services/clock.h"
#include "application/usecases/create_course_use_case_impl.h"
#include "application/usecases/enroll_student_use_case_impl.h"
#include "application/usecases/grade_enrollment_use_case_impl.h"
#include "application/usecases/get_course_use_case_impl.h"
#include "infrastructure/dispatcher/dispatcher.h"
#include "infrastructure/repositories/inmemory_course_repository.h"
#include "infrastructure/repositories/inmemory_enrollment_repository.h"

int main()
{
    // Common
    auto idGenerator = std::make_shared<IdGenerator>();
    auto clock = std::make_shared<SystemClock>();

    // Создаём репозитории
    auto enrollmentRepo = std::make_shared<InMemoryEnrollmentRepository>();
    auto courseRepo = std::make_shared<InMemoryCourseRepository>(enrollmentRepo);

    // Создаём use case
    auto createCourseUC = std::make_shared<CreateCourseUseCase>(courseRepo, idGenerator);
    auto enrollStudentUC = std::make_shared<EnrollStudentUseCase>(courseRepo, idGenerator);
    auto gradeEnrollmentUC = std::make_shared<GradeEnrollmentUseCase>(courseRepo, clock);
    auto getCourseUC = std::make_shared<GetCourseUseCase>(courseRepo);

    // Создаём Dispatcher и запускаем
    Dispatcher dispatcher(createCourseUC, enrollStudentUC, gradeEnrollmentUC, getCourseUC);
    dispatcher.start();

    return 0;
}
