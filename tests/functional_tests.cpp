#include <gtest/gtest.h>
#include "domain/services/id_generator.h"
#include "domain/services/clock.h"
#include "application/usecases/create_course_use_case_impl.h"
#include "application/usecases/enroll_student_use_case_impl.h"
#include "application/usecases/grade_enrollment_use_case_impl.h"
#include "application/usecases/get_course_use_case_impl.h"
#include "infrastructure/repositories/inmemory_course_repository.h"
#include "infrastructure/repositories/inmemory_enrollment_repository.h"

// Test fixture for functional tests
class FunctionalTest : public ::testing::Test
{
protected:
    IdGenerator idGenerator;
    SystemClock clock;
    InMemoryEnrollmentRepository enrollmentRepo;
    InMemoryCourseRepository courseRepo;

    FunctionalTest() : courseRepo(enrollmentRepo) {}

    Course makeCourse(int id, const std::string &name, const std::string &desc, int teacherId)
    {
        return Course(id, name, desc, teacherId);
    }

    Enrollment makeEnrollment(int id, int studentId, int courseId)
    {
        return Enrollment(id, studentId, courseId);
    }
};

// Test for CreateCourseUseCase
TEST_F(FunctionalTest, CreateCourseUseCase_Execute_CreatesAndSavesCourse)
{
    // Arrange
    CreateCourseUseCase createCourseUC(courseRepo, idGenerator);
    CreateCourseCommand command{1001, "Math 101", "Introduction to Mathematics"};
    Course expectedCourse = makeCourse(1, command.title, command.description, command.teacherId);

    // Act
    int courseId = createCourseUC.execute(command);

    // Assert
    GetCourseUseCase getCourseUC(courseRepo);
    CourseDTO retrievedCourse = getCourseUC.execute(courseId);
    EXPECT_EQ(retrievedCourse.id, courseId);
    EXPECT_EQ(retrievedCourse.title, command.title);
    EXPECT_EQ(retrievedCourse.description, command.description);
    EXPECT_EQ(retrievedCourse.teacherId, command.teacherId);
}

// Test for EnrollStudentUseCase
TEST_F(FunctionalTest, EnrollStudentUseCase_Execute_EnrollsStudentAndSavesCourse)
{
    // Arrange
    CreateCourseUseCase createCourseUC(courseRepo, idGenerator);
    EnrollStudentUseCase enrollStudentUC(courseRepo, idGenerator);
    CreateCourseCommand courseCommand{1001, "Math 101", "Introduction to Mathematics"};
    int courseId = createCourseUC.execute(courseCommand);
    EnrollStudentCommand enrollCommand{courseId, 2001};

    // Act
    int enrollmentId = enrollStudentUC.execute(enrollCommand);

    // Assert
    GetCourseUseCase getCourseUC(courseRepo);
    CourseDTO retrievedCourse = getCourseUC.execute(courseId);
    auto enrollments = retrievedCourse.enrollments;
    bool enrollmentFound = false;
    for (const auto &enrollment : enrollments)
    {
        if (enrollment.id == enrollmentId && enrollment.studentId == enrollCommand.studentId)
        {
            enrollmentFound = true;
            break;
        }
    }
    EXPECT_TRUE(enrollmentFound);
}

// Test for GradeEnrollmentUseCase
TEST_F(FunctionalTest, GradeEnrollmentUseCase_GradesEnrollmentAndSavesCourse)
{
    // Arrange
    CreateCourseUseCase createCourseUC(courseRepo, idGenerator);
    EnrollStudentUseCase enrollStudentUC(courseRepo, idGenerator);
    GradeEnrollmentUseCase gradeEnrollmentUC(courseRepo, clock);
    CreateCourseCommand courseCommand{1001, "Math 101", "Introduction to Mathematics"};
    int courseId = createCourseUC.execute(courseCommand);
    EnrollStudentCommand enrollCommand{courseId, 2001};
    int enrollmentId = enrollStudentUC.execute(enrollCommand);
    int gradeValue = static_cast<int>(Grade::GradeEnum::EXCELLENT);
    GradeEnrollmentCommand gradeCommand{courseId, enrollmentId, gradeValue};

    // Act
    gradeEnrollmentUC.execute(gradeCommand);

    // Assert
    GetCourseUseCase getCourseUC(courseRepo);
    CourseDTO retrievedCourse = getCourseUC.execute(courseId);
    auto enrollments = retrievedCourse.enrollments;
    bool gradeFound = false;
    for (const auto &enrollment : enrollments)
    {
        if (enrollment.id == enrollmentId)
        {
            auto grade = enrollment.grade;
            if (grade.has_value())
            {
                gradeFound = true;
            }
            break;
        }
    }
    EXPECT_TRUE(gradeFound);
}