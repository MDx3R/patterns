#include <unordered_map>
#include "include/application/repositories/course_repository.h"
#include "include/application/repositories/enrollment_repository.h"
#include <stdexcept>

class InMemoryCourseRepository : public ICourseRepository
{
private:
    std::unordered_map<int, Course> storage;
    IEnrollmentRepository &enrollmentRepo;

public:
    explicit InMemoryCourseRepository(IEnrollmentRepository &enrollRepo)
        : enrollmentRepo(enrollRepo) {}

    void save(const Course &course) override
    {
        for (const auto &enrollment : course.getEnrollments())
        {
            enrollmentRepo.save(enrollment); // upsert
        }
        storage[course.getId()] = course; // upsert
    }

    Course getById(int id) const override
    {
        auto it = storage.find(id);
        if (it == storage.end())
            throw std::runtime_error("Course not found");

        Course c = it->second;

        auto enrollments = enrollmentRepo.byCourse(c.getId());
        for (const auto &e : enrollments)
        {
            c.addEnrollment(e);
        }

        return c;
    }

    std::vector<Course> all() const override
    {
        std::vector<Course> result;
        for (const auto &[_, c] : storage)
        {
            result.push_back(getById(c.getId()));
        }
        return result;
    }
};
