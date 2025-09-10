#include <iostream>
#include <vector>
using namespace std;

bool convertibilidad_(int x, int y, vector<int> &v){
    if(x==y){
        //Guardo los x que cumplen la condicion
        v.push_back(x);
        return true;
    }
    else if(x>y){
        return false;
    }
    //Para que y cumpla lo pedido tiene que ser divisble por 2 o que su ultimo digito sea 1 (y%10==1)
    else if(y % 2 == 0 && convertibilidad_(x,y/2, v)){
        v.push_back(y);
        return true;
    }
    else if(y % 10 ==1  && convertibilidad_(x,(y-1)/10, v)){
        v.push_back(y);
        return true;
    }
    return false;
}

void convertibilidad(int x, int y){
    vector<int> v;
    if(convertibilidad_(x,y,v)){
        cout << "YES\n" << v.size()<< "\n";
        //Imprimo asi para que no quede un espacio al final
        for(int i=0; i< v.size()-1; i++){
            cout <<  v[i] << " ";
        }
        cout << v[v.size()-1];
    }
    else{
        cout<< "NO";
    }
}

int main(){
    int x,y;
    cin >> x >>y;
    convertibilidad(x,y);
    return 0;
}

