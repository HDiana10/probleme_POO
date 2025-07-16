#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

class Participant{
    private:
        std::string nume, piesa;
        int punctaj, voturi[4] = {0};
        std::string tara[4];
    public:
        Participant(std::string nume, std::string piesa, int pct): nume(nume), piesa(piesa), punctaj(pct){}
        std::string get_nume(){ return nume; }
        std::string get_piesa(){ return piesa; }
        int get_punctaj(){ return punctaj; }
        int get_voturi(){ return voturi[0];}
        std::string get_vot(int poz){ return tara[poz]; }
        void afisare(){
            std::cout << nume << " " << piesa << " " << punctaj << '\n';
        }
        void votare(){
            for(int i=0; i<4; i++)
                std::cin >> tara[i];
        }
        void actualizare_punctaj(int pct){ this->punctaj += pct; }
        void update_voturi(int p){ voturi[p]++; }
};

bool compare(Participant *&a, Participant *&b){
    return (a->get_punctaj() > b->get_punctaj()) || (a->get_punctaj() == b->get_punctaj() && a->get_voturi() > b->get_voturi());
}

class Eurovision{
    private:
        std::vector <Participant*> vec;
    public:
        void adauga_participant(std::string nume, std::string piesa, int pct){
            vec.push_back(new Participant(nume, piesa, pct));
        }
        void afisare_participanti(){
            for(int i = 0; i < vec.size(); i++)
                vec[i] -> afisare();
        }
        void votare(){
            for(int i = 0; i < vec.size(); i++){
                vec[i] -> votare();
                for(int j=0, p=7; j<4; j++, p-=2){
                    std::string tara = vec[i] -> get_vot(j);
                    for(int k = 0; k < vec.size(); k++)
                        if(vec[k] -> get_nume() == tara){
                            vec[k] -> actualizare_punctaj(p);
                            break;
                        }
                }
            }
        }
        void tara_populara(){
            int nr_vot_max = 0, poz = 0;
            for(int i=0; i<vec.size(); i++){
                int nr_vot = 0;
                for(int j=0; j<vec.size(); j++){
                    if(j != i){
                        std::string tara = vec[i] -> get_nume();
                        for(int k=0; k<4; k++){
                            if(vec[j] -> get_vot(k) == tara)
                                nr_vot ++;
                                vec[i]->update_voturi(k);
                        }
                    }
                if(nr_vot > nr_vot_max)
                    nr_vot_max = nr_vot, poz = i;
                }
            }
            vec[poz] -> afisare();
        }
        void clasament(){
            std::sort(vec.begin(), vec.end(), compare);
            this->afisare_participanti();
        }
};

int main(){
    int test;
    Eurovision concurs;
    
    while (test != 6) {
        std::cin>>test;
        switch(test){
            case 1:{
                std::string nume, piesa;
                std::cin >> nume >> piesa;
                concurs.adauga_participant(nume, piesa, 0);
                break;
            }
            case 2:{ // afisare
                concurs.afisare_participanti();
                break;
            }
            case 3:{ // votare
                concurs.votare();
                break;
            }
            case 4:{
                concurs.tara_populara();
                break;
            }
            case 5:{
                concurs.clasament();
                break;
            }
            default:{
                break;
            }
        }
    } while (test != 6);
}
