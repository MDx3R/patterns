#pragma once
#include <vector>
#include "domain/entity/course.h"

class ICourseRepository
{
public:
    virtual ~ICourseRepository() = default;
    virtual void save(const Course &) = 0;
    virtual Course getById(int id) const = 0;
    virtual std::vector<Course> all() const = 0;
};