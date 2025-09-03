#include "grade.h"

Grade::Grade(int id, const std::string &value, std::time_t date, int teacherId)
    : grade_id(id), value(value), date(date), teacher_id(teacherId) {}

int Grade::getId() const
{
    return grade_id;
}

int Grade::getTeacherId() const
{
    return teacher_id;
}

std::string Grade::getValue() const
{
    return value;
}

std::time_t Grade::getDate() const
{
    return date;
}