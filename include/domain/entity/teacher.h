#pragma once
#include <string>

class Teacher
{
private:
    int teacherId;
    std::string name;

public:
    Teacher(int id, const std::string &name);

    int getId() const;
    std::string getName() const;

    void setName(const std::string &newName);
};
