#include "domain/entity/grade.h"

Grade::Grade(int id, Grade::GradeEnum value, std::time_t date, int teacherId)
    : grade_id(id), value(value), date(date), teacher_id(teacherId) {}

int Grade::getId() const
{
    return grade_id;
}

int Grade::getTeacherId() const
{
    return teacher_id;
}

Grade::GradeEnum Grade::getValue() const
{
    return value;
}

std::time_t Grade::getDate() const
{
    return date;
}