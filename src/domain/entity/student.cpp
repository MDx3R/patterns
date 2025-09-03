#include "student.h"

Student::Student(int id, const std::string &name)
    : student_id(id), name(name) {}

int Student::getId() const
{
    return student_id;
}

std::string Student::getName() const
{
    return name;
}

void Student::setName(const std::string &newName)
{
    name = newName;
}