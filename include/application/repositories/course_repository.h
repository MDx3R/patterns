#include <vector>
#include "domain/entity/course.h"

struct ICourseRepository
{
    virtual ~ICourseRepository() = default;
    virtual int save(const Course &) = 0;
    virtual Course getById(int id) const = 0;
    virtual std::vector<Course> all() const = 0;
};