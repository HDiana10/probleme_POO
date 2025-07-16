#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>

class Vehicul{
    protected:
        int masa;
        std::string marca;
    public:
        Vehicul(std::string marca, int masa): marca(marca), masa(masa) {}
        virtual void display() = 0;
        int masa_totala() { return masa + this -> masa_aditionala(); }
        virtual int masa_aditionala() = 0;
        float viteza_maxima(){
            return 1.0 * 300000 / (masa + this->masa_aditionala());
        }
        virtual void adauga_bagaj(int masa_bagaj) = 0;
};

class Motocicleta: public Vehicul{
    private:
        std::string tip;
    public:
        Motocicleta(std::string marca, int masa, std::string tip): Vehicul(marca, masa), tip(tip) {}
        void display(){
            std::cout << "motocicleta " << masa << " " << marca << " " << tip << "\n";
        }
        int masa_aditionala(){
            return 70;
        }
        void adauga_bagaj(int masa){};
};

class Masina: public Vehicul{
    protected:
        int nr_pasageri, capacitate_portbagaj, masa_bagaje;
    public:
        Masina(std::string marca, int masa, int nr_pasageri, int capacitate_portbagaj): Vehicul(marca, masa), nr_pasageri(nr_pasageri), capacitate_portbagaj(capacitate_portbagaj), masa_bagaje(0) {}
        void display(){
            std::cout << "masina " << masa << " " << marca << " " << nr_pasageri << " " << capacitate_portbagaj << "\n";
        }
        int masa_aditionala(){
            return (nr_pasageri + 1) * 70 + masa_bagaje;
        }
        void adauga_bagaj(int bagaj) {
            masa_bagaje += bagaj;
            if(masa_bagaje > capacitate_portbagaj)
                masa_bagaje = capacitate_portbagaj;
        }
};

class MasinaElectrica: public Masina{
    private:
        int masa_baterie;
    public:
        MasinaElectrica(std::string marca, int masa, int nr_pasageri, int capacitate_portbagaj, int masa_baterie): Masina(marca, masa, nr_pasageri, capacitate_portbagaj), masa_baterie(masa_baterie){}
        void display(){
            std::cout << "masina electrica " << masa << " " << marca << " " << nr_pasageri << " " << capacitate_portbagaj << " " << masa_baterie << "\n";
        }
        int masa_aditionala(){
            return (nr_pasageri + 1) * 70 + masa_baterie + masa_bagaje;
        }
        
};

bool compare(Vehicul *&a, Vehicul *&b){
    return a -> viteza_maxima() > b -> viteza_maxima();
}

class ParcAuto{
    private:
        std::vector <Vehicul *> parc;
    public:
        void adauga_vehicul(Vehicul *v){
            parc.push_back(v);
        }
        void display(){
            for(int i = 0; i < parc.size(); i++){
                parc[i] -> display();
            }
        }
        void calcul_masa_aditionala(){
            for(int i = 0; i < parc.size(); i++){
                std::cout << parc[i] -> masa_aditionala() << '\n';
            }
        }
        void calcul_viteza_maxima(){
            for(int i = 0; i < parc.size(); i++){
                std::cout << std::fixed << std::setprecision(2) << parc[i] -> viteza_maxima() << '\n';
            }
        }
        void adauga_bagaj(int index, int masa_bagaj){
            std::cin >> index >> masa_bagaj;
            parc[index] -> adauga_bagaj(masa_bagaj);
            std::cout << parc[index] -> masa_totala() << '\n';
        }
        void sortare_viteza_maxima(){
            std::sort(parc.begin(), parc.end(), compare);
            this -> display();
        }
};

int main(){
    int test, nr_vehicule, masa, nr_pasageri, capacitate_portbagaj, masa_baterie;
    std::string marca, tip, clasa;
    std::cin >> nr_vehicule;
    Vehicul *v;
    ParcAuto parc;
    
    for(int i = 0; i < nr_vehicule; i++){
        std::cin >> masa >> marca >> clasa;
        if(clasa == "moto"){
            std::cin >> tip;
            v = new Motocicleta(marca, masa, tip);
            
        }
        else if(clasa == "auto"){
            std::cin >> nr_pasageri >> capacitate_portbagaj;
            v = new Masina(marca, masa, nr_pasageri, capacitate_portbagaj);
        }
        else{
            std::cin >> nr_pasageri >> capacitate_portbagaj >> masa_baterie;
            v = new MasinaElectrica(marca, masa, nr_pasageri, capacitate_portbagaj, masa_baterie);
        }
        parc.adauga_vehicul(v);
    }
    
    std::cin >> test;
    
    switch(test){
        case 1:{ // afisare
            parc.display();
            break;
        }
        case 2:{ // calcul masa aditionala
            parc.calcul_masa_aditionala();
            break;
        }
        case 3:{ // calcul viteza maxima
            parc.calcul_viteza_maxima();
            break;
        }
        case 4:{ // adauga bagaj
            int index, masa_bagaj;
            parc.adauga_bagaj(index, masa_bagaj);
            break;
        }
        case 5:{ // sortare
            parc.sortare_viteza_maxima();
            break;
        }
    }
    
