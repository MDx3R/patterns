#include <vector>
#include "domain/entity/student.h"

struct IStudentRepository
{
    virtual ~IStudentRepository() = default;
    virtual void save(const Student &) = 0;
    virtual Student getById(int id) const = 0;
    virtual std::vector<Student> all() const = 0;
};