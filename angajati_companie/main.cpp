#include <string>
#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>

class Angajat{
protected:
    float salariu;
    std::string nume;
    int nr_ore;
    std::string tip_angajat;
public:
    Angajat(float salariu, std::string nume, int nr_ore, std::string tip_angajat):
        salariu(salariu), nume(nume), nr_ore(nr_ore), tip_angajat(tip_angajat){}
    void afisare(){
        std::cout << this->tip_angajat << std::endl;
        std::cout << this->nume << ":" << this->salariu << std::endl;
    }
    virtual float calcul_salariu_brut_pe_ora() = 0;
    virtual float calcul_salariu_net() = 0;
    std::string get_nume(){return this->nume;}
    float get_salariu(){return this->salariu;}
    std::string get_tip_angajat(){return this->tip_angajat;}
};

class PersoanaFizica: public Angajat{
public:
    PersoanaFizica(float salariu, std::string nume, int nr_ore):Angajat(salariu, nume, nr_ore, "Persoana fizica"){}
    float calcul_salariu_brut_pe_ora(){
        return this->salariu / (this->nr_ore * 4);
    }
    
    float calcul_salariu_net(){
        return (100-42.0)/100 * this->salariu;
    }
};

class PersoanaJuridica: public Angajat{
public:    
    PersoanaJuridica(float salariu, std::string nume, int nr_ore):Angajat(salariu, nume, nr_ore, "Persoana juridica"){}
    float calcul_salariu_brut_pe_ora(){
        return this->salariu / (this->nr_ore * 8 * 4);
    }
    
    float calcul_salariu_net(){
        return (100-10)/100.0 * this->salariu;
    }
};

bool compare_angajati( Angajat * lhs,  Angajat * rhs){
    if (lhs->get_tip_angajat() != rhs->get_tip_angajat())
        return (lhs->get_tip_angajat() == "Persoana fizica");
    if (lhs->calcul_salariu_net() > rhs->calcul_salariu_net())
        return true;
    else
        return false;
}

class AdministrareAngajat{
private:
    std::vector<Angajat*> vec;
public:
    AdministrareAngajat(){}
    void adauga_angajat(Angajat* ptr_angajat){
        vec.push_back(ptr_angajat);
    }
    void afisare_angajati(){
        for (int i=0; i<vec.size(); i++){
            vec[i]->afisare();
            std::cout << std::endl;
        }
    }
    
    void afisare_salarii_brute_pe_ora(){
        for (int i=0; i<vec.size(); i++){
            // std::cout << std::fixed << std::setprecision(0);
            std::cout << vec[i]->get_nume() << ":" << int(vec[i]->calcul_salariu_brut_pe_ora()) << " lei/h";
            std::cout << std::endl;
        }
    }
    
    void afisare_salarii_nete(){
        for (Angajat * a:vec){
            std::cout << a->get_nume() << ":" << a->get_salariu() << "-" << a->calcul_salariu_net() << std::endl;
        }
    }
    
    void ordonare_salariu_net(){
        std::sort(vec.begin(), vec.end(), compare_angajati);
        for (auto a:vec){
            std::cout << a->get_nume() << ":" << a->get_salariu() << std::endl;
        }
    }
};


int main(){
    int comanda;
    int temp_nr_angajati;
    std::string temp_tip_angajat;
    std::string temp_nume;
    float temp_salariu_brut;
    int nr_zile_concediu;
    int temp_nr_zile_lucrate;
    Angajat * temp_angajat = nullptr;
    AdministrareAngajat firma;
    
    std::cin >> comanda;
    std::cin >> temp_nr_angajati;
    
    for (int i=0; i<temp_nr_angajati; i++){
        std::cin.ignore();
        getline(std::cin, temp_tip_angajat);
        getline(std::cin, temp_nume);
        std::cin >> temp_salariu_brut;
        std::cin >> nr_zile_concediu;
        std::cin >> temp_nr_zile_lucrate;
        
        if (temp_tip_angajat == "Persoana fizica"){
            temp_angajat = new PersoanaFizica(temp_salariu_brut, temp_nume, temp_nr_zile_lucrate);
        }
        else {
            temp_angajat = new PersoanaJuridica(temp_salariu_brut, temp_nume, temp_nr_zile_lucrate);
        }
        
        firma.adauga_angajat(temp_angajat);
    }
    
    switch(comanda){
        case 1:{
            firma.afisare_angajati();
            break;
        }
        
        case 2:{
            firma.afisare_salarii_brute_pe_ora();
            break;
        }
        
        case 3:{
            firma.afisare_salarii_nete();
            break;
        }
        
        case 4:{
            firma.ordonare_salariu_net();
            break;
        }
        default:{break;}
    }
    return 0;
}
