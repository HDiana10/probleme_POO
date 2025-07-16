#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>

class EvenimentMedical{
    protected:
        std::string tip, sectie;
        int luna, an;
    public:
        EvenimentMedical(std::string tip, int luna, int an, std::string sectie): tip(tip), luna(luna), an(an), sectie(sectie){}
        std::string get_tip(){ return tip; }
        std::string get_sectie() { return sectie; }
        int get_luna() { return luna; }
        int get_an() { return an; }
        virtual std::string get_diagnostic() = 0;
        virtual void afisare() = 0;  
        virtual int consultatie() = 0;
        virtual int nr_zile() = 0;
        bool data(int a, int l){
            int l1, l2;
            l2 = a*100 + l;
            if(l<6){
                l1 = (a-1)*100 + (12 - l + 5);
            }
            else l1 = a*100 + l-6;
            
            if(l1<= an*100+luna && an*100+luna <=l2)
                return 1;
            return 0;
        }
        bool verif_data(int an, int luna){
            if(this->an >an)
                return 1;
            if(this->an == an && this->luna > luna)
                return 1;
            return 0;
        }
};

class Consultatie: public EvenimentMedical{
    private:
        std::string diagnostic;
    public:
        Consultatie(std::string tip, int luna, int an, std::string sectie, std::string rezultat): diagnostic(rezultat), EvenimentMedical(tip, luna, an, sectie){}
        void afisare(){
            std::cout << "Consultatie\n" << luna << "." << an << "," << sectie << ":" << diagnostic << '\n';
        }
        int consultatie() { return 1; }
        int nr_zile(){ return 0; }
        std::string get_diagnostic() { return diagnostic; }
};

class Internare: public EvenimentMedical{
    private:
        int zile_internare;
    public:
        Internare(std::string tip, int luna, int an, std::string sectie, int nr_zile): zile_internare(nr_zile), EvenimentMedical(tip, luna, an, sectie){}
        void afisare(){
            std::cout << "Internare\n" << luna << "." << an << "," << sectie << ":" << zile_internare << '\n';
        }
        int consultatie() { return 0; }
        int nr_zile() { return zile_internare; }
        std::string get_diagnostic(){return "";}
};

bool compare(EvenimentMedical *&a, EvenimentMedical *&b){
    return a->nr_zile() > b->nr_zile();
}

class DosarMedical{
    private:
        std::string pacient;
        int comorbiditati;
        std::vector <EvenimentMedical*> agenda;
    public:
        DosarMedical(){
            int nr_evenimente, luna, an, nr_zile;
            std::string tip, sectie, diagnostic;
            std::cin >> nr_evenimente;
            std::cin.ignore();
            getline(std::cin, this->pacient);
            std::cin >> this->comorbiditati;
            
            for(int i = 0; i < nr_evenimente; i++){
                std::cin >> an >> luna;
                std::cin.ignore();
                getline(std::cin, sectie);
                std::cin >> tip;
                if(tip == "Consultatie"){
                    std::cin >> diagnostic;
                    agenda.push_back( new Consultatie(tip, luna, an, sectie, diagnostic));
                }
                else{
                    std::cin >> nr_zile;
                    agenda.push_back( new Internare(tip, luna, an, sectie, nr_zile));
                }
            }
        }
        void afisare(){
            std::cout << pacient << '\n';
            
            for(int i=0; i<agenda.size(); i++)
                agenda[i]->afisare();
        }
        void evenimente_anuale(int an){
            int zile_internare = 0, consultatii = 0;
            for(int i = 0; i<agenda.size(); i++)
                if(an == agenda[i] -> get_an()){
                    zile_internare += agenda[i] -> nr_zile();
                    consultatii += agenda[i] -> consultatie();
                }
            std::cout << an << ": zile internare=" << zile_internare << ", consultatii=" << consultatii << '\n';
        }
        int LACE(){
            int nr_internari, nr_zile, an = 2022, luna = 12;
            for(int i=0; i<agenda.size(); i++)
                if(agenda[i] -> get_tip() == "Internare"){
                if(agenda[i] -> data(2023, 5)) nr_internari++;
                if(agenda[i] -> verif_data(an, luna))
                    nr_zile = agenda[i] -> nr_zile();
                }
                else{
                    if(agenda[i] -> get_diagnostic() == "Bolnav") this->comorbiditati +=1;
                }
            
            return nr_internari + nr_zile + comorbiditati;
        }
        void sortare(){
            std::sort(agenda.begin(), agenda.end(), compare);
            for(int i=0; i<agenda.size(); i++)
                if(agenda[i]->get_tip() =="Internare")
                    std::cout<< agenda[i]->get_luna() << "." << agenda[i]->get_an() << ":" << agenda[i]->get_sectie() << ":" << agenda[i]->nr_zile() << '\n';
        }
};

int main(){
    DosarMedical dosar;
    
    int test;
    std::cin>>test;
    
    switch(test){
        case 1:{ //afisare dosar medical
            dosar.afisare();
            break;
        }
        case 2:{ //calcul evenimente anuale
            dosar.evenimente_anuale(2022);
            dosar.evenimente_anuale(2023);
            break;
        }
        case 3:{ // calcul scor reinternare
            std::cout << dosar.LACE() << '\n';
            break;
        }
        case 4:{ // sortare
            dosar.sortare();
            break;
        }
    }
}
