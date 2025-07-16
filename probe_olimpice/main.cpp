#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cmath>
#include <iomanip>

class MathFunction{
    protected:
        std::string function_name;
    public:
        std::string get_function_name(){ return function_name; }
        virtual float get_value(int x){}
        float get_max_value(int x, int y){
            float max_val = get_value(x);
            for(int i = x+1; i <= y; i++){
                float val = get_value(i);
                if(val > max_val)
                    max_val = val;
            }
            return max_val;
        }
        MathFunction(std::string nume): function_name(nume) {}
        virtual void display() = 0;
};

class Polynomial: public MathFunction{
    protected:
        std::vector <float> coefficients;
    public:
        Polynomial(std::string nume, std::vector <float> coefficients): MathFunction(nume), coefficients(coefficients) {}
        void display(){
            std::cout <<  function_name << "\nf(x) =";
            if(coefficients[0]!=0 || coefficients.size() == 1) std::cout << " " << coefficients[0];
            for(int i=1; i< coefficients.size(); i++)
                if(coefficients[i]>0){
                    std::cout << " + ";
                    if(coefficients[i] != -1){std::cout << coefficients[i];}
                    std::cout << "x";
                        if(i>1) std::cout << "^" << i;
                }
                else if(coefficients[i] < 0){
                    std::cout << " - ";
                    if(coefficients[i] != -1){std::cout << coefficients[i];}
                    std::cout << "x";
                        if(i>1) std::cout << "^" << i;
                }
            std::cout<<"\n";
        }
        float get_value(int x){
            float val = 0;
            for(int i = 0; i<coefficients.size(); i++){
                val += coefficients[i] * pow(x, i);
            }
            return val;
        }
};

class Quadratic: public Polynomial{
    public:
        Quadratic(std::string nume, std::vector <float> coefficients): Polynomial(nume, coefficients) {}
        void print_roots(){
            float x1, x2, delta;
            delta = coefficients[1] * coefficients[1] - 4 * coefficients[0] * coefficients[2];
            if(delta == 0){
                x1 = (- coefficients[1] + sqrt(delta)) / ( 2 * coefficients[2]);
                std::cout << "X1 = X2 = " << std::fixed << std::setprecision(2) << x1 << '\n';
            }
            else{
                x1 = (- coefficients[1] + sqrt(delta)) / ( 2 * coefficients[2]);
                x2 = (- coefficients[1] - sqrt(delta)) / ( 2 * coefficients[2]);
                std::cout << "X1 = " << std::fixed << std::setprecision(2) <<x1 << '\n';
                std::cout << "X2 = " << std::fixed << std::setprecision(2) <<x2 << '\n';
            }
        }
};

class Exponential: public MathFunction{
    private:
        const float e = 2.71;
        float constant, exp_coef;
    public:
        Exponential(std::string nume, float constant, float exp_coef): MathFunction(nume), constant(constant), exp_coef(exp_coef) {}
        void display(){
            std::cout << function_name << "\nf(x) = ";
            if(constant !=0){
                std::cout<< constant << " ";
            }
            if(exp_coef > 0){
                if(exp_coef == 1) std::cout<< "+ e^x";
                else std::cout<< "+ "<< exp_coef << "e^x";
            }
            else if(exp_coef < 0){
                if(exp_coef == 1) std::cout<< "- e^x";
                else std::cout<< "- "<< exp_coef << "e^x";
            }
            else if(constant == 0) std::cout <<"0";\
            std::cout<<"\n";
        }
        float get_value(int x){
            float val;
            val = constant + exp_coef * pow(e, x);
            return val;
        }
};


std::vector <MathFunction*> functie;

class DiscreteFunction: public MathFunction{
    private:
        std::vector <float> x_values, y_values;
    public:
        virtual float get_value(int x){}
        virtual void display(){}
        DiscreteFunction(std::vector <float> x_values, std::vector <float> y_values): MathFunction("DiscreteFunction"), x_values(x_values), y_values(y_values) {}
        std::string find_best_approximation(){
            float delta_min=-1, delta, ans;
            for(int i=0; i<functie.size(); i++){
                delta = 0;
                for(int j=0; j<x_values.size(); j++)
                    delta += abs(functie[i]->get_value(x_values[i]) - y_values[i]);
                if(delta_min == -1 || delta < delta_min)
                    delta_min = delta, poz = i;
            }
            
            std::string answer = "f(x) =";
            for(int i=0; i<functie.size(); i++){
                if(val>0){
                    answer += " +";
                    if(val != -1){answer += to_string(val);}
                    std::cout << "x";
                        if(i>1) std::cout << "^" << i;
                }
                else if(val < 0){
                    std::cout << " - ";
                    if(coefficients[i] != -1){std::cout << coefficients[i];}
                    std::cout << "x";
                        if(i>1) std::cout << "^" << i;
            }
        }
    }
};


int main(){
    int nr_functii;
    std::cin>>nr_functii;
    
    for(int i=0; i<nr_functii; i++){
        int nr_termeni;
        std::string nume;
        std::cin >> nume;
        MathFunction *fct = nullptr;
        if(nume == "Polynomial"){
            std::cin >> nr_termeni;
            float coeficient;
            std::vector <float> coeficienti;
            for(int i = 0; i<nr_termeni; i++){
                std::cin>>coeficient;
                coeficienti.push_back(coeficient);
            }
            fct = new Polynomial(nume, coeficienti);
        }
        
        else if(nume == "Quadratic"){
            nr_termeni = 3;
            float coeficient;
            std::vector <float> coeficienti;
            for(int i = 0; i<nr_termeni; i++){
                std::cin>>coeficient;
                coeficienti.push_back(coeficient);
            }
            fct = new Quadratic(nume, coeficienti);
        }
        else{
            float constanta, exponent;
            std::cin >> constanta >> exponent;
            fct = new Exponential(nume, constanta, exponent);
        }
        functie.push_back(fct);
    }
    int test;
    std::cin >> test;
    
    switch(test){
        case 1:{ // afisare
            for(int i=0; i<functie.size(); i++)
                functie[i]->display();
            break;
        }
        case 2:{
            for(int i=0; i < functie.size(); i++)
                if(functie[i]->get_function_name() == "Quadratic"){
                    Quadratic *quad = dynamic_cast<Quadratic*>(functie[i]);
                    quad -> print_roots();
                }
            break;
        }
        case 3:{
            int a, b;
            std::cin >> a >> b;
            for(int i=0; i < functie.size(); i++)
                std::cout << std::fixed << std::setprecision(2) << functie[i]->get_max_value(a, b) << '\n';
            break;
        }
        case 4:{
            std::vector <float> x_values, y_values;
            float x, y;
            for(int i=0; i<3; i++){
                std::cin >> x;
                x_values.push_back(x);
            }
            for(int i=0; i<3; i++){
                std::cin >> y;
                y_values.push_back(y);
            }
            functie.push_back(new DiscreteFunction(x_values, y_values));
            DiscreteFunction *disc = dynamic_cast<DiscreteFunction*>(functie[functie.size()-1]);
            std::cout<< disc -> find_best_approximation();
            break;
        }
    }
}
