#include "domain/entity/enrollment.h"

Enrollment::Enrollment(int id, int studentId, int courseId)
    : enrollment_id(id), student_id(studentId), course_id(courseId), grade(std::nullopt) {}

int Enrollment::getId() const
{
    return enrollment_id;
}

int Enrollment::getStudentId() const
{
    return student_id;
}

int Enrollment::getCourseId() const
{
    return course_id;
}

const Grade *Enrollment::getGrade() const
{
    return grade ? &(*grade) : nullptr;
}

void Enrollment::setGrade(std::optional<Grade> newGrade)
{
    grade = std::move(newGrade);
}