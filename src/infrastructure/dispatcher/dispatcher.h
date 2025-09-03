#include <iostream>
#include <memory>
#include <string>

#include "application/usecases/create_course_use_case.h"
#include "application/usecases/enroll_student_use_case.h"
#include "application/usecases/grade_enrollment_use_case.h"

class Dispatcher
{
public:
    Dispatcher(ICreateCourseUseCase &createCourseUC,
               IEnrollStudentUseCase &enrollStudentUC,
               IGradeEnrollmentUseCase &gradeEnrollmentUC)
        : createCourseUseCase(createCourseUC),
          enrollStudentUseCase(enrollStudentUC),
          gradeEnrollmentUseCase(gradeEnrollmentUC)
    {
    }

    void start()
    {
        std::cout << "=======================================\n";
        std::cout << "         Elective System\n";
        std::cout << "=======================================\n";

        bool running = true;
        while (running)
        {
            showMainMenu();
            int choice;
            std::cin >> choice;
            std::cin.ignore();

            switch (choice)
            {
            case 1:
                handleCreateCourse();
                break;
            case 2:
                handleEnrollStudent();
                break;
            case 3:
                handleGradeEnrollment();
                break;
            case 4:
                std::cout << "Course viewing is not implemented yet.\n";
                break;
            case 5:
                std::cout << "Exiting...\n";
                running = false;
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
            }
        }
    }

private:
    ICreateCourseUseCase &createCourseUseCase;
    IEnrollStudentUseCase &enrollStudentUseCase;
    IGradeEnrollmentUseCase &gradeEnrollmentUseCase;

    void showMainMenu()
    {
        std::cout << "\n1. Create course\n";
        std::cout << "2. Enroll student in course\n";
        std::cout << "3. Grade student\n";
        std::cout << "4. View course and enrollments\n";
        std::cout << "5. Exit\n";
        std::cout << "Select an action: ";
    }

    void handleCreateCourse()
    {
        CreateCourseCommand cmd;
        std::cout << "Enter teacher ID: ";
        std::cin >> cmd.teacherId;
        std::cin.ignore();
        std::cout << "Enter course title: ";
        std::getline(std::cin, cmd.title);
        std::cout << "Enter course description: ";
        std::getline(std::cin, cmd.description);

        int courseId = createCourseUseCase.execute(cmd);
        std::cout << "Course '" << cmd.title << "' successfully created with ID = " << courseId << "\n";
    }

    void handleEnrollStudent()
    {
        EnrollStudentCommand cmd;
        std::cout << "Enter course ID: ";
        std::cin >> cmd.courseId;
        std::cout << "Enter student ID: ";
        std::cin >> cmd.studentId;

        int enrollmentId = enrollStudentUseCase.execute(cmd);
        std::cout << "Student " << cmd.studentId << " successfully enrolled in course "
                  << cmd.courseId << ". Enrollment ID = " << enrollmentId << "\n";
    }

    void handleGradeEnrollment()
    {
        GradeEnrollmentCommand cmd;
        int gradeValue;
        std::cout << "Enter course ID: ";
        std::cin >> cmd.courseId;
        std::cout << "Enter enrollment ID: ";
        std::cin >> cmd.enrollmentId;
        std::cout << "Enter teacher ID: ";
        std::cin >> cmd.teacherId;
        std::cout << "Enter grade (0-5): ";
        std::cin >> gradeValue;
        cmd.gradeValue = static_cast<Grade::GradeEnum>(gradeValue);

        gradeEnrollmentUseCase.execute(cmd);
        std::cout << "Grade successfully assigned.\n";
    }
};
