#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "infrastructure/repositories/inmemory_course_repository.h"
#include "infrastructure/repositories/inmemory_enrollment_repository.h"

// Test fixture for integration tests
class InMemoryRepositoriesTest : public ::testing::Test
{
protected:
    std::shared_ptr<InMemoryEnrollmentRepository> enrollmentRepo;
    std::shared_ptr<InMemoryCourseRepository> courseRepo;

    void SetUp() override
    {
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

// Test InMemoryEnrollmentRepository::save
TEST_F(InMemoryRepositoriesTest, EnrollmentRepository_Save_StoresEnrollment)
{
    // Arrange
    Enrollment enrollment = makeEnrollment(1, 1001, 101);

    // Act
    enrollmentRepo->save(enrollment);

    // Assert
    Enrollment retrieved = enrollmentRepo->getById(1);
    EXPECT_EQ(retrieved.getId(), 1);
    EXPECT_EQ(retrieved.getStudentId(), 1001);
    EXPECT_EQ(retrieved.getCourseId(), 101);
}

// Test InMemoryEnrollmentRepository::save updates existing enrollment
TEST_F(InMemoryRepositoriesTest, EnrollmentRepository_Save_UpdatesExistingEnrollment)
{
    // Arrange
    Enrollment enrollment1 = makeEnrollment(1, 1001, 101);
    enrollmentRepo->save(enrollment1);

    Enrollment enrollment2 = makeEnrollment(1, 1002, 101); // Same ID, different student

    // Act
    enrollmentRepo->save(enrollment2);

    // Assert
    Enrollment retrieved = enrollmentRepo->getById(1);
    EXPECT_EQ(retrieved.getStudentId(), 1002); // Updated studentId
    EXPECT_EQ(retrieved.getCourseId(), 101);
}

// Test InMemoryEnrollmentRepository::getById throws for non-existent enrollment
TEST_F(InMemoryRepositoriesTest, EnrollmentRepository_GetById_ThrowsForNonExistent)
{
    // Act & Assert
    EXPECT_THROW(enrollmentRepo->getById(999), std::runtime_error);
}

// Test InMemoryEnrollmentRepository::existsById
TEST_F(InMemoryRepositoriesTest, EnrollmentRepository_ExistsById_ReturnsCorrectly)
{
    // Arrange
    Enrollment enrollment = makeEnrollment(1, 1001, 101);
    enrollmentRepo->save(enrollment);

    // Act & Assert
    EXPECT_TRUE(enrollmentRepo->existsById(1));
    EXPECT_FALSE(enrollmentRepo->existsById(999));
}

// Test InMemoryEnrollmentRepository::byCourse
TEST_F(InMemoryRepositoriesTest, EnrollmentRepository_ByCourse_ReturnsCorrectEnrollments)
{
    // Arrange
    Enrollment enrollment1 = makeEnrollment(1, 1001, 101);
    Enrollment enrollment2 = makeEnrollment(2, 1002, 101);
    Enrollment enrollment3 = makeEnrollment(3, 1003, 102);
    enrollmentRepo->save(enrollment1);
    enrollmentRepo->save(enrollment2);
    enrollmentRepo->save(enrollment3);

    // Act
    auto enrollments = enrollmentRepo->byCourse(101);

    // Assert
    EXPECT_EQ(enrollments.size(), 2);
    EXPECT_EQ(enrollments[0].getId(), 1);
    EXPECT_EQ(enrollments[1].getId(), 2);

    auto empty = enrollmentRepo->byCourse(999);
    EXPECT_TRUE(empty.empty());
}

// Test InMemoryEnrollmentRepository::byStudent
TEST_F(InMemoryRepositoriesTest, EnrollmentRepository_ByStudent_ReturnsCorrectEnrollments)
{
    // Arrange
    Enrollment enrollment1 = makeEnrollment(1, 1001, 101);
    Enrollment enrollment2 = makeEnrollment(2, 1001, 102);
    Enrollment enrollment3 = makeEnrollment(3, 1003, 102);
    enrollmentRepo->save(enrollment1);
    enrollmentRepo->save(enrollment2);
    enrollmentRepo->save(enrollment3);

    // Act
    auto enrollments = enrollmentRepo->byStudent(1001);

    // Assert
    EXPECT_EQ(enrollments.size(), 2);
    EXPECT_EQ(enrollments[0].getId(), 1);
    EXPECT_EQ(enrollments[1].getId(), 2);

    auto empty = enrollmentRepo->byStudent(999);
    EXPECT_TRUE(empty.empty());
}

// Test InMemoryCourseRepository::save
TEST_F(InMemoryRepositoriesTest, CourseRepository_Save_StoresCourseAndEnrollments)
{
    // Arrange
    Enrollment enrollment = makeEnrollment(1, 1001, 101);
    Course course = makeCourse(101, "Math 101", "Introduction to Mathematics", 2001);
    course.addEnrollment(enrollment);

    // Act
    courseRepo->save(course);

    // Assert
    Course retrieved = courseRepo->getById(101);
    EXPECT_EQ(retrieved.getId(), 101);
    EXPECT_EQ(retrieved.getTitle(), "Math 101");
    EXPECT_EQ(retrieved.getDescription(), "Introduction to Mathematics");
    EXPECT_EQ(retrieved.getTeacherId(), 2001);
    EXPECT_EQ(retrieved.getEnrollments().size(), 1);
    EXPECT_EQ(retrieved.getEnrollments()[0].getId(), 1);
}

// Test InMemoryCourseRepository::save updates existing course
TEST_F(InMemoryRepositoriesTest, CourseRepository_Save_UpdatesExistingCourse)
{
    // Arrange
    Course course1 = makeCourse(101, "Math 101", "Introduction to Mathematics", 2001);
    courseRepo->save(course1);

    Course course2 = makeCourse(101, "Math 102", "Advanced Mathematics", 2002);

    // Act
    courseRepo->save(course2);

    // Assert
    Course retrieved = courseRepo->getById(101);
    EXPECT_EQ(retrieved.getTitle(), "Math 102");
    EXPECT_EQ(retrieved.getDescription(), "Advanced Mathematics");
    EXPECT_EQ(retrieved.getTeacherId(), 2002);
}

// Test InMemoryCourseRepository::getById throws for non-existent course
TEST_F(InMemoryRepositoriesTest, CourseRepository_GetById_ThrowsForNonExistent)
{
    // Act & Assert
    EXPECT_THROW(courseRepo->getById(999), std::runtime_error);
}

// Test InMemoryCourseRepository::all
TEST_F(InMemoryRepositoriesTest, CourseRepository_All_ReturnsAllCoursesWithEnrollments)
{
    // Arrange
    Enrollment enrollment1 = makeEnrollment(1, 1001, 101);
    Enrollment enrollment2 = makeEnrollment(2, 1002, 102);
    Course course1 = makeCourse(101, "Math 101", "Introduction to Mathematics", 2001);
    Course course2 = makeCourse(102, "Physics 101", "Introduction to Physics", 2002);
    course1.addEnrollment(enrollment1);
    course2.addEnrollment(enrollment2);

    courseRepo->save(course1);
    courseRepo->save(course2);

    // Act
    auto courses = courseRepo->all();

    // Assert
    EXPECT_EQ(courses.size(), 2);

    auto course101 = courses[0].getId() == 101 ? courses[0] : courses[1];
    auto course102 = courses[0].getId() == 102 ? courses[0] : courses[1];

    EXPECT_EQ(course101.getId(), 101);
    EXPECT_EQ(course101.getEnrollments().size(), 1);
    EXPECT_EQ(course101.getEnrollments()[0].getId(), 1);

    EXPECT_EQ(course102.getId(), 102);
    EXPECT_EQ(course102.getEnrollments().size(), 1);
    EXPECT_EQ(course102.getEnrollments()[0].getId(), 2);
}

// Test integration of saving course with multiple enrollments
TEST_F(InMemoryRepositoriesTest, CourseRepository_SaveAndRetrieve_MultipleEnrollments)
{
    // Arrange
    Enrollment enrollment1 = makeEnrollment(1, 1001, 101);
    Enrollment enrollment2 = makeEnrollment(2, 1002, 101);
    Course course = makeCourse(101, "Math 101", "Introduction to Mathematics", 2001);
    course.addEnrollment(enrollment1);
    course.addEnrollment(enrollment2);

    // Act
    courseRepo->save(course);

    // Assert
    Course retrieved = courseRepo->getById(101);
    EXPECT_EQ(retrieved.getEnrollments().size(), 2);
    EXPECT_EQ(retrieved.getEnrollments()[0].getId(), 1);
    EXPECT_EQ(retrieved.getEnrollments()[1].getId(), 2);
}