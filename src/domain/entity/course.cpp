#include "domain/entity/course.h"

Course::Course(int id, const std::string &title, const std::string &description, int teacherId)
    : courseId(id), teacherId(teacherId), title(title), description(description) {}

Course::Course(int id, const std::string &title, const std::string &description,
               int teacherId, const std::vector<Enrollment> &enrollments)
    : courseId(id), teacherId(teacherId), title(title), description(description), enrollments(enrollments) {}

int Course::getId() const
{
    return courseId;
}

int Course::getTeacherId() const
{
    return teacherId;
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

void Course::clearEnrollments()
{
    enrollments.clear();
}

bool Course::operator==(const Course &other) const
{
    return courseId == other.courseId &&
           title == other.title &&
           description == other.description &&
           teacherId == other.teacherId &&
           enrollments == other.enrollments;
}
