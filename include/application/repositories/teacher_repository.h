#pragma once
#include <vector>
#include "domain/entity/teacher.h"

struct ITeacherRepository
{
    virtual ~ITeacherRepository() = default;
    virtual void save(const Teacher &) = 0;
    virtual Teacher getById(int id) const = 0;
    virtual std::vector<Teacher> all() const = 0;
};