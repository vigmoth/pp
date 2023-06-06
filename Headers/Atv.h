#ifndef ATV_H
#define ATV_H

#include <iostream>
#include <string>
#include "Vehicle.h"

template<typename T>
class Atv : public Vehicle<T> {
    std::string Brand, Model;
    int Power;
public:
    std::string GetBrand() const { return this->Brand; };
    std::string GetModel() const { return this->Model; };
    int GetPower() const { return this->Power; };
public:
    Atv(std::string Brand = nullptr, std::string Model = nullptr, int Power = 0, int Available = 0)
        : Vehicle<T>(Available), Brand(Brand), Model(Model), Power(Power) { };
    virtual std::ostream &Print(std::ostream &out) {
        out << "Brand: " << this->GetBrand() << std::endl <<
            "\tModel: " << this->GetModel() << std::endl <<
            "\tPower: " << this->GetPower() << std::endl <<
            "\tAvailable: " << (this->GetAvailability() ? "\033[1;32mDA\033[0m" : "\033[1;31mNU\033[0m") << std::endl;
        return out;
    }
};

#endif