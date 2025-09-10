#include <iostream>
#include <algorithm>
using namespace std;


int contar(char l, string s){
    int contador=0;
    for(char c: s){
        if(c==l){
            contador++;
        }
    }
    return contador;
}


int l_lindo(char l,  const string &s, int n){
    if(n==1){
        if(l==s[0]){
            return 0;
        }
        else{ 
            return 1;
        }
    }
    int mitad=n/2;
    //Puntaje representa la cantidad de letras que hay que cambiar en el string para pasarlo a l-lindo.
    // Cuento las letras correctas en la mitad izquierda y le resto su largo para tener la cantidad 
    //de letras incorrectas, hago lo mismo con la mitad derecha.
    int puntaje1= mitad - contar(l, s.substr(0,mitad))+l_lindo(l+1,s.substr(mitad), mitad);
    int puntaje2= mitad - contar(l, s.substr(mitad)) +l_lindo(l+1,s.substr(0,mitad), mitad);

    //Selecciono el puntaje con mas letras correctas y se lo resto a n
    return min(puntaje1,puntaje2) ;
}

int main(){
    int t;
    cin >> t;
    while(t>0){
        int n;
        string s;
        cin >> n >> s;
        cout << l_lindo('a', s, n) << "\n";
        t--;
    }
    return 0;
}