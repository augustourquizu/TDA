#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;


long long contarHasta(long long n, long long l);

long long ale_y_los_1s(long long n, long long l, long long s){
    //[l:s]=[1:s] - [1:l-1]
    long long res= contarHasta(n,s) - contarHasta(n,l-1);
    return res ;
}

//Guarda las los largos de ale(n) para no repetir cuentas
unordered_map<long long,long long> guardar;

//Halla largo de la secuencia de ale
long long largo(long long n){
    if(n == 0 || n==1) return 1;
    if(guardar.find(n)!=guardar.end()) return guardar[n];
    //La secuencia de ale se puede es una recurrencia en donde cada nivel es de la forma |n/2| n mod 2 |n/2|. 
    //Al hacer esto duplico la longitud de la secuencia y le sumo uno (el centro) 
    guardar[n]= 2*(largo(n/2))+1;
    return guardar[n];
}

long long contarHasta(long long n, long long l){
    if(n==0) return 0;
    //En contarAle, puede quedar contarHasta(1,0) por lo que que tengo en cuenta aca 
    if(n==1) return l;
    long long centro=largo(n/2)+1;

    if(l<centro)  return contarHasta(n/2,l);

    //La secuencia es de la forma ale(n/2) n mod 2 ale(n/2). Si l=centro,  la cantidad de son ale(n/2) + n mod 2
    //Propongo ale(n)=n. Explico con induccion: 
    //Veo caso base: Si n=1, ale(1)=1. 
    //Supongo que ale(n)=n. Entonces veo n+1 -> Si n+1 es impar, entonces la recurrencia queda ale(n/2) n+1 mod 2 
    //ale(n/2). Por induccion ale(n/2)=n/2. Entonces ale(n+1)= n/2*2 +n+1 mod 2 (n impar)= n+1. Si n+1 es par 
    //entonces ale(n+1)=(n+1)/2*2+n mod 2=n+1. Vale la hipotesis inductiva

    else if(l==centro) return n/2 + n % 2;

    else if (l>centro) return n/2+ n % 2+ contarHasta(n/2, l-centro);

    return 0;
}



int main(){
    long long n, l ,s;
    cin >> n >> l >> s;
    cout << ale_y_los_1s(n,l,s);
    return 0;
}