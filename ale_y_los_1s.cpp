#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int contar_ale_1s(int n, vector<int> &v){
    int contador=0;
    int i=1;
    int niveles=log2(n)+1;
    if(v[0]==1){
        contador+=1;
    }
    while(i<niveles){
        if(v[i]==1){
            contador=contador*2+1;
        }
        else{contador*=2;}
        i+=1;
    }
    return contador;
}

vector<int> ale_y_los_1s_(int n){
    if(n==1 || n==0){ 
        return {n};
    }
    vector<int> mitad= ale_y_los_1s_(n/2);
    vector<int> res;
    //Si divido el problea en dos partes, izquierda de n mod 2 y derecha, me daran las dos partes iguales.
    //Asi que calculo solo una parte
    res.insert(res.begin(),mitad.begin(), mitad.end());
    res.push_back(n % 2);
    return res;
}

int ale_y_los_1s(int n){
    vector<int> res=ale_y_los_1s_(n);
    return contar_ale_1s(n,res);
}

int main(){
    cout << ale_y_los_1s(500);
    return 0;
}
