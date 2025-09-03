#include "domain/entity/grade.h"

domain::Grade::Grade(int id, domain::Grade::GradeEnum value, std::time_t date, int teacherId)
    : grade_id(id), value(value), date(date), teacher_id(teacherId) {}

int domain::Grade::getId() const
{
    return grade_id;
}

int domain::Grade::getTeacherId() const
{
    return teacher_id;
}

domain::Grade::GradeEnum domain::Grade::getValue() const
{
    return value;
}

std::time_t domain::Grade::getDate() const
{
    return date;
}