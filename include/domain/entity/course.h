#include <string>
#include <vector>
#include <optional>
#include "enrollment.h"

class Course
{
private:
    int course_id;
    int teacher_id;
    std::string title;
    std::string description;
    std::vector<Enrollment> enrollments;

public:
    Course(int id, const std::string &title, const std::string &description, int teacherId);
    Course(int id, const std::string &title, const std::string &description,
           int teacherId, const std::vector<Enrollment> &enrollments);

    int getId() const;
    int getTeacherId() const;
    std::string getTitle() const;
    std::string getDescription() const;
    std::vector<Enrollment> getEnrollments() const;

    void setTitle(const std::string &newTitle);
    void setDescription(const std::string &newDescription);

    void addEnrollment(const Enrollment &enrollment);
    void gradeEnrollment(int enrollmentId, Grade &grade);
};