#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

class Publicatie{
    protected:
        std::string titlu;
        int nr_autori, an_publicare, nr_citari;
    public:
        Publicatie(std::string titlu, int nr_autori, int an_publicatie, int nr_citari): titlu(titlu), nr_autori(nr_autori), an_publicare(an_publicatie), nr_citari(nr_citari) {}
        virtual void display() = 0;
        virtual float punctaj(int an) = 0;
        int get_nr_citari() { return nr_citari;}
};

class Conferinta: public Publicatie{
    private:
        std::string ISI;
    public:
        Conferinta(std::string titlu, int nr_autori, int an_publicatie, int nr_citari, int cod): Publicatie(titlu, nr_autori, an_publicatie, nr_citari){
            if(cod)
                ISI = "ISI";
            else
                ISI = "non-ISI";
        }
        void display(){
            std::cout << titlu << ", " << nr_autori << ", " << an_publicare << ", " << nr_citari << ", " << ISI <<'\n';
        }
        float punctaj(int an){
            if(an_publicare == an){
                if(ISI == "ISI")
                    return 0.75;
                return 0.25;
            }
            return 0;
        }
};

class Revista: public Publicatie{
    private:
        int percentila;
    public:
        Revista(std::string titlu, int nr_autori, int an_publicatie, int nr_citari, int cod): Publicatie(titlu, nr_autori, an_publicatie, nr_citari), percentila(cod) {}
        void display(){
            std::cout << titlu << ", " << nr_autori << ", " << an_publicare << ", " << nr_citari << ", Q" << percentila << '\n';
        }
        float punctaj(int an){
            if(an_publicare == an){
                if(percentila == 1)
                    return 1.0 * 20/nr_autori;
                if(percentila == 2)
                    return 1.0 * 10/nr_autori;
                return 1.0 * 5/nr_autori;
            }
            return 0;
        }
};

bool compare(Publicatie *&a, Publicatie *&b){
    return a->get_nr_citari() >= b->get_nr_citari();
}

class Profil{
    private:
        std::string nume;
        int nr_publicatii;
        std::vector <Publicatie*> publicatii;
    public:
        Profil(){
            getline(std::cin, this->nume);
            std::cin >> nr_publicatii;
            
            std::string titlu, tip;
            int cod, nr_autori, an_publicatie, nr_citari; 
            for(int i=0; i < nr_publicatii; i++){
                std::cin.ignore();
                getline(std::cin, titlu);
                std::cin >> nr_autori >> an_publicatie >> nr_citari >> tip >> cod;
                
                if(tip == "conferinta")
                    publicatii.push_back(new Conferinta(titlu, nr_autori, an_publicatie, nr_citari, cod));
                else
                    publicatii.push_back(new Revista(titlu, nr_autori, an_publicatie, nr_citari, cod));
            }
        }
        void display(){
            std::cout << nume << '\n';
            for(int i=0; i<nr_publicatii; i++){
                publicatii[i] -> display();
            }
        }
        void punctaj_anual(int an){
            float punctaj = 0;
            for(int i=0; i<publicatii.size(); i++)
                punctaj += publicatii[i]->punctaj(an);
            std::cout << punctaj << '\n';
        }
        void i10(){
            int nr = 0;
            for(int i = 0; i < publicatii.size(); i++)
                if(publicatii[i] -> get_nr_citari() > 10) nr++;
            std::cout << nr;
        }
        void h_index(){
            std::sort(publicatii.begin(), publicatii.end(), compare);
            int ans;
            bool ok = 0;
            for(int h = 1; h < nr_publicatii; h++){
                ok = 1;
                for(int i=0; i<h; i++)
                    if(publicatii[i] -> get_nr_citari() < h){
                        ok = 0;
                        break;
                    }
                if(ok)  ans = h;
            }
            
            std::cout << ans;
        }
};

int main()
{
    Profil cercetator;
    int test;
    std::cin >> test;
    
    switch (test){
        case 1:{
            cercetator.display();
            break;
        }
        
        case 2:{
            cercetator.punctaj_anual(2023);
            cercetator.punctaj_anual(2022);
            cercetator.punctaj_anual(2021);
            break;
        }
        
        case 3:{
            cercetator.i10();
            break;
        }
        
        case 4:{
            cercetator.h_index();
            break;
        }
    }
