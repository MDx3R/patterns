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
    std::shared_ptr<IdGenerator> idGenerator;
    std::shared_ptr<SystemClock> clock;
    std::shared_ptr<InMemoryEnrollmentRepository> enrollmentRepo;
    std::shared_ptr<InMemoryCourseRepository> courseRepo;

    void SetUp() override
    {
        idGenerator = std::make_shared<IdGenerator>();
        clock = std::make_shared<SystemClock>();
        enrollmentRepo = std::make_shared<InMemoryEnrollmentRepository>();
        courseRepo = std::make_shared<InMemoryCourseRepository>(enrollmentRepo);
    }

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
    GradeEnrollmentCommand gradeCommand{courseId, enrollmentId, courseCommand.teacherId, Grade::GradeEnum::EXCELLENT};

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

TEST_F(FunctionalTest, EnrollStudentUseCase_Execute_NoCourseThrows)
{
    // Arrange
    EnrollStudentUseCase enrollStudentUC(courseRepo, idGenerator);
    int courseId = 999;
    EnrollStudentCommand enrollCommand{courseId, 2001};

    // Act & Assert
    EXPECT_THROW(enrollStudentUC.execute(enrollCommand), std::runtime_error);
}

TEST_F(FunctionalTest, GradeEnrollmentUseCase_Execute_NoCourseThrows)
{
    // Arrange
    GradeEnrollmentUseCase gradeEnrollmentUC(courseRepo, clock);

    int teacherId = 1;
    int courseId = 999;
    int enrollmentId = 999;
    int gradeValue = static_cast<int>(Grade::GradeEnum::EXCELLENT);
    GradeEnrollmentCommand gradeCommand{courseId, enrollmentId, 1, Grade::GradeEnum::EXCELLENT};

    // Act & Assert
    EXPECT_THROW(gradeEnrollmentUC.execute(gradeCommand), std::runtime_error);
}

TEST_F(FunctionalTest, GradeEnrollmentUseCase_Execute_NoEnrollmentNoOp)
{
    // Arrange
    CreateCourseUseCase createCourseUC(courseRepo, idGenerator);
    GradeEnrollmentUseCase gradeEnrollmentUC(courseRepo, clock);
    CreateCourseCommand courseCommand{1001, "Math 101", "Introduction to Mathematics"};
    int courseId = createCourseUC.execute(courseCommand);

    int enrollmentId = 999;
    GradeEnrollmentCommand gradeCommand{courseId, enrollmentId, courseCommand.teacherId, Grade::GradeEnum::EXCELLENT};

    // Act
    gradeEnrollmentUC.execute(gradeCommand);

    // Assert
    GetCourseUseCase getCourseUC(courseRepo);
    CourseDTO retrievedCourse = getCourseUC.execute(courseId);
    auto enrollments = retrievedCourse.enrollments;
    bool enrollmentFound = false;
    for (const auto &enrollment : enrollments)
    {
        if (enrollment.id == enrollmentId)
        {
            enrollmentFound = true;
        }
    }
    EXPECT_FALSE(enrollmentFound);
}