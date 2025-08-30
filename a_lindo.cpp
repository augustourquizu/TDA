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


int l_lindo(char l, string s){
    int n = s.length();

    if(n==1){
        if(l==s[0]){
            return 0;
        }
        else{ 
            return 1;
        }
    }
    
    //Puntaje representa la cantidad de letras que hay que cambiar en el string para pasarlo a l-lindo.
    // Cuento las letras correctas en la mitad izquierda y le resto su largo para tener la cantidad 
    //de letras incorrectas, hago lo mismo con la mitad derecha.
    int puntaje1= n/2 - contar(l, s.substr(0,n/2))+l_lindo(l+1,s.substr(n/2));
    int puntaje2= n/2 - contar(l, s.substr(n/2)) +l_lindo(l+1,s.substr(0,n/2));

    //Selecciono el puntaje con mas letras correctas y se lo resto a n
    return min(puntaje1,puntaje2) ;
}

int main(){
    cout << "Obtenido:" << l_lindo('a', "aaaadcbb") << "| Esperado: 0\n" ;
    cout << "Obtenido:" << l_lindo('a', "bbaaceaa") << ". Esperado: 4\n" ;
    cout << "Obtenido:" << l_lindo('a', "jkghasdf") << ". Esperado: 7\n" ;
    cout << "Obtenido:" << l_lindo('a', "x") << ". Esperado: 1\n" ;
    cout << "Obtenido:" << l_lindo('a', "ccddaabb") << ". Esperado: 5\n" ;
    return 0;
}