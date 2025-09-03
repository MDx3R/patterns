#include "course.h"

Course::Course(int id, const std::string &title, const std::string &description, int teacherId)
    : course_id(id), teacher_id(teacherId), title(title), description(description) {}

Course::Course(int id, const std::string &title, const std::string &description,
               int teacherId, const std::vector<Enrollment> &enrollments)
    : course_id(id), teacher_id(teacherId), title(title), description(description), enrollments(enrollments) {}

int Course::getId() const
{
    return course_id;
}

int Course::getTeacherId() const
{
    return teacher_id;
}

std::string Course::getTitle() const
{
    return title;
}

std::string Course::getDescription() const
{
    return description;
}

std::vector<Enrollment> Course::getEnrollments() const
{
    return enrollments;
}

void Course::setTitle(const std::string &newTitle)
{
    title = newTitle;
}

void Course::setDescription(const std::string &newDescription)
{
    description = newDescription;
}

void Course::addEnrollment(const Enrollment &enrollment)
{
    enrollments.push_back(enrollment);
}

void Course::gradeEnrollment(int enrollmentId, Grade &grade)
{
    for (auto &enrollment : enrollments)
    {
        if (enrollment.getId() == enrollmentId)
        {
            enrollment.setGrade(std::move(grade));
            break;
        }
    }
}