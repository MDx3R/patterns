#pragma once
#include <string>
#include <optional>
#include <domain/entity/grade.h>
#include <vector>

struct EnrollmentDTO
{
    int id;
    int studentId;
    int courseId;
    std::optional<Grade> grade;

    EnrollmentDTO(const Enrollment &enrollment)
        : id(enrollment.getId()),
          studentId(enrollment.getStudentId()),
          courseId(enrollment.getCourseId())
    {
        const Grade *g = enrollment.getGrade();
        if (g)
            grade = *g;
    }
};

struct CourseDTO
{
    int id;
    std::string title;
    std::string description;
    int teacherId;
    std::vector<EnrollmentDTO> enrollments;

    CourseDTO(const Course &course)
        : id(course.getId()),
          title(course.getTitle()),
          description(course.getDescription()),
          teacherId(course.getTeacherId())
    {
        for (const auto &enrollment : course.getEnrollments())
        {
            enrollments.emplace_back(enrollment);
        }
    }
};

class IGetCourseUseCase
{
public:
    virtual ~IGetCourseUseCase() = default;
    virtual CourseDTO execute(int courseId) = 0;
};
