#pragma once
#include <vector>
#include "domain/entity/teacher.h"

class ITeacherRepository
{
public:
    virtual ~ITeacherRepository() = default;
    virtual void save(const Teacher &) = 0;
    virtual Teacher getById(int id) const = 0;
    virtual std::vector<Teacher> all() const = 0;
};