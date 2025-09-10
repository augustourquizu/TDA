#include <iostream>
#include <unordered_map>
#include <vector>
#include <tuple>
using namespace std;

int frecuencia(int k, vector<int> lista){
    int frec=0;
    for(int n:lista){
        if(k==n){
            frec++;
        }
    }
    return frec;
}

int alegria_carta(int k,int n, const vector<int> &alegria, vector<vector<int>> &dp){
    //Entrego las cartas 1 persona a la vez
    for(int j=0; j<=n; j++){
        //Entrego las cartas 1 por 1 a la persona actual
        for(int i=0; i<=k; i++ ){
            //Entrego las cartas una por una (ignoro caso i=t ya que entrego 0 cartas)
            for(int t=0;t<=i; t++){
                //Busco cuantas cartas me conviene entregarle a la persona j para maximizar la alegria
                dp[i][j]=max(dp[i][j], dp[i-t][j-1]+alegria[t]);
                }   
                }
            }
        //Devuelve la alegria de k cartas favoritas entregadas a n personas
        return dp[k][n];
        }

int alegria_total(int k, const vector<int> &cartas, const vector<int> &favoritos, const vector<int> &alegria, int n){
    //Matriz de k+1xn+1 en la que guardare la alegria de entregar k cartas a n personas
    vector<vector<int>> dp(k+1, vector<int>(n+1,0));
    unordered_map<int,tuple<int,int>> frec;
    int res=0;

    //Anoto cuantas personas tienen una carta favorito y cuantas veces aparece
    for(int fav: favoritos){
        if(!frec.count(fav)){
        frec[fav]= make_tuple(frecuencia(fav, cartas),frecuencia(fav, favoritos));
        }
    }

    //Calculo la alegria por carta por separado y las sumo al total
    //Si una persona no tiene una carta como favorito, da igual si evaluo alegria con esa carta en esa persona
    for (auto i = frec.begin(); i != frec.end(); i++){
        tuple<int,int> par_frecc= i->second;
        int cant_carta= get<0>(par_frecc);
        int cant_fav= get<1>(par_frecc);
        res+=alegria_carta(k, n, alegria, dp);
    }
    return res;
}

void llenar_vector(vector<int> &v, int comienzo=0) {
    for (int i = comienzo; i < v.size(); i++) {
        cin >> v[i];
    }
}

int main(){
    int n,k;
    cin >> n >>k;

    vector<int> cartas(n*k);
    llenar_vector(cartas);

    vector<int> favoritos(n);
    llenar_vector(favoritos);
    
    vector<int> alegria(k+1);
    //Tengo en cuenta alegria base
    alegria[0]=0;
    llenar_vector(alegria,1);
    
    cout << alegria_total(k, cartas, favoritos, alegria, n);   
}
