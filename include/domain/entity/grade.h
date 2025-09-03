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
    std::string value;
    std::time_t date;

public:
    Grade(int id, const std::string &value, std::time_t date, int teacherId);

    int getId() const;
    int getTeacherId() const;
    std::string getValue() const;
    std::time_t getDate() const;
};