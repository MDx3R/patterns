#pragma once
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include "application/repositories/enrollment_repository.h"

class InMemoryEnrollmentRepository : public IEnrollmentRepository
{
private:
    std::unordered_map<int, Enrollment> storage;

public:
    void save(const Enrollment &enrollment) override
    {
        storage[enrollment.getId()] = enrollment; // upsert
    }

    Enrollment getById(int id) const override
    {
        auto it = storage.find(id);
        if (it != storage.end())
            return it->second;
        throw std::runtime_error("Enrollment not found");
    }

    bool existsById(int id) const override
    {
        return storage.find(id) != storage.end();
    }

    std::vector<Enrollment> byCourse(int courseId) const override
    {
        std::vector<Enrollment> result;
        for (const auto &[_, e] : storage)
        {
            if (e.getCourseId() == courseId)
                result.push_back(e);
        }
        return result;
    }

    std::vector<Enrollment> byStudent(int studentId) const override
    {
        std::vector<Enrollment> result;
        for (const auto &[_, e] : storage)
        {
            if (e.getStudentId() == studentId)
                result.push_back(e);
        }
        return result;
    }
};
