#include "../Headers/Atv.h"

Atv::Atv(std::string Brand, std::string Model, int Power, int Available) : Vehicle(Available) {
    if (!Brand.empty()) {
        this->Brand = Brand;
    }
    if (!Model.empty()) {
        this->Model = Model;
    }
    this->Power = Power;
}

std::string Atv::GetBrand() const {
    return this->Brand;
}

std::string Atv::GetModel() const {
    return this->Model;
}

int Atv::GetPower() const {
    return this->Power;
}

std::ostream &operator << (std::ostream &out, Atv &atv) {
    return atv.Print(out);
}

std::ostream &Atv::Print(std::ostream &out) {
    out << "Brand: " << this->GetBrand() << std::endl <<
        "\tModel: " << this->GetModel() << std::endl <<
        "\tPower: " << this->GetPower() << std::endl <<
        "\tAvailable: " << (this->GetAvailability() ? "\033[1;32mDA\033[0m" : "\033[1;31mNU\033[0m") << std::endl;
    return out;
}