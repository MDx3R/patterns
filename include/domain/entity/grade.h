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
    int grade_id;
    int teacher_id;
    GradeEnum value;
    std::time_t date;

public:
    Grade() = default;
    Grade(int id, GradeEnum value, std::time_t date, int teacherId);

    int getId() const;
    int getTeacherId() const;
    GradeEnum getValue() const;
    std::time_t getDate() const;
};
