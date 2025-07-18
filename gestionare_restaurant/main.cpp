#include <iostream>
#include <string>
#include <iomanip>

class Restaurant{
private:
    std::string nume;
    int nr_preparate;
    std::string *nume_preparate;
    float *preturi_preparate;
    float rating;
    
public:
    Restaurant(std::string nume, int nr_preparate, std::string *nume_preparate, float *preturi_preparate, float rating){
        this->nume = nume;
        this->nr_preparate = nr_preparate;
        this->nume_preparate = new std::string[this->nr_preparate];
        for (int i=0; i<this->nr_preparate; i++){
            *(this->nume_preparate+i) = *(nume_preparate+i);
        }
        this->preturi_preparate = new float[this->nr_preparate];
        for (int i=0; i<this->nr_preparate; i++){
            *(this->preturi_preparate+i) = *(preturi_preparate+i);
        }
        this->rating = rating;
    }
    
    void afisare(){
        std::cout << this->nume << std::endl;
        
        for (int i=0; i<this->nr_preparate; i++){
            std::cout << *(this->nume_preparate+i) << "; ";
        }
        std::cout << std::endl;
        for (int i=0; i<this->nr_preparate; i++){
            std::cout << preturi_preparate[i] << "; ";
        }
        std::cout << std::endl;
    }
    
    void verificare_meniu(std::string preparat){
        bool found = false;
        // int found = 0;
        for (int i=0; i<this->nr_preparate; i++){
            if (*(this->nume_preparate+i) == preparat){
                found = true;
                // found = 1;
                std::cout << *(this->nume_preparate+i) << " " << *(this->preturi_preparate+i) << std::endl;
                break;
            }
        }
        
        if (!found){
            for (int i=0; i<this->nr_preparate; i++){
                std::cout << *(this->nume_preparate+i) << std::endl;
            }
        }
    }
    
    void actualizare_rating(float new_rating){
        this->rating = (this->rating + new_rating) / 2;
    }
    
    float get_rating(){return this->rating;}
    
    void majorare_preturi(float procent){
        for (int i=0; i<this->nr_preparate; i++){
            *(this->preturi_preparate+i) += procent/100 * *(this->preturi_preparate+i);
        }
    }
};


int main(){
    std::string temp_nume;
    int temp_nr_produse;
    std::string *temp_nume_produse = nullptr;
    float *temp_preturi_produse = nullptr;
    float temp_rating;
    std::string temp_nume_produs;
    int comanda;
    float majorare;
    
    std::getline(std::cin, temp_nume);
    std::cin >> temp_nr_produse;
    temp_nume_produse = new std::string[temp_nr_produse];
    temp_preturi_produse = new float[temp_nr_produse];
    std::cin.ignore();
    for (int i=0; i<temp_nr_produse; i++){
        std::getline(std::cin, temp_nume_produse[i]);
    }
    for (int i=0; i<temp_nr_produse; i++){
        std::cin >> temp_preturi_produse[i];
    }
    std::cin >> temp_rating;
    std::cin >> comanda;
    std::cout << std::fixed << std::setprecision(2);
    
    // Restaurant r(std::string temp_nume); // antet de functie
    Restaurant r(temp_nume, temp_nr_produse, temp_nume_produse, temp_preturi_produse, temp_rating); // apel de functie
    
    switch(comanda){
        case 1:{
            r.afisare();
            break;
        }
        
        case 2:{
            std::cin.ignore();
            std::getline(std::cin, temp_nume_produs);
            r.verificare_meniu(temp_nume_produs);
            break;
        }
        
        case 3:{
            std::cin >> temp_rating;
            r.actualizare_rating(temp_rating);
            std::cout << r.get_rating();
            break;
        }
        
        case 4:{
            std::cin >> majorare;
            r.majorare_preturi(majorare);
            r.afisare();
            break;
        }
    }
    
    return 0;
}
