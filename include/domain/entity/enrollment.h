#include <memory>
#include <optional>
#include "domain/entity/grade.h"

class Enrollment
{
private:
    int enrollment_id;
    int student_id;
    int course_id;
    std::optional<domain::Grade> grade;

public:
    Enrollment(int id, int studentId, int courseId);

    int getId() const;
    int getStudentId() const;
    int getCourseId() const;
    const domain::Grade *getGrade() const;

    void setGrade(std::optional<domain::Grade> newGrade);
};