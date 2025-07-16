#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>

class Camera{
    protected:
        std::string tip;
        int nr_camera, pers_cazate, capacitate;
        float pret;
        
    public:
        Camera(std::string tip, int nr_camera, int pers_cazate, int pret, int capacitate): tip(tip), nr_camera(nr_camera), pers_cazate(pers_cazate), pret(pret), capacitate(capacitate){}
        void afisare(){
            std::cout << nr_camera << " " << tip << " " << pers_cazate << " " << pret << '\n';
        }
        bool camera_ocupata(){return pers_cazate>0;}
        int locuri_libere(){
            if(this->camera_ocupata() == 0)
                return capacitate;
            return 0;
        }
        int get_capacitate(){return capacitate;}
        float get_pret(){return pret;}
};

class Single: public Camera{
    public:
        Single(std::string tip, int nr_camera, int pers_cazate, int pret): Camera(tip, nr_camera, pers_cazate, pret, 1){}
};

class Twin: public Camera{
    public:
       Twin(std::string tip, int nr_camera, int pers_cazate, int pret): Camera(tip, nr_camera, pers_cazate, pret, 2){}
};

class Double: public Camera{
    public:
        Double(std::string tip, int nr_camera, int pers_cazate, int pret): Camera(tip, nr_camera, pers_cazate, pret, 2){}
};

class Triple: public Camera{
    public:
        Triple(std::string tip, int nr_camera, int pers_cazate, int pret): Camera(tip, nr_camera, pers_cazate, pret, 3){}
};

bool compare(Camera *&a, Camera *&b){
    return (a->get_capacitate() < b->get_capacitate()) || ((a->get_capacitate() == b->get_capacitate()) && (a->get_pret() < b->get_pret()));    
}

class Hotel{
    private:
        std::vector <Camera*> vec;
    public:
        void adauga_camera(Camera *c){
            vec.push_back(c);
        }
        void afisare_camere(){
            for(int i=0; i<vec.size(); i++)
                vec[i]->afisare();
        }
        float grad_ocupare(){
            int nr = 0;
            for(int i=0; i<vec.size(); i++)
                nr += vec[i]->camera_ocupata();
            return 1.0 * nr / vec.size() * 100;
        }
        int capacitate_ramasa(){
            int cap = 0;
            for(int i=0; i<vec.size(); i++){
                cap += vec[i]->locuri_libere();
            }
            return cap;
        }
        void sortare_camere(){
            sort(vec.begin(), vec.end(), compare);
        }
};

int main(){
    int test;
    Hotel gestiune_hotel;
    do{
        std::cin >> test;
        switch(test){
            case 1:{
                Camera *c = nullptr;
                int nr_camera, pers_cazate;
                std::string tip_camera;
                float pret;
                std::cin >> nr_camera >> tip_camera >> pers_cazate >> pret;
                if(tip_camera == "single")
                    c = new Single(tip_camera, nr_camera, pers_cazate, pret);
                else if(tip_camera == "twin")
                    c = new Twin(tip_camera, nr_camera, pers_cazate, pret);
                else if(tip_camera == "triple")
                    c = new Triple(tip_camera, nr_camera, pers_cazate, pret);
                else
                    c = new Double(tip_camera, nr_camera, pers_cazate, pret);
                
                gestiune_hotel.adauga_camera(c);
                break;
            }
            case 2:{
                gestiune_hotel.afisare_camere();
                break;
            }
            case 3:{
                std::cout << std::fixed << std::setprecision(2) << gestiune_hotel.grad_ocupare();
                break;
            }
            case 4:{
                std::cout << gestiune_hotel.capacitate_ramasa();
                break;
            }
            case 5:{
                gestiune_hotel.sortare_camere();
                gestiune_hotel.afisare_camere();
                break;
            }
        }
    }while(test!=-1);
}
