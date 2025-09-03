#include <string>

struct CreateCourseCommand
{
    int teacherId;
    std::string title;
    std::string description;
};

class ICreateCourseUseCase
{
public:
    virtual ~ICreateCourseUseCase() = default;
    virtual int execute(const CreateCourseCommand &request) = 0; // returns course_id
};