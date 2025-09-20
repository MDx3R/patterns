#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "application/usecases/create_course_use_case_impl.h"
#include "application/usecases/enroll_student_use_case_impl.h"
#include "application/usecases/grade_enrollment_use_case_impl.h"
#include "application/repositories/course_repository.h"
#include "domain/services/id_generator.h"
#include "domain/services/clock.h"

// Mock ICourseRepository
class MockCourseRepository : public ICourseRepository
{
public:
    MOCK_METHOD(void, save, (const Course &), (override));
    MOCK_METHOD(Course, getById, (int id), (const, override));
    MOCK_METHOD(std::vector<Course>, all, (), (const, override));
};

// Mock IIdGenerator
class MockIdGenerator : public IIdGenerator
{
public:
    MOCK_METHOD(int, getNext, (), (override));
};

// Mock IClock
class MockClock : public IClock
{
public:
    MOCK_METHOD(std::time_t, now, (), (const, override));
};

// Test fixture
class UseCaseTest : public ::testing::Test
{
protected:
    std::shared_ptr<MockCourseRepository> mockCourseRepo;
    std::shared_ptr<MockIdGenerator> mockIdGen;
    std::shared_ptr<MockClock> mockClock;

    void SetUp() override
    {
        mockCourseRepo = std::make_shared<MockCourseRepository>();
        mockIdGen = std::make_shared<MockIdGenerator>();
        mockClock = std::make_shared<MockClock>();
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

// Tests for CreateCourseUseCase
TEST_F(UseCaseTest, CreateCourseUseCase_Execute_CreatesAndSavesCourse)
{
    // Arrange
    CreateCourseCommand command{1001, "Math 101", "Introduction to Mathematics"};
    Course expectedCourse = makeCourse(42, command.title, command.description, command.teacherId);

    EXPECT_CALL(*mockIdGen, getNext()).WillOnce(::testing::Return(42));
    EXPECT_CALL(*mockCourseRepo, save(::testing::Eq(expectedCourse)));

    // Act
    CreateCourseUseCase useCase(mockCourseRepo, mockIdGen);
    int result = useCase.execute(command);

    // Assert
    EXPECT_EQ(result, 42);
}

// Tests for EnrollStudentUseCase
TEST_F(UseCaseTest, EnrollStudentUseCase_Execute_EnrollsStudentAndSavesCourse)
{
    // Arrange
    EnrollStudentCommand command{101, 2001};
    Course course = makeCourse(command.courseId, "Math 101", "Introduction to Mathematics", 1001);
    Enrollment enrollment = makeEnrollment(5001, command.studentId, command.courseId);

    Course expectedCourse = course;
    expectedCourse.addEnrollment(enrollment);

    EXPECT_CALL(*mockCourseRepo, getById(101)).WillOnce(::testing::Return(course));
    EXPECT_CALL(*mockIdGen, getNext()).WillOnce(::testing::Return(5001));
    EXPECT_CALL(*mockCourseRepo, save(::testing::Eq(expectedCourse)));

    // Act
    EnrollStudentUseCase useCase(mockCourseRepo, mockIdGen);
    int result = useCase.execute(command);

    // Assert
    EXPECT_EQ(result, 5001);
}

// Tests for GradeEnrollmentUseCase
TEST_F(UseCaseTest, GradeEnrollment_GradesEnrollmentAndSavesCourse)
{
    // Arrange
    int courseId = 101;
    int enrollmentId = 5001;
    int teacherId = 123;
    int gradeValue = static_cast<int>(Grade::GradeEnum::EXCELLENT);
    std::time_t fakeNow = 1693852800;

    GradeEnrollmentCommand cmd{courseId, enrollmentId, gradeValue};

    Course course = makeCourse(courseId, "Math 101", "Introduction to Mathematics", teacherId);
    Enrollment enrollment = makeEnrollment(enrollmentId, 2001, courseId);
    course.addEnrollment(enrollment);

    Course expectedCourse = course;
    Grade expectedGrade(0, cmd.gradeValue, fakeNow, cmd.teacherId);
    expectedCourse.gradeEnrollment(enrollmentId, expectedGrade);

    EXPECT_CALL(*mockClock, now()).WillOnce(::testing::Return(fakeNow));
    EXPECT_CALL(*mockCourseRepo, getById(courseId)).WillOnce(::testing::Return(course));
    EXPECT_CALL(*mockCourseRepo, save(::testing::Eq(expectedCourse)));

    // Act
    GradeEnrollmentUseCase useCase(mockCourseRepo, mockClock);
    useCase.execute(cmd);

    // Assert
    // No return
}
