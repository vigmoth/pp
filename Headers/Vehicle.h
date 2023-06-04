#ifndef VEHICLE_H
#define VEHICLE_H

#include <iostream>

template<typename T>
class Vehicle {
    T Availability;

public:
    T GetAvailability() const {
        return this->Availability;
    }

    void SetAvailability(T Availability) {
        this->Availability = Availability;
    }

public:
    Vehicle(T Availability = 0) {
        this->Availability = Availability;
    }

    template<typename TT>
    friend std::ostream &operator << (std::ostream &out, Vehicle<TT> &vehicle) {
        return vehicle.Print(out);
    }

    virtual std::ostream &Print(std::ostream &out) {
        out << "Available: " << this->GetAvailability() << std::endl;
        return out;
    }
};

#endif