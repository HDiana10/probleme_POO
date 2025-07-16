#ifndef ANGAJAT_H
#define ANGAJAT_H
#include <string>

class Angajat{
private:
    std::string nume;
    std::string departament;
    std::string tip;
public:
    virtual void afisare() = 0;
    virtual float rentabilitate_angajat() = 0;
    virtual float calcul_salariu(){
        return 0;
    };
    Angajat(std::string, std::string, std::string);
    std::string get_nume();
    std::string get_departament();
    //std::string get_tip();
};

#endif
