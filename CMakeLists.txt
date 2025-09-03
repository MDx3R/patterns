cmake_minimum_required(VERSION 3.16)

project(MyProject VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(core
    src/application/usecases/create_course_use_case.cpp
    src/application/usecases/enroll_student_use_case.cpp
    src/application/usecases/grade_enrollment_use_case.cpp
    src/domain/entity/course.cpp
    src/domain/entity/enrollment.cpp
    src/domain/entity/grade.cpp
    src/domain/entity/student.cpp
    src/domain/entity/teacher.cpp
)

target_include_directories(core PUBLIC include)

add_executable(app
    app/main.cpp
)

target_link_libraries(app PRIVATE core)