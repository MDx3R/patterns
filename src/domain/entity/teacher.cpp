#include "domain/entity/teacher.h"

Teacher::Teacher(int id, const std::string &name)
    : teacher_id(id), name(name) {}

int Teacher::getId() const
{
    return teacher_id;
}

std::string Teacher::getName() const
{
    return name;
}

void Teacher::setName(const std::string &newName)
{
    name = newName;
}