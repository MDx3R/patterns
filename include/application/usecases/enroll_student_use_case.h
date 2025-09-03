#pragma once
struct EnrollStudentCommand
{
    int courseId;
    int studentId;
};

class IEnrollStudentUseCase
{
public:
    virtual ~IEnrollStudentUseCase() = default;
    virtual int execute(const EnrollStudentCommand &request) = 0; // returns enrollment_id
};
