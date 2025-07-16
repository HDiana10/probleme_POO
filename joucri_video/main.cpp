#include <algorithm>
#include <iomanip>


class JocVideo{
    protected:
        std::string nume;
        int zi, luna, an, nr_note;
        std::vector <int> note;
    public:
        virtual void display() = 0;
        virtual void get_playtime(int a, float b) = 0;
        JocVideo(std::string nume, int ziua, int luna, int anul, int nr_note, std::vector <int> note): nume(nume), zi(ziua), luna(luna), an(anul), nr_note(nr_note), note(note) {}
        std::string get_nume(){ return nume; }
        float get_nota(){
            int ma=0;
            for(int i=0; i<nr_note; i++) ma += note[i];
            return 1.0 * ma/nr_note;
        }
        int get_zi(){ return zi;}
        int get_an(){ return an;}
        int get_luna(){ return luna;}
        virtual void afisare() = 0;
        int verif_data(int zi, int luna, int an){
            if(this->an > an)
                return 1;
            if(this->an == an)
                if(this->luna > luna)
                    return 1;
                else if(this->luna == luna && this->zi >= zi)
                    return 1;
            return 0;
        }
};

class JocSinglePlayer: public JocVideo{
    private:
        int nr_nivele;
    public:
        JocSinglePlayer(std::string nume, int ziua, int luna, int anul, int nr_note, std::vector <int> note, int nr_nivele): JocVideo(nume, ziua, luna, anul, nr_note, note), nr_nivele(nr_nivele){}
        void display(){
            std::cout << "singleplayer: " << nume << " - " << zi << " " << luna << " " << an << " - " << nr_nivele << '\n';
        }
        void afisare(){ std::cout << nume <<": singleplayer\n"; }
        void get_playtime(int a, float b){
            std::cout  << std::fixed << std::setprecision(2) << 1.0 * nr_nivele * a * b <<'\n';
        }
};

class JocMultiPlayer: public JocVideo{
    private:
        int nr_meciuri;
    public:
        JocMultiPlayer(std::string nume, int ziua, int luna, int anul, int nr_note, std::vector <int> note, int nr_meciuri): JocVideo(nume, ziua, luna, anul, nr_note, note), nr_meciuri(nr_meciuri){}
        void display(){
            std::cout << "multiplayer: " << nume << " - " << zi << " " << luna << " " << an << " - " << nr_meciuri << '\n';
        }
        void afisare(){ std::cout << nume << ": multiplayer\n"; }
        void get_playtime(int a, float b){
            std::cout  << std::fixed << std::setprecision(2) << 1.0 * nr_meciuri / a * b << '\n';
        }
};

bool comp(JocVideo *&a, JocVideo *&b){
    if(a->get_an() > b->get_an())
        return 0;
    if(a->get_an() == b->get_an())
        if(a->get_luna() > b->get_luna())
            return 0;
        else if(a->get_luna() == b->get_luna() && a->get_zi() > b->get_zi())
            return 0;
    return 1;
}

class JocVideoHandler{
    private:
        std::vector <JocVideo*> joc;
        
    public:
        void adauga_joc(JocVideo *temp){
            joc.push_back(temp);
        }
        void display(){
            for(int i=0; i<joc.size(); i++){
                joc[i]->display();
            }
        }
        void nota_maxima(){
            float nota_maxima=0, k;
            for(int i=0; i<joc.size(); i++)
                if(joc[i]->get_nota() > nota_maxima)
                    nota_maxima = joc[i]->get_nota(), k = i;
            
            std::cout << joc[k]-> get_nume() << ": " << std::fixed << std::setprecision(2) << nota_maxima <<'\n';
        }
        void filtrare(int zi, int luna, int an){
            for(int i=0; i<joc.size(); i++)
                if(joc[i]->verif_data(zi, luna, an))
                    joc[i]->afisare();
        }
        void nou_vechi(){
            std::sort(joc.begin(), joc.end(), comp);
            joc[joc.size() - 1] -> display();
            joc[0] -> display();
        }
        void timp(int a, float b){
            for(int i=0; i<joc.size(); i++){
                std::cout << joc[i]->get_nume() << ": ";
                joc[i]->get_playtime(a, b);
            }
        }
};

int main(){
    JocVideoHandler gestiune_joc;
    int nr_jocuri, anul, luna, ziua, nr_note, nr;
    std::string nume, tip;
    std::cin >> nr_jocuri;
    //std::cout<< nr_jocuri;
    
    for(int i=0; i<nr_jocuri; i++){
        JocVideo *temp;
        std::cin.ignore();
        getline(std::cin, nume);
        //std::cout << nume << " ";
        std::cin >> ziua >> luna >> anul >> nr_note;
        std::vector <int> note;
        //std::cout << ziua << luna << anul << " " << nr_note << '\n';
        for(int j=0; j<nr_note; j++){
            //std::cout<<nr <<'\n';
            std::cin>>nr;
            //std::cout<< j << " " << nr << '\n';
            note.push_back(nr);
        }
        std::cin >> tip;
        std::cin >> nr;
        
        if(tip == "singleplayer"){
            temp = new JocSinglePlayer(nume, ziua, luna, anul, nr_note, note, nr);
        }
        else{
            temp = new JocMultiPlayer(nume, ziua, luna, anul, nr_note, note, nr);
        }
        
        gestiune_joc.adauga_joc(temp);
    }
    
    int test;
    std::cin >> test;
    switch (test){
        case 1:{ // afisare jocuri: nume - zi luna an - nivele/sesiuni
            gestiune_joc.display();
            break;
        }
        
        case 2:{ // afisare joc cu nota cea mai mare: nume: nota (2 zecimale)
            gestiune_joc.nota_maxima();
            break;
        }
        
        case 3:{ // filtrare data lansare
            std::cin>> ziua >> luna >> anul;
            gestiune_joc.filtrare(ziua, luna, anul);
            break;
        }
        
        case 4:{ // cel mai nou/vechi joc
            gestiune_joc.nou_vechi();
            break;
        }
        
        case 5:{ // caclul timp total
            int a;
            float b;
            std::cin >> a >> b;
            gestiune_joc.timp(a, b);
            break;
        }
    }
}
