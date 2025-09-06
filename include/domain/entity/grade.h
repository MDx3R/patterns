#pragma once
#include <string>
#include <ctime>

class Grade // VO
{
public:
    enum class GradeEnum
    {
        EXCELLENT = 5,
        GOOD = 4,
        SATISFACTORY = 3,
        UNSATISFACTORY = 2
    };

private:
    int gradeId;
    int teacherId;
    GradeEnum value;
    std::time_t date;

public:
    Grade() = default;
    Grade(int id, GradeEnum value, std::time_t date, int teacherId);

    int getId() const;
    int getTeacherId() const;
    GradeEnum getValue() const;
    std::time_t getDate() const;

    bool operator==(const Grade &other) const
    {
        return gradeId == other.gradeId &&
               teacherId == other.teacherId &&
               value == other.value &&
               date == other.date;
    }
};
