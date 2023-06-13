#include <iostream>
#include <string>
#include <cstdio>
#include <conio.h>
#include <cstring>
#include <fstream>
#include <vector>
#include <map>
#include "Headers/Atv.h"

void Help() {
    std::cout << "Afisare\n\t-afisare" << std::endl <<
        "Adaugare\n\t-adaugare \"Brand\" \"Model\" Putere" << std::endl <<
        "Cautare\n\t-cautare interval cai putere (min-max)" << std::endl <<
        "Rezervare\n\t-rezervare \"Brand\" \"Model\"" << std::endl <<
        "Returnare\n\t-returnare \"Brand\" \"Model\"" << std::endl <<
        "Imprumut\n\t-imprumut \"Brand\" \"Model\" Ore (<10)" << std::endl;
}

void menu() {
    std::cout << "\033[38;5;226m----------------------------\n";
    std::cout << "\033[0;31m------MENIU--------\n";
    std::cout << "\033[38;5;226m----------------------------\n";
    std::cout << "\033[38;5;208m1-Afisare\n";
    std::cout << "\033[38;5;208m2-Adaugare\n";
    std::cout << "\033[38;5;208m3-Cautare\n";
    std::cout << "\033[38;5;208m4-Rezervare\n";
    std::cout << "\033[38;5;208m5-Returnare\n";
    std::cout << "\033[38;5;208m6-Imprumuta\n";
    std::cout << "0-IESIRE\n";
    std::cout << "\033[38;5;226m----------------------------\033[0;m\n";
}

void ReadData(std::string path, std::vector<Vehicle<int> *> &Vehicles) {
    std::string line;
    std::string token;
    std::string delimiter = ",";
    std::ifstream f(path);
    if (f.is_open()) {
        while (std::getline(f, line)) {
            token = line.substr(0, line.find(delimiter));
            std::string Brand = token;
            line.erase(0, line.find(delimiter) + delimiter.length());

            token = line.substr(0, line.find(delimiter));
            std::string Model = token;
            line.erase(0, line.find(delimiter) + delimiter.length());

            token = line.substr(0, line.find(delimiter));
            int Power = std::stoi(token);
            line.erase(0, line.find(delimiter) + delimiter.length());

            token = line.substr(0, std::string::npos);
            int Available = std::stoi(token);
            Vehicles.push_back(new Atv(Brand, Model, Power, Available));
        }
    }
}

void afisare(std::string path, int argc) {
    if (argc == 1) {
        system("cls");
    }
    std::vector<Vehicle<int> *> Vehicles;
    ReadData(path, Vehicles);
    for (int i = 0; i < Vehicles.size(); i++) {
        if (dynamic_cast<Atv *>(Vehicles[i])) {
            Atv *atv = ((Atv *) (Vehicles[i]));
            std::cout << *atv;
        }
    }
    if (argc == 1) {
        std::cout << "Apasati orice tasta pentru a va intoarce la meniul principal!";
        _getch();
    }
}

void cautare(std::string path, int argc, char *argv[]) {
    int min, max;
    char *token;
    std::vector<Vehicle<int> *> Vehicles;
    ReadData(path, Vehicles);
    if (argc == 3) {
        token = strtok(argv[2], "-");
        min = std::stoi(token);
        token = strtok(NULL, "");
        max = std::stoi(token);
        std::cout << "Atv-urile disponibile cu cai putere cuprinsi in itervalul dat sunt: " << std::endl;
        for (int i = 0; i < Vehicles.size(); i++) {
            if (dynamic_cast<Atv *>(Vehicles[i])) {
                Atv *atv = ((Atv *) Vehicles[i]);
                if (min <= atv->GetPower() && atv->GetPower() <= max && atv->GetAvailability() == 1) {
                    std::cout << *atv;
                }
            }
        }
        exit(1);
    } else {
        system("cls");
        std::cout << "CAUTARE" << std::endl << std::endl;
        std::cout << "Introduceti un interval de cai putere: ";
        std::cin >> min >> max;
        std::cout << "Atv-urile disponibile cu cai putere cuprinsi in itervalul dat sunt: " << std::endl;
        for (int i = 0; i < Vehicles.size(); i++) {
            if (dynamic_cast<Atv *>(Vehicles[i])) {
                Atv *atv = ((Atv *) Vehicles[i]);
                if (min <= atv->GetPower() && atv->GetPower() <= max && atv->GetAvailability() == 1) {
                    std::cout << *atv;
                }
            }
        }
        std::cout << "Apasati orice tasta pentru a va intoarce la meniul principal!";
        _getch();
    }
}

void adaugare(std::string path, int argc, char *argv[]) {
    std::string Brand, Model, Power;
    std::ofstream f;
    f.open(path, std::ios::app);
    if (argc == 5) {
        Brand = argv[2];
        Model = argv[3];
        Power = argv[4];
        f << Brand << "," << Model << "," << Power << "," << "1" << "\n";
        f.close();
        exit(1);
    } else {
        system("cls");
        std::cout << "ADAUGARE" << std::endl << std::endl;
        std::cout << "Introduceti Brand-ul: ";
        std::cin >> Brand;
        std::cin.ignore();
        std::cout << "Introduceti Modelul: ";
        std::getline(std::cin, Model);
        std::cout << "Introduceti cai putere: ";
        std::cin >> Power;
        f << Brand << "," << Model << "," << Power << "," << "1" << "\n";
        f.close();
    }
}

void rezervare(std::string path, int argc, char *argv[]);

void Res(std::string path, int argc, char *argv[], std::vector<Vehicle<int> *> Vehicles, std::string Brand, std::string Model) {
    int exists = 0, option = 0;
    std::string data;
    FILE *temp;
    for (int i = 0; i < Vehicles.size(); i++) {
        if (dynamic_cast<Atv *>(Vehicles[i])) {
            Atv *atv = ((Atv *) Vehicles[i]);
            if (atv->GetBrand() == Brand && atv->GetModel() == Model && atv->GetAvailability() == 1) {
                exists++;
            }
        }
    }
    if (exists == 0) {
        std::cout << "Nu avem brand-ul si modelul cautat sau atv-ul nu este disponibil!" << std::endl;
        exit(1);
    } else if (exists > 0) {
        temp = fopen("./Sources/temp.txt", "w");
        for (int i = 0; i < Vehicles.size(); i++) {
            if (dynamic_cast<Atv *>(Vehicles[i])) {
                Atv *atv = ((Atv *) Vehicles[i]);
                if (atv->GetBrand() == Brand && atv->GetModel() == Model) {
                    atv->SetAvailability(0);
                }
            }
        }
        for (int i = 0; i < Vehicles.size(); i++) {
            if (dynamic_cast<Atv *>(Vehicles[i])) {
                Atv *atv = ((Atv *) Vehicles[i]);
                data = atv->GetBrand() + ","
                    + atv->GetModel() + ","
                    + std::to_string(atv->GetPower()) + ","
                    + std::to_string(atv->GetAvailability())
                    + "\n";
                fputs(data.c_str(), temp);
            }
        }
        fclose(temp);
        remove("./Sources/Data.txt");
        rename("./Sources/temp.txt", "./Sources/Data.txt");
    }
}

void rezervare(std::string path, int argc, char *argv[]) {
    std::string Brand, Model, data;
    std::fstream f;
    std::vector<Vehicle<int> *> Vehicles;
    int exists = 0, option = 0;
    ReadData(path, Vehicles);
    FILE *temp;
    if (argc == 4) {
        Brand = argv[2];
        Model = argv[3];
        Res(path, argc, argv, Vehicles, Brand, Model);
        exit(1);
    } else {
        system("cls");
        std::cout << "REZERVARE" << std::endl << std::endl;
        std::cout << "Introduceti brand-ul: ";
        std::cin >> Brand;
        std::cin.ignore();
        std::cout << "Introduceti modelul: ";
        std::getline(std::cin, Model);
        for (int i = 0; i < Vehicles.size(); i++) {
            if (dynamic_cast<Atv *>(Vehicles[i])) {
                Atv *atv = ((Atv *) Vehicles[i]);
                if (atv->GetBrand() == Brand && atv->GetModel() == Model && atv->GetAvailability() == 1) {
                    exists++;
                }
            }
        }
        if (exists == 0) {
            std::cout << "Nu avem brand-ul si modelul cautat sau atv-ul nu este disponibil!" << std::endl <<
                "1. Reveniti la meniul principal!" << std::endl <<
                "2. Reintroduceti datele!" << std::endl;
            std::cin >> option;
            if (option == 1) {
                return;
            }
            if (option == 2) {
                rezervare(path, argc, argv);
            }
        } else if (exists > 0) {
            temp = fopen("./Sources/temp.txt", "w");
            for (int i = 0; i < Vehicles.size(); i++) {
                if (dynamic_cast<Atv *>(Vehicles[i])) {
                    Atv *atv = ((Atv *) Vehicles[i]);
                    if (atv->GetBrand() == Brand && atv->GetModel() == Model) {
                        atv->SetAvailability(0);
                    }
                }
            }
            for (int i = 0; i < Vehicles.size(); i++) {
                if (dynamic_cast<Atv *>(Vehicles[i])) {
                    Atv *atv = ((Atv *) Vehicles[i]);
                    data = atv->GetBrand() + ","
                        + atv->GetModel() + ","
                        + std::to_string(atv->GetPower()) + ","
                        + std::to_string(atv->GetAvailability())
                        + "\n";
                    fputs(data.c_str(), temp);
                }
            }
            fclose(temp);
            remove("./Sources/Data.txt");
            rename("./Sources/temp.txt", "./Sources/Data.txt");
        }
    }
}

void imprumut(std::string path, int argc, char *argv[]);

void Imp(std::string path, int argc, char *argv[], std::vector<Vehicle<int> *> Vehicles, std::string Brand, std::string Model) {
    std::string data, arg;
    int exists = 0, count = argc, ora;
    FILE *temp;
    arg = argv[count - 1];
    ora = std::stoi(arg);
    for (int i = 0; i < Vehicles.size(); i++) {
        if (dynamic_cast<Atv *>(Vehicles[i])) {
            Atv *atv = ((Atv *) Vehicles[i]);
            if (atv->GetBrand() == Brand && atv->GetModel() == Model && atv->GetAvailability() == 1) {
                exists++;
            }
        }
    }
    if (exists == 0) {
        std::cout << "Nu avem brand-ul si modelul cautat sau atv-ul nu este disponibil!" << std::endl;
        exit(1);
    } else if (exists > 0) {
        if (ora > 10) {
            std::cout << "Ati introdus mai mult de 10 ore!" << std::endl;
            exit(1);
        } else {
            temp = fopen("./Sources/temp.txt", "w");
            for (int i = 0; i < Vehicles.size(); i++) {
                if (dynamic_cast<Atv *>(Vehicles[i])) {
                    Atv *atv = ((Atv *) Vehicles[i]);
                    if (atv->GetBrand() == Brand && atv->GetModel() == Model) {
                        atv->SetAvailability(0);
                    }
                }
            }
            for (int i = 0; i < Vehicles.size(); i++) {
                if (dynamic_cast<Atv *>(Vehicles[i])) {
                    Atv *atv = ((Atv *) Vehicles[i]);
                    data = atv->GetBrand() + ","
                        + atv->GetModel() + ","
                        + std::to_string(atv->GetPower()) + ","
                        + std::to_string(atv->GetAvailability())
                        + "\n";
                    fputs(data.c_str(), temp);
                }
            }
            fclose(temp);
            remove("./Sources/Data.txt");
            rename("./Sources/temp.txt", "./Sources/Data.txt");
        }
    }
}

void imprumut(std::string path, int argc, char *argv[]) {
    std::string Brand, Model, data;
    int ora, option, exists = 0;
    std::fstream f;
    std::vector<Vehicle<int> *> Vehicles;
    ReadData(path, Vehicles);
    FILE *temp;
    if (argc == 5) {
        Brand = argv[2];
        Model = argv[3];
        Imp(path, argc, argv, Vehicles, Brand, Model);
        exit(1);
    } else {
        system("cls");
        std::cout << "IMPRUMUT" << std::endl << std::endl;
        std::cout << "Introduceti brand-ul: ";
        std::cin >> Brand;
        std::cin.ignore();
        std::cout << "Introduceti modelul: ";
        std::getline(std::cin, Model);
        for (int i = 0; i < Vehicles.size(); i++) {
            if (dynamic_cast<Atv *>(Vehicles[i])) {
                Atv *atv = ((Atv *) Vehicles[i]);
                if (atv->GetBrand() == Brand && atv->GetModel() == Model && atv->GetAvailability() == 1) {
                    exists++;
                }
            }
        }
        if (exists == 0) {
            std::cout << "Nu avem brand-ul si modelul cautat sau atv-ul nu este disponibil!" << std::endl <<
                "1. Reveniti la meniul principal!" << std::endl <<
                "2. Reintroduceti datele!" << std::endl;
            std::cin >> option;
            if (option == 1) {
                return;
            }
            if (option == 2) {
                imprumut(path, argc, argv);
            }
        } else if (exists > 0) {
            std::cout << "Introduceti pentru cate ore (<10h) doriti sa imprumutati: ";
            std::cin >> ora;
            if (ora > 10) {
                std::cout << "Ati introdus mai mult de 10 ore!" << std::endl <<
                    "1. Reveniti la meniul principal!" << std::endl <<
                    "2. Reintroduceti datele!" << std::endl;
                std::cin >> option;
                if (option == 1) {
                    return;
                }
                if (option == 2) {
                    imprumut(path, argc, argv);
                }
            } else {
                temp = fopen("./Sources/temp.txt", "w");
                for (int i = 0; i < Vehicles.size(); i++) {
                    if (dynamic_cast<Atv *>(Vehicles[i])) {
                        Atv *atv = ((Atv *) Vehicles[i]);
                        if (atv->GetBrand() == Brand && atv->GetModel() == Model) {
                            atv->SetAvailability(0);
                        }
                    }
                }
                for (int i = 0; i < Vehicles.size(); i++) {
                    if (dynamic_cast<Atv *>(Vehicles[i])) {
                        Atv *atv = ((Atv *) Vehicles[i]);
                        data = atv->GetBrand() + ","
                            + atv->GetModel() + ","
                            + std::to_string(atv->GetPower()) + ","
                            + std::to_string(atv->GetAvailability())
                            + "\n";
                        fputs(data.c_str(), temp);
                    }
                }
                fclose(temp);
                remove("./Sources/Data.txt");
                rename("./Sources/temp.txt", "./Sources/Data.txt");
            }
        }
    }
}

void returnare(std::string path, int argc, char *argv[]);

void Ret(std::string path, int argc, char *argv[], std::vector<Vehicle<int> *> Vehicles, std::string Brand, std::string Model) {
    std::string data;
    int exists = 0;
    FILE *temp;
    for (int i = 0; i < Vehicles.size(); i++) {
        if (dynamic_cast<Atv *>(Vehicles[i])) {
            Atv *atv = ((Atv *) Vehicles[i]);
            if (atv->GetBrand() == Brand && atv->GetModel() == Model && atv->GetAvailability() == 0) {
                exists++;
            }
        }
    }
    if (exists == 0) {
        std::cout << "Nu avem brand-ul si modelul cautat sau atv-ul a fost deja returnat!" << std::endl;
        exit(1);
    } else if (exists > 0) {
        temp = fopen("./Sources/temp.txt", "w");
        for (int i = 0; i < Vehicles.size(); i++) {
            if (dynamic_cast<Atv *>(Vehicles[i])) {
                Atv *atv = ((Atv *) Vehicles[i]);
                if (atv->GetBrand() == Brand && atv->GetModel() == Model) {
                    atv->SetAvailability(1);
                }
            }
        }
        for (int i = 0; i < Vehicles.size(); i++) {
            if (dynamic_cast<Atv *>(Vehicles[i])) {
                Atv *atv = ((Atv *) Vehicles[i]);
                data = atv->GetBrand() + ","
                    + atv->GetModel() + ","
                    + std::to_string(atv->GetPower()) + ","
                    + std::to_string(atv->GetAvailability())
                    + "\n";
                fputs(data.c_str(), temp);
            }
        }
        fclose(temp);
        remove("./Sources/Data.txt");
        rename("./Sources/temp.txt", "./Sources/Data.txt");
    }
}

void returnare(std::string path, int argc, char *argv[]) {
    std::string Brand, Model, data;
    std::fstream f;
    std::vector<Vehicle<int> *> Vehicles;
    int exists = 0, option = 0;
    ReadData(path, Vehicles);
    FILE *temp;
    if (argc == 4) {
        Brand = argv[2];
        Model = argv[3];
        Ret(path, argc, argv, Vehicles, Brand, Model);
        exit(1);
    } else {
        system("cls");
        std::cout << "RETURNARE" << std::endl << std::endl;
        std::cout << "Introduceti brand-ul: ";
        std::cin >> Brand;
        std::cin.ignore();
        std::cout << "Introduceti modelul: ";
        std::getline(std::cin, Model);
        for (int i = 0; i < Vehicles.size(); i++) {
            if (dynamic_cast<Atv *>(Vehicles[i])) {
                Atv *atv = ((Atv *) Vehicles[i]);
                if (atv->GetBrand() == Brand && atv->GetModel() == Model && atv->GetAvailability() == 0) {
                    exists++;
                }
            }
        }
        if (exists == 0) {
            std::cout << "Nu avem brand-ul si modelul cautat sau atv-ul a fost deja returnat!" << std::endl <<
                "1. Reveniti la meniul principal!" << std::endl <<
                "2. Reintroduceti datele!" << std::endl;
            std::cin >> option;
            if (option == 1) {
                return;
            }
            if (option == 2) {
                returnare(path, argc, argv);
            }
        } else if (exists > 0) {
            temp = fopen("./Sources/temp.txt", "w");
            for (int i = 0; i < Vehicles.size(); i++) {
                if (dynamic_cast<Atv *>(Vehicles[i])) {
                    Atv *atv = ((Atv *) Vehicles[i]);
                    if (atv->GetBrand() == Brand && atv->GetModel() == Model) {
                        atv->SetAvailability(1);
                    }
                }
            }
            for (int i = 0; i < Vehicles.size(); i++) {
                if (dynamic_cast<Atv *>(Vehicles[i])) {
                    Atv *atv = ((Atv *) Vehicles[i]);
                    data = atv->GetBrand() + ","
                        + atv->GetModel() + ","
                        + std::to_string(atv->GetPower()) + ","
                        + std::to_string(atv->GetAvailability())
                        + "\n";
                    fputs(data.c_str(), temp);
                }
            }
            fclose(temp);
            remove("./Sources/Data.txt");
            rename("./Sources/temp.txt", "./Sources/Data.txt");
        }
    }
}

int main(int argc, char *argv[]) {
    std::string path = "./Sources/Data.txt";
    if (argc == 1) {
        int option;
        do {
            system("cls");
            menu();
            std::cout << "Introduceti optiunea: ";
            std::cin >> option;
            std::cin.ignore();

            switch (option) {
                case 1:
                    afisare(path, argc);
                    break;
                case 2:
                    adaugare(path, argc, argv);
                    break;
                case 3:
                    cautare(path, argc, argv);
                    break;
                case 4:
                    rezervare(path, argc, argv);
                    break;
                case 5:
                    returnare(path, argc, argv);
                    break;
                case 6:
                    imprumut(path, argc, argv);
                    break;
                case 0:
                    exit(1);
                default:
                    std::cout << "Optiune invalida!" << std::endl;
                    break;
            }
        } while (option != 0);
    } else if (argc == 2 && strcmp(argv[1], "-help") == 0) {
        Help();
        exit(1);
    } else if (argc < 3 && strcmp(argv[1], "-afisare") == 0) {
        afisare(path, argc);
    } else if (argc < 6 && strcmp(argv[1], "-adaugare") == 0) {
        adaugare(path, argc, argv);
    } else if (argc < 4 && strcmp(argv[1], "-cautare") == 0) {
        cautare(path, argc, argv);
    } else if (argc < 5 && strcmp(argv[1], "-rezervare") == 0) {
        rezervare(path, argc, argv);
    } else if (argc < 6 && strcmp(argv[1], "-imprumut") == 0) {
        imprumut(path, argc, argv);
    } else if (argc < 5 && strcmp(argv[1], "-returnare") == 0) {
        returnare(path, argc, argv);
    } else if (strcmp(argv[1], "-adaugare") != 0 ||
        strcmp(argv[1], "-cautare") != 0 ||
        strcmp(argv[1], "-imprumut") != 0 ||
        strcmp(argv[1], "-returnare") != 0) {
        Help();
        exit(1);
    }
}