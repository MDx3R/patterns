#include <iostream>
#include <memory>
#include <string>

#include "application/usecases/create_course_use_case.h"
#include "application/usecases/enroll_student_use_case.h"
#include "application/usecases/grade_enrollment_use_case.h"
#include "application/usecases/get_course_use_case.h"

class Dispatcher
{
public:
    Dispatcher(std::shared_ptr<ICreateCourseUseCase> createCourseUC,
               std::shared_ptr<IEnrollStudentUseCase> enrollStudentUC,
               std::shared_ptr<IGradeEnrollmentUseCase> gradeEnrollmentUC,
               std::shared_ptr<IGetCourseUseCase> getCourseUC)
        : createCourseUseCase(createCourseUC),
          enrollStudentUseCase(enrollStudentUC),
          gradeEnrollmentUseCase(gradeEnrollmentUC),
          getCourseUseCase(getCourseUC)
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

            try
            {
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
                    handleGetCourse();
                    break;
                case 5:
                    std::cout << "Exiting...\n";
                    running = false;
                    break;
                default:
                    std::cout << "Invalid choice. Please try again.\n";
                }
            }
            catch (const std::exception &e)
            {
                std::cout << "Error: " << e.what() << "\n";
            }
        }
    }

private:
    std::shared_ptr<ICreateCourseUseCase> createCourseUseCase;
    std::shared_ptr<IEnrollStudentUseCase> enrollStudentUseCase;
    std::shared_ptr<IGradeEnrollmentUseCase> gradeEnrollmentUseCase;
    std::shared_ptr<IGetCourseUseCase> getCourseUseCase;

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

        int courseId = createCourseUseCase->execute(cmd);
        std::cout << "Course '" << cmd.title << "' successfully created with ID = " << courseId << "\n";
    }

    void handleEnrollStudent()
    {
        EnrollStudentCommand cmd;
        std::cout << "Enter course ID: ";
        std::cin >> cmd.courseId;
        std::cout << "Enter student ID: ";
        std::cin >> cmd.studentId;

        int enrollmentId = enrollStudentUseCase->execute(cmd);
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

        gradeEnrollmentUseCase->execute(cmd);
        std::cout << "Grade successfully assigned.\n";
    }

    void handleGetCourse()
    {
        int courseId;
        std::cout << "Enter course ID to view: ";
        std::cin >> courseId;

        auto courseDTO = getCourseUseCase->execute(courseId);

        std::cout << "\nCourse ID: " << courseDTO.id << "\n";
        std::cout << "Title: " << courseDTO.title << "\n";
        std::cout << "Description: " << courseDTO.description << "\n";
        std::cout << "Teacher ID: " << courseDTO.teacherId << "\n";
        std::cout << "Enrollments:\n";

        for (const auto &enrollment : courseDTO.enrollments)
        {
            std::cout << "  Enrollment ID: " << enrollment.id
                      << ", Student ID: " << enrollment.studentId
                      << ", Grade: ";
            if (enrollment.grade)
                std::cout << static_cast<int>(enrollment.grade->getValue());
            else
                std::cout << "N/A";
            std::cout << "\n";
        }
    }
};
