#pragma once
#include <memory>
#include <optional>
#include "domain/entity/grade.h"

class Enrollment
{
private:
    int enrollmentId;
    int studentId;
    int courseId;
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
        return enrollmentId == other.enrollmentId &&
               studentId == other.studentId &&
               courseId == other.courseId &&
               grade == other.grade;
    }
};