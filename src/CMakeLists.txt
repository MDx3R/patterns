add_library(core
    application/usecases/create_course_use_case.cpp
    application/usecases/enroll_student_use_case.cpp
    application/usecases/grade_enrollment_use_case.cpp
    application/usecases/get_course_use_case.cpp
    domain/entity/course.cpp
    domain/entity/enrollment.cpp
    domain/entity/grade.cpp
    domain/entity/student.cpp
    domain/entity/teacher.cpp
)

target_include_directories(core PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/include
)
