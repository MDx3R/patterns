#pragma once
#include <memory>
#include <optional>
#include "domain/entity/grade.h"

class Enrollment
{
private:
    int enrollment_id;
    int student_id;
    int course_id;
    std::optional<Grade> grade;

public:
    Enrollment() = default;
    Enrollment(int id, int studentId, int courseId);

    int getId() const;
    int getStudentId() const;
    int getCourseId() const;
    const Grade *getGrade() const;

    void setGrade(std::optional<Grade> newGrade);

    bool operator==(const Enrollment &other) const
    {
        return enrollment_id == other.enrollment_id &&
               student_id == other.student_id &&
               course_id == other.course_id &&
               grade == other.grade;
    }
};