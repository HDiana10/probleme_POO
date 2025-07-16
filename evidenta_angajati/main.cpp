#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include "Angajat.h"

class Salariat: public Angajat{
    private:
        int norma, vechime;
        float salariu_net;
    public:
        Salariat(std::string tip, std::string nume, std::string departament, int norma, int vechime, float salariu_net): Angajat(tip, nume, departament), norma(norma), vechime(vechime), salariu_net(salariu_net){}
        void afisare(){
            std::cout << this->get_nume() << " " << norma << " " << vechime << " " << salariu_net << "\n";
        }
        float rentabilitate_angajat(){
            return norma * ( 250 - 20 - vechime / 3 ) / this->calcul_salariu(); 
        }
        float calcul_salariu(){
            if(this->get_departament() == "IT")
                return 12 * salariu_net / 0.65;
            return 12 * salariu_net / 0.55;
        }
};

class Colaborator: public Angajat{
    private:
        float onorariu, nr_prestari_anuale;
    public:
        Colaborator(std::string tip, std::string nume, std::string departament, float onorariu, float nr_prestari_anuale): Angajat(tip, nume, departament), onorariu(onorariu), nr_prestari_anuale(nr_prestari_anuale){}
        void afisare(){
            std::cout << this->get_nume() << " " << onorariu << " " << nr_prestari_anuale << "\n";
        }
        float rentabilitate_angajat(){return 0;}
        float calcul_salariu(){
            if(this->get_departament() == "IT")
                return nr_prestari_anuale * onorariu / 0.65;
            return nr_prestari_anuale * onorariu / 0.55;
        }
};

class Firma{
    private:
        std::vector<Angajat*> vec;
    public:
        void adauga_angajat(Angajat *a){vec.push_back(a);}
        void afisare_angajati(std::string departament){
            for(int i=0; i<vec.size(); i++)
                if(vec[i]->get_departament() == departament)
                    vec[i]-> afisare();
        }
        void calcul_salariu(std::string nume){
            for(int i=0; i<vec.size(); i++)
                if(vec[i]->get_nume() == nume)
                    std::cout << std::fixed << std::setprecision(2) << vec[i]->calcul_salariu();
        }
        void rentabilitate(){
            float rent_max = 0, poz = -1;
            for(int i=0; i<vec.size(); i++){
                    float rent = vec[i]->rentabilitate_angajat();
                    if(rent_max < rent)
                        rent_max = rent, poz = i;
                }
            std::cout << vec[poz] -> get_nume() << '\n';
        }
        void salariu_anual(std::string departament){
            double salariu = 0, nr=0;
            for(int i=0; i<vec.size(); i++)
                if(vec[i]->get_departament() == departament)
                    salariu += vec[i]->calcul_salariu(), nr++;
            std::cout << std::fixed << std::setprecision(2) << salariu/nr;
        }
};

int main(){
    int n, comanda;
    std::string tip, nume, departament;
    int norma, vechime;
    float salariu_net, onorariu, nr_prestari_anuale;
    Angajat *ang = nullptr;
    Firma firma;
    std::cin >> n;
    
    for(int i=0; i<n; i++){
        std::cin.ignore();
        getline(std::cin, tip);
        getline(std::cin, nume);
        getline(std::cin, departament);
        
        if(tip == "salariat"){
            std::cin >> norma >> vechime >> salariu_net;
            ang = new Salariat(tip, nume, departament, norma, vechime, salariu_net);
        }
        else{
            std::cin >> onorariu >> nr_prestari_anuale;
            ang = new Colaborator(tip, nume, departament, onorariu, nr_prestari_anuale);
        }
        
        firma.adauga_angajat(ang);
    }
    
    std::cin >> comanda;
    
    switch(comanda){
        case 1:{
            std::cin.ignore();
            getline(std::cin, departament);
            firma.afisare_angajati(departament);
            break;
        }
        
        case 2:{
            std::cin.ignore();
            getline(std::cin, nume);
            firma.calcul_salariu(nume);
            break;
        }
        
        case 3:{
            firma.rentabilitate();
            break;
        }
        
        case 4:{
            std::cin >> departament;
            firma.salariu_anual(departament);
            break;
        }
    }
}
