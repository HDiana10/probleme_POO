#include <iostream>
#include <string>
#include <iomanip>

class Semnal{
private:
    std::string tip;
    int nr_esantioane;
    float *esantioane;
    
public:
    Semnal(std::string tip, int nr_esantioane, float *esantioane){
        this->tip = tip;
        this->nr_esantioane = nr_esantioane;
        this->esantioane = new float[this->nr_esantioane];
        for (int i=0; i<nr_esantioane; i++){
            *(this->esantioane + i) = *(esantioane+i);
            // this->esantioane[i] = esantioane[i];
        }
    }
    
    Semnal(const Semnal &s){
        this->tip = s.tip;
        this->nr_esantioane = s.nr_esantioane;
        this->esantioane = new float[this->nr_esantioane];
        for (int i=0; i<this->nr_esantioane; i++){
            *(this->esantioane + i) = *(s.esantioane+i);
        }
    }
    
    void display(){
        std::cout<<this->tip<<std::endl;
        for (int i=0; i<this->nr_esantioane; i++){
            std::cout << this->esantioane[i] << " ";
        }
        std::cout << std::endl;
    }
    
    float putere_semnal(){
        float suma=0;
        for (int i=0; i<this->nr_esantioane; i++){
            suma += (this->esantioane[i]*this->esantioane[i]);
        }
        return suma/this->nr_esantioane;
    }
    
    int get_nr_esantioane(){
        return this->nr_esantioane;
    }
    
    float* get_esantioane(){
        return this->esantioane;
    }
};

Semnal adaugare_zgomot(Semnal semnal_util, Semnal semnal_zgomot){
    std::string tip = "util+zgomot";
    int nr_esantioane = semnal_util.get_nr_esantioane();
    float *esantioane_suma = new float[nr_esantioane];
    for (int i=0; i<nr_esantioane; i++){
        esantioane_suma[i] = *(semnal_util.get_esantioane()+i) + *(semnal_zgomot.get_esantioane()+i);
    }
    return Semnal(tip, nr_esantioane, esantioane_suma);
}

Semnal convolutie(Semnal semnal_util, Semnal semnal_util_zgomot){
    std::string tip = "convolutie";
    int nr_esantioane = semnal_util.get_nr_esantioane();
    float *esantioane_suma = new float[nr_esantioane];
    for (int i=0; i<nr_esantioane; i++){
        esantioane_suma[i] = *(semnal_util.get_esantioane()+i) * *(semnal_util_zgomot.get_esantioane()+nr_esantioane-1-i);
    }
    return Semnal(tip, nr_esantioane, esantioane_suma);
}


int main(){
    std::string temp_tip;
    int temp_nr_esantioane;
    float *temp_esantioane = nullptr;
    int comanda;
    
    std::cin >> temp_tip;
    std::cin >> temp_nr_esantioane;
    temp_esantioane = new float[temp_nr_esantioane];
    for (int i=0; i<temp_nr_esantioane; i++){
        std::cin >> temp_esantioane[i];
    }
    
    Semnal s1(temp_tip, temp_nr_esantioane, temp_esantioane);
    
    std::cin >> comanda;
    
    switch(comanda){
        case 1:{
            s1.display();
            break;
        }
        
        case 2:{
            std::cout << std::fixed << std::setprecision(2) << s1.putere_semnal();
            break;
        }
        
        case 3:{
            std::cin >> temp_tip;
            std::cin >> temp_nr_esantioane;
            temp_esantioane = new float[temp_nr_esantioane];
            for (int i=0; i<temp_nr_esantioane; i++){
                std::cin >> temp_esantioane[i];
            }
            
            Semnal S_zgomot(temp_tip, temp_nr_esantioane, temp_esantioane);
            
            Semnal S_util_zgomot = adaugare_zgomot(s1, S_zgomot);
            S_util_zgomot.display();
            s1.display();
            
            break;
        }
        
        case 4:{
            std::cin >> temp_tip;
            std::cin >> temp_nr_esantioane;
            temp_esantioane = new float[temp_nr_esantioane];
            for (int i=0; i<temp_nr_esantioane; i++){
                std::cin >> temp_esantioane[i];
            }
            
            Semnal S_zgomot(temp_tip, temp_nr_esantioane, temp_esantioane);
            Semnal s_copie(s1);
            Semnal S_util_zgomot = adaugare_zgomot(s1, S_zgomot);
            Semnal s_convolutie = convolutie(s_copie, S_util_zgomot);
            s_convolutie.display();
            
            break;
        }
    }
    
    
    return 0;
}
