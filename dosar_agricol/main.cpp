#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <iomanip>

class ActivitateAgricola{
    protected:
        int luna, an, numar_hectare;
        std::string nume_cultura, tip;
    public:
        ActivitateAgricola(std::string tip, std::string nume, int luna, int an, int nr): tip(tip), nume_cultura(nume), luna(luna), an(an), numar_hectare(nr){}
        int get_an(){ return an; }
        std::string get_tip(){ return tip; }
        int get_luna() { return luna; }
        virtual int get_cantitate() = 0;
        virtual void afisare() = 0;
        virtual void calcul_activitate(int &nr, int &kg) = 0;
        virtual void evaluare(int &nr_insamantari, int &nr_recolte, int &nr_hectare, int &cant_recolta, int &cant_seminte) = 0;
};

class Insamantare: public ActivitateAgricola{
    private:
        int cantitate_seminte;
    public:
        Insamantare(std::string tip, std::string nume, int luna, int an, int nr, int cant): cantitate_seminte(cant), ActivitateAgricola(tip, nume, luna, an, nr){}
        void afisare(){
            std::cout << tip << '\n' << luna << "." << an << ":" << nume_cultura << ", Cantitate seminte:" << cantitate_seminte << '\n';
        }
        void calcul_activitate(int &nr, int &kg){ nr ++;}
        void evaluare(int &nr_insamantari, int &nr_recolte, int &nr_hectare, int &cant_recolta, int &cant_seminte){
            nr_insamantari ++;
            nr_hectare += numar_hectare;
            cant_seminte += cantitate_seminte;
        }
        int get_cantitate(){ return cantitate_seminte; }
};

class Recolta: public ActivitateAgricola{
    private:
        int cantitate_recolta;
    public:
        Recolta(std::string tip, std::string nume, int luna, int an, int nr, int cant): cantitate_recolta(cant), ActivitateAgricola(tip, nume, luna, an, nr){}
        void afisare(){
            std::cout << tip << '\n' << luna << "." << an << ":" << nume_cultura << ", Cantitate recoltata:" << cantitate_recolta << '\n';
        }
        void calcul_activitate(int &nr, int &kg){ kg += cantitate_recolta;}
        void evaluare(int &nr_insamantari, int &nr_recolte, int &nr_hectare, int &cant_recolta, int &cant_seminte){
            nr_recolte ++;
            cant_recolta += cantitate_recolta;
        }
        int get_cantitate(){ return cantitate_recolta; }
};

bool compare(ActivitateAgricola *&a, ActivitateAgricola *&b){
    if(a -> get_tip() != b -> get_tip())
        return a -> get_tip() == "Insamantare";
    return a -> get_cantitate() < b -> get_cantitate();
}

class DosarAgricol{
    protected:
        std::string nume_fermier;
        std::vector <ActivitateAgricola*> agenda;
    public:
        DosarAgricol(std::string nume): nume_fermier(nume){
            int nr_evenimente, nr_hectare, luna, anul, cant;
            std::string nume_plante, tip;
            
            std::cin >> nr_evenimente;
            
            for(int i = 0; i < nr_evenimente; i++){
                std::cin >> nume_plante >> nr_hectare >> luna >> anul >> tip >> cant;
                if(tip == "Insamantare")
                    agenda.push_back(new Insamantare(tip, nume_plante, luna, anul, nr_hectare, cant));
                else
                    agenda.push_back(new Recolta(tip, nume_plante, luna, anul, nr_hectare, cant));
            }
        }
        void afisare(){
            std::cout << nume_fermier << '\n';
            for(int i = 0; i < agenda.size(); i++)
                agenda[i] -> afisare();
        }
        void calcul_activitate(int an){
            int nr_insamantari = 0, kg_recoltate = 0;
            for(int i = 0; i < agenda.size(); i++)
                if(an == agenda[i] -> get_an())
                    agenda[i] -> calcul_activitate(nr_insamantari, kg_recoltate);
            std::cout << an << ": nr insamantari=" << nr_insamantari << ", kg recoltate=" << kg_recoltate << "\n";
        }
        void evaluare(int an1, int an2){
            int nr_insamantari = 0, nr_recolte = 0, nr_hectare = 0, cant_recoltata = 0, cant_seminte = 0, performanta;
            float eficienta;
            for(int i=0; i<agenda.size(); i++)
                if(an1 <= agenda[i] -> get_an() && agenda[i] -> get_an() <= an2){
                    agenda[i] -> evaluare(nr_insamantari, nr_recolte, nr_hectare, cant_recoltata, cant_seminte);
                }
            performanta = nr_recolte - nr_insamantari + nr_hectare;
            eficienta = 1.0 * cant_recoltata / cant_seminte;
            
            std::cout << "Performanta:" << performanta << "\nEficienta:" << std::fixed << std::setprecision(2) << eficienta <<'\n';
        }
        void ordonare(){
            std::sort(agenda.begin(), agenda.end(), compare);
            int ok = 0, i;
            for(i = 0; i < agenda.size() && agenda[i] -> get_tip() == "Insamantare"; i++){
                if(ok == 0){ std:: cout << "Insamantari:\n"; ok = 1;}
                std::cout << agenda[i] -> get_luna() << "." << agenda[i] -> get_an() << ":" << agenda[i] -> get_cantitate() << '\n'; 
            }
            for(; i < agenda.size(); i++){
                if(ok == 1){ std:: cout << "\nRecolte:\n"; ok = 0;}
                std::cout << agenda[i] -> get_luna() << "." << agenda[i] -> get_an() << ":" << agenda[i] -> get_cantitate() << '\n'; 
            }
        }
};

int main(){
    int test;
    std::string nume_fermier;
    std::cin >> test;
    std::cin.ignore();
    getline(std::cin, nume_fermier);
    
    DosarAgricol dosar(nume_fermier);
    
    switch (test){
        case 1:{
            dosar.afisare();
            break;
        }
        case 2:{
            dosar.calcul_activitate(2022);
            dosar.calcul_activitate(2023);
            break;
        }
        case 3:{
            dosar.evaluare(2022, 2023);
            break;
        }
        case 4:{
            dosar.ordonare();
            break;
        }
    }
}
