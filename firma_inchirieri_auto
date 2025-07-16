#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <cmath>

class Automobil{
    protected:
        int capacitate, viteza;
        std::string tip, nume;
        float nivel_poluare;
    public:
        Automobil(std::string tip, std::string nume, int capacitate, int viteza): tip(tip), nume(nume), capacitate(capacitate), viteza(viteza){}
        int get_capacitate(){return capacitate;}
        int get_viteza(){return viteza;}
        std::string get_nume(){return nume;}
        std::string get_tip(){return tip;}
        float get_nivel_poluare(){return nivel_poluare;}
        int calc_capacitate(int nr){
            if(nr % capacitate == 0)
                return nr/capacitate;
            else
                return nr/capacitate + 1;
        }
        void calc_poluare(int nr_pasageri){
            int nr = this -> calc_capacitate(nr_pasageri);
            if(nr_pasageri % capacitate){
                this->nivel_poluare = this -> coeficient_poluare(nr_pasageri%capacitate);
                nr--;
            }
            nivel_poluare += nr*coeficient_poluare(capacitate);    
        }
        virtual float coeficient_poluare(int nr_pasageri) = 0;
};

class Masina: public Automobil{
    public:
        Masina(std::string tip, std::string nume, int capacitate, int viteza): Automobil(tip, nume, capacitate, viteza){}
        float coeficient_poluare(int nr_pasageri){
            return 1.0 * viteza / 100 + nr_pasageri/capacitate;
        }
};

class Autocar: public Automobil{
    public:
        Autocar(std::string tip, std::string nume, int capacitate, int viteza): Automobil(tip, nume, capacitate, viteza){}
        float coeficient_poluare(int nr_pasageri){
            return 1.0 * viteza / 20 + std::pow(2.71, 1.0 * (2*nr_pasageri)/capacitate);
        }
};


bool comp(Automobil *&a, Automobil *&b){
    return a->get_nivel_poluare() <= b->get_nivel_poluare();
}


class FirmaAuto{
    private:
        std::vector <Automobil*> vec;
    public:
        void adauga_masina(Automobil *a){vec.push_back(a);}
        void afisare_masini(){
            for(int i=0; i<vec.size(); i++)
                std::cout << vec[i]->get_nume() << "\n" << vec[i]->get_capacitate() << "\n" << vec[i]->get_viteza() << '\n';
        }
        void calc_grup(int nr_persoane){
            for(int i = 0; i < vec.size(); i++){
                std::cout << vec[i]->get_nume() << "\n" << vec[i]->calc_capacitate(nr_persoane) << '\n';   
            }
        }
        void calc_drum(int lungime, int durata){
            for(int i=0; i < vec.size(); i++){
                float timp = 1.0 * lungime / vec[i]->get_viteza();
                if(timp <= durata){
                    std::cout << vec[i]->get_nume() << "\n" << std::fixed << std::setprecision(2) << timp << '\n';
                }
            }
        }
        void calc_poluare(int nr_persoane){
            for(int i=0; i < vec.size(); i++)
                vec[i]->calc_poluare(nr_persoane);
            std::sort(vec.begin(), vec.end(), comp);
            
            for(int i = 0; i < vec.size(); i++)
                std::cout << vec[i]->get_nume() << '\n';
        }
};

int main(){
    int test, nr_automobile;
    std::string tip, nume;
    int capacitate, viteza;
    FirmaAuto firma;
    Automobil *a = nullptr;
    std::cin >> test;
    
    std::cin>>nr_automobile;
    for(int i=0; i < nr_automobile; i++)
    {
        std::cin.ignore();
        getline(std::cin, tip);
        getline(std::cin, nume);
        std::cin >> capacitate >> viteza;
        if(tip == "Masina")
            a = new Masina(tip, nume, capacitate, viteza);
        else
            a = new Autocar(tip, nume, capacitate, viteza);
        firma.adauga_masina(a);
    }
    
    switch(test){
        case 1:{
            firma.afisare_masini();
            break;
        }
        
        case 2:{
            int nr_persoane;
            std::cin >> nr_persoane;
            firma.calc_grup(nr_persoane);
            break;    
        }
        
        case 3:{
            int lungime, durata;
            std::cin >> lungime >> durata;
            firma.calc_drum(lungime, durata);
            break;
        }
        
        case 4:{
            int nr_persoane;
            std::cin >> nr_persoane;
            firma.calc_poluare(nr_persoane);
            break;
        }
    }
}
