#pragma once
#include "application/repositories/course_repository.h"
#include "application/usecases/get_course_use_case.h"

class GetCourseUseCase : public IGetCourseUseCase
{
private:
    std::shared_ptr<ICourseRepository> courseRepository;

public:
    explicit GetCourseUseCase(std::shared_ptr<ICourseRepository> repo);
    CourseDTO execute(int courseId) override;
};
