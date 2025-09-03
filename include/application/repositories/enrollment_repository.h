#include <optional>
#include <vector>
#include "domain/entity/enrollment.h"

struct IEnrollmentRepository
{
    virtual ~IEnrollmentRepository() = default;
    virtual int save(const Enrollment &) = 0; // upsert
    virtual Enrollment getById(int id) const = 0;
    virtual std::vector<Enrollment> byCourse(int courseId) const = 0;
    virtual std::vector<Enrollment> byStudent(int studentId) const = 0;
};