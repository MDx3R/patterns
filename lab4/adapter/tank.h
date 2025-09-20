#pragma once
#include <string>

class GasTank
{
private:
    double R = 8.31; // Молярная газовая постоянная

    double volume, mass, molar;

public:
    GasTank(double volume, double mass, double molar) : volume(volume), mass(mass), molar(molar) {}

    double getVolume() const { return volume; }
    double getMass() const { return mass; }
    double getMolar() const { return molar; }

    void setVolume(double volume) { this->volume = volume; }
    void setMass(double mass) { this->mass = mass; }
    void setMolar(double molar) { this->molar = molar; }

    double getPressure(int t) const
    {
        return amountOfMatter() * R * t;
    }
    double amountOfMatter() const { return mass / molar; }
    std::string toString() const
    {
        return "GasTank(volume=" + std::to_string(volume) +
               ", mass=" + std::to_string(mass) +
               ", molar=" + std::to_string(molar) + ")";
    }
};