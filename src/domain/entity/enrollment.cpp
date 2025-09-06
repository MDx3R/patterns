#include "domain/entity/enrollment.h"

Enrollment::Enrollment(int id, int studentId, int courseId)
    : enrollmentId(id), studentId(studentId), courseId(courseId), grade(std::nullopt) {}

int Enrollment::getId() const
{
    return enrollmentId;
}

int Enrollment::getStudentId() const
{
    return studentId;
}

int Enrollment::getCourseId() const
{
    return courseId;
}

const Grade *Enrollment::getGrade() const
{
    return grade ? &(*grade) : nullptr;
}

void Enrollment::setGrade(std::optional<Grade> newGrade)
{
    grade = std::move(newGrade);
}

bool Enrollment::operator==(const Enrollment &other) const
{
    return enrollmentId == other.enrollmentId &&
           studentId == other.studentId &&
           courseId == other.courseId &&
           grade == other.grade;
}