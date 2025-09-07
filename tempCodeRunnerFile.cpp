#include <iostream>
#include <unordered_map>
using namespace std;

int borrar(string s, int n){
    //memo que guarda un caracter y el caracter que aparece despues de este en el string
    unordered_map <char, char> memo;
    int i=0;
    int res=0;
    while(i<n-1){
        char actual=s[i];
        char siguiente=s[i+1];

        memo[actual]=siguiente;
        //Para tener menos borrados tengo que borrar caracteres que se encuentran entre un mismo caracter
        // Ej: azza(z se encuentra entre a asi que lo elimino)
        if(actual!=siguiente && memo.count(siguiente) ){

            //Elimino de memo los caracteres que estan entre en medio de un caracter y actualizo el res
            //Ej : azbca(zbc entre a asi que los elimino de memo)
            char eliminar=memo[siguiente];
            while(eliminar!=siguiente){
                res++;
                char siguiente_eliminado=memo[eliminar];
                memo.erase(eliminar);
                eliminar=siguiente_eliminado;
            }
        }
        i++;
    }
    char actual=s[i];

    //Si el ultimo caracter actual esta en memo, sera eliminado en cadena cuando elimine a los otros iguales
    //Ej: abzaa (el ultimo a se elimina cuando elimino los otros a)
    if(!memo.count(actual)){
        return res+= memo.size()+1;
    }
    return res+= memo.size();
}

int main(){
    int n;
    string s;
    cin >> n >> s;
    cout << borrar(s,n);
}