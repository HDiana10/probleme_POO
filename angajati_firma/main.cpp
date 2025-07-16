#include <iostream>
#include <string>
#include <vector>

class Angajat{
    protected:
        std::string nume, functie;
        float salariu_baza, procent_taxe = 40;
    public:
        Angajat(std::string nume="", std::string functie="", float salariu_baza=0): nume(nume), functie(functie), salariu_baza(salariu_baza){}
        virtual float get_salariu_net()=0;
        virtual float get_salariu_brut()=0;
        float get_salariu_baza(){return salariu_baza;}
        std::string get_nume(){return nume;}
        std::string get_functie(){return functie;}
        void marire_salariu(float p){this-> salariu_baza = (100+p)*salariu_baza/100;}
        virtual ~Angajat(){std::cout<<"Destructor Angajat\n";}
};

class Analist: public Angajat{
    public:
        Analist(std::string nume, std::string functie, float salariu_baza): Angajat(nume, functie, salariu_baza){}
        float get_salariu_brut(){return salariu_baza;}
        float get_salariu_net(){return (salariu_baza) * (100 - procent_taxe)/100;} 
        void marire_salariu(float p){}
        ~Analist(){std::cout<<"Destructor Analist\n";}
};

class Programator: public Analist{
    protected:
        float procent_deducere_salariu_it = 10;
    public:
        Programator(std::string nume, std::string functie, float salariu_baza): Analist(nume, functie, salariu_baza){}
        float get_salariu_brut(){return salariu_baza;}
        float get_salariu_net(){return (salariu_baza) * (100 - procent_taxe + procent_deducere_salariu_it)/100;}
        ~Programator(){std::cout<<"Destructor Programator\n";}
};

class LiderEchipaProgramare: public Programator{
    protected:
        float bonus_vechime_functie = 500;
        int vechime_functie;
    public:
        LiderEchipaProgramare(int vechime, std::string nume, std::string functie, float salariu_baza): vechime_functie(vechime), Programator(nume, functie, salariu_baza){}
        float get_salariu_brut(){return salariu_baza + bonus_vechime_functie * vechime_functie;}
        float get_salariu_net(){return (salariu_baza + bonus_vechime_functie * vechime_functie) * (100 - procent_taxe + procent_deducere_salariu_it)/100;}
};

class FirmaProgramare{
    private:
        std::vector <Angajat*> vec;
    public:
        void adauga_angajat(Angajat* a){
            vec.push_back(a);
        }
        void afiseaza_angajati(){
            for(int i=0; i<vec.size(); i++)
                std::cout<< vec[i]->get_nume() << "\n" << vec[i]->get_functie() << "\n";
        }
        void calcul_salarii(){
            for(int i=0; i<vec.size(); i++){
                std::cout << vec[i]->get_nume() << '\n';
                std::cout << "Salariu brut: " << vec[i]->get_salariu_brut() << "\n";
                std::cout << "Salariu Net: " << vec[i]->get_salariu_net() << "\n";
            }
        }
        void mareste_salarii(float p1, float p2, float p3){
            for(int i=0; i<vec.size(); i++){
                std::cout<< vec[i]->get_nume() << "\nSalariu de baza vechi: " << vec[i]->get_salariu_baza() << "\n";
                if(vec[i]->get_functie() == "Analist")
                    vec[i]->marire_salariu(p1);
                else if(vec[i]->get_functie() == "Programator")
                    vec[i]->marire_salariu(p2);
                else
                    vec[i]->marire_salariu(p3);
                std::cout<< "Salariu de baza nou: " << vec[i]->get_salariu_baza() << "\n";
            }
        }
        void promoveaza(std::string nume, std::string functie){
            for(int i=0; i<vec.size(); i++)
                if(vec[i]->get_nume() == nume)
                {
                    Angajat *a = nullptr;
                    if(functie=="Analist")
                        a = new Analist(nume, functie, vec[i]->get_salariu_baza());
                    else if(functie == "Programator")
                        a = new Programator(nume, functie, vec[i]->get_salariu_baza());
                    else
                        a = new LiderEchipaProgramare(0, nume, functie, vec[i]->get_salariu_baza());
                    delete vec[i];
                    vec[i] = a;
                    break;
                }
        }
};

int main()
{
    int nr_angajati;
    Angajat *temp_angajat=nullptr;
    int vechime;
    float salariu_baza;
    std::string nume, functie;
    FirmaProgramare firma;
    
    std::cin >> nr_angajati;
    
    for(int i=0; i<nr_angajati; i++)
    {
        std::cin.ignore();
        std::getline(std::cin, nume);
        std::getline(std::cin, functie);
        std::cin >> salariu_baza;
        if(functie == "Analist")
            temp_angajat = new Analist(nume, functie, salariu_baza);
        else if(functie == "Programator"){
            temp_angajat = new Programator(nume, functie, salariu_baza);
        }
        else{
            std::cin>> vechime;
            temp_angajat = new LiderEchipaProgramare(vechime, nume, functie, salariu_baza);
        }
        firma.adauga_angajat(temp_angajat);
    }
    
    int comanda;
    std::cin>>comanda;
    
    switch(comanda){
        case 1:{
            firma.afiseaza_angajati();
            break;
        }
        
        case 2:{
            firma.calcul_salarii();
            break;
        }
        case 3:{
            std::string functie[3];
            float procent[3];
            
            for(int i=0; i<3; i++){
                std::cin >> functie[i] >> procent[i];
            }
            
            if(functie[0] != "Analist")
                if(functie[1] == "Analist")
                    std::swap(functie[0], functie[1]), std::swap(procent[0], procent[1]);
                else
                    std::swap(functie[0], functie[2]), std::swap(procent[0], procent[2]);
            if(functie[1] != "Programator")
                std::swap(functie[1], functie[2]);
                
            firma.mareste_salarii(procent[0], procent[1], procent[2]);
            break;
        }
        
        case 4:{
            std::cin.ignore();
            std::getline(std::cin, nume);
            std::getline(std::cin, functie);
            firma.promoveaza(nume, functie);
            firma.afiseaza_angajati();
            break;
        }
    }
}
