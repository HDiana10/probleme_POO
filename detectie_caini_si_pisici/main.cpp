#include <iostream>
#include <string>
#include <iomanip>
///#include <cmath> 
class Caseta{
    private:
        int x1, y1, x2, y2;
        std::string eticheta;

    public:
       void set(int x1, int x2, int y1, int y2, std::string eticheta){
           this->x1 = x1;
           this->y1 = y1;
           this->x2 = x2;
           this->y2 = y2;
           this->eticheta = eticheta;
       }
       
       void display(){
           std::cout<< this->x1 << " " << this->x2 << " ";
           std::cout<< this->y1 << " " << this->y2 << "\n";
           std::cout<< this->eticheta << "\n";
       }
       
       std::string get_eticheta(){return this->eticheta;}
       
       float IoU(Caseta c){
           float cx1, cx2, cy1, cy2, a1, a2, a3;
           cx1 = std::max(this->x1, c.x1);
           cx2 = std::min(this->x2, c.x2);
           cy1 = std::max(this->y1, c.y1);
           cy2 = std::min(this->y2, c.y2);
           a1 = 1.0 * (this->x2 - this ->x1 + 1) * (this->y2 - this->y1 + 1);
           a2 = 1.0 * (c.x2 - c.x1 + 1) * (c.y2 - c.y1 + 1);
           a3 = 1.0 * (cx2 - cx1 + 1) * (cy2 - cy1 + 1);
           //std::cout<< a1 << " " << a2 << " " << a3 << '\n';
           return a3 / (a1 + a2 - a3);
       }
       
};


int main()
{
    int n, test, temp_x1, temp_y1, temp_x2, temp_y2;
    std::string temp_eticheta;
    float prag, iou;
    
    std::cin>>n;
    Caseta c[n], c2;
    
    for(int i=0; i<n; i++){
        std::cin>> temp_x1 >> temp_x2 >> temp_y1 >> temp_y2 >> temp_eticheta;
            c[i].set(temp_x1, temp_x2, temp_y1, temp_y2, temp_eticheta);
    }
    
    std::cin>>test;
    
    switch(test){
        case 1:
            for(int i=0; i<n; i++)
                c[i].display();
            break;
        
        case 2:
            std::cin>> temp_x1 >> temp_x2 >> temp_y1 >> temp_y2 >> temp_eticheta;
            c2.set(temp_x1, temp_x2, temp_y1, temp_y2, temp_eticheta);
            std::cout << std::fixed << std::setprecision(4) << c[0].IoU(c2);
            break;
        
        case 3:
            std::cin>> temp_x1 >> temp_x2 >> temp_y1 >> temp_y2 >> temp_eticheta;
            c2.set(temp_x1, temp_x2, temp_y1, temp_y2, temp_eticheta);
            std::cin>>prag;
            iou = c[0].IoU(c2);
            if(iou > prag && c2.get_eticheta() == c[0].get_eticheta())
                std::cout<< "1";
            else
                std::cout<< "0";
            break;
        
        case 4:{
            int m, tp = 0, fp = 0;
            std::cin>>m;
            Caseta c1[m];
            
            for(int i=0; i<m; i++){
                std::cin>> temp_x1 >> temp_x2 >> temp_y1 >> temp_y2 >> temp_eticheta;
                    c1[i].set(temp_x1, temp_x2, temp_y1, temp_y2, temp_eticheta);
            }
            std::cin>>prag;
            
            for(int i=0; i<n && i<m; i++){
                iou = c[i].IoU(c1[i]);
                if(iou > prag && c1[i].get_eticheta() == c[i].get_eticheta())
                    tp++;
                else
                    fp++;
            }
            
            std::cout << std::fixed << std::setprecision(4) << 1.0 * tp / (fp + tp);
            break;
        }
    }
}
