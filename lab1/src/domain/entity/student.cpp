#include "domain/entity/student.h"

Student::Student(int id, const std::string &name)
    : studentId(id), name(name) {}

int Student::getId() const
{
    return studentId;
}

std::string Student::getName() const
{
    return name;
}

void Student::setName(const std::string &newName)
{
    name = newName;
}