#include "Angajat.h"
#include <string>

Angajat::Angajat(std::string tip, std::string nume, std::string departament):tip(tip), nume(nume), departament(departament){}

std::string Angajat::get_nume(){return nume;}
std::string Angajat::get_departament(){return departament;}
//std::string Angajat::get_tip(){return tip;}
