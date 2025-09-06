#pragma once
#include <string>

class Student
{
private:
    int studentId;
    std::string name;

public:
    Student(int id, const std::string &name);

    int getId() const;
    std::string getName() const;

    void setName(const std::string &newName);
};