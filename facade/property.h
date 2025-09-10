#pragma once
#include <string>

class Property
{
protected:
    double area;
    int yearBuilt;
    int residents;
    double wear; // %

public:
    Property(double area, int yearBuilt, int residents, double wear)
        : area(area), yearBuilt(yearBuilt), residents(residents), wear(wear) {}

    virtual ~Property() = default;

    virtual double getArea() const { return area; }
    virtual int getYearBuilt() const { return yearBuilt; }
    virtual int getResidents() const { return residents; }
    virtual double getWear() const { return wear; }

    virtual std::string getType() const = 0;
};

namespace subsystem
{
    class Apartment : public Property
    {
    public:
        std::string getType() const override { return "Apartment"; }
    };

    class Townhouse : public Property
    {
    private:
        int numFloors;

    public:
        Townhouse(double area, int yearBuilt, int residents, double wear, int numFloors)
            : Property(area, yearBuilt, residents, wear), numFloors(numFloors) {}

        std::string getType() const override { return "Townhouse"; }
        int getNumFloors() const { return numFloors; }
    };

    class Cottage : public Property
    {
    private:
        bool hasGarden;

    public:
        Cottage(double area, int yearBuilt, int residents, double wear, bool hasGarden)
            : Property(area, yearBuilt, residents, wear), hasGarden(hasGarden) {}

        std::string getType() const override { return "Cottage"; }
        bool getHasGarden() const { return hasGarden; }
    };
}