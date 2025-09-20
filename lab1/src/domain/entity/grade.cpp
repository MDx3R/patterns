#include "domain/entity/grade.h"

Grade::Grade(int id, Grade::GradeEnum value, std::time_t date, int teacherId)
    : gradeId(id), value(value), date(date), teacherId(teacherId) {}

int Grade::getId() const
{
    return gradeId;
}

int Grade::getTeacherId() const
{
    return teacherId;
}

Grade::GradeEnum Grade::getValue() const
{
    return value;
}

std::time_t Grade::getDate() const
{
    return date;
}

bool Grade::operator==(const Grade &other) const
{
    return gradeId == other.gradeId &&
           teacherId == other.teacherId &&
           value == other.value &&
           date == other.date;
}