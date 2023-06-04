#ifndef ATV_H
#define ATV_H

#include <iostream>
#include <string>
#include "Vehicle.h"

class Atv : public Vehicle<int> {
    std::string Brand, Model;
    int Power;
public:
    std::string GetBrand() const;
    std::string GetModel() const;
    int GetPower() const;
public:
    Atv(std::string Brand = nullptr, std::string Model = nullptr, int Power = 0, int Available = 0);
    virtual std::ostream &Print(std::ostream &out);
};

#endif