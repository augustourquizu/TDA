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

int alegria_carta(int k,int n, vector<int> alegria, vector<vector<int>> dp){
    //Entrego las cartas 1 persona a la vez
    for(int j=0; j<=n; j++){
        //Entrego las cartas 1 por 1 a la persona actual
        for(int i=0; i<=k; i++ ){
            //Entrego las cartas una por una (ignoro caso i=t ya que entrego 0 cartas)
            for(int t;t<=i; t++){
                //Busco cuantas cartas me conviene entregarle a la persona j para maximizar la alegria
                dp[i][j]=max(dp[i][j], dp[i-t][j-1]+alegria[t]);
                }   
                }
            }
        //Devuelve la alegria de k cartas favoritas entregadas a n personas
        return dp[k][n];
        }

int alegria_total(int k, vector<int> cartas, vector<int> favoritos, vector<int> alegria, int n){
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
        int k= get<0>(par_frecc);
        int n= get<1>(par_frecc);
        res+=alegria_carta(k, n, alegria, dp);
    }
}

vector<int> crear_vector(int n) {
    vector<int> v(n+1);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }
    return v;
}

int main(){
    int n,k;
    cin >> n >>k;
    vector<int> cartas=crear_vector(n*k);
    vector<int> favoritos= crear_vector(n);
    vector<int> alegria= crear_vector(k);
    //h0=0
    alegria.insert(alegria.begin(),0);

    cout << alegria_total(k, cartas, favoritos, alegria, n);   
}
