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

    if(dp[k][n]==0){

        //Entrego las cartas 1 persona a la vez
        for(int j=1; j<=n; j++){

            if(dp[k][j]==0){

                //Entrego las cartas 1 por 1
                for(int i=1; i<=k; i++ ){

                    //Entrego las cartas una por una a la persona j
                    for(int t=0;t<=i && t<alegria.size(); t++){

                        //Busco cuantas cartas me conviene entregarle a la persona j para maximizar la alegria
                        dp[i][j]=max(dp[i][j], dp[i-t][j-1]+alegria[t]);
                        }   
                    }
                }
            }
        }
        //Devuelve la alegria de k cartas favoritas entregadas a n personas
        return dp[k][n];
        }

int alegria_total(int k, const vector<int> &cartas, const vector<int> &favoritos, const vector<int> &alegria, int n){
    //Guarda cuantas veces aparecen las cartas favoritos en el mazo y en la lista de favoritos
    unordered_map<int,tuple<int,int>> frec;
    int res=0;
    //Cuento la carta que mas veces aparece y la que mas querida es para armar el dp
    int max_carta=0;
    int max_fav=0;

    //Anoto cuantas personas tienen una carta favorito y cuantas veces aparece
    for(int fav: favoritos){
        if(!frec.count(fav)){
            int frec_carta_total=frecuencia(fav, cartas);
            max_carta=max(frec_carta_total,max_carta);

            int frec_carta_fav=frecuencia(fav,favoritos);
            max_fav=max(max_fav, frec_carta_fav);
            
            frec[fav]= make_tuple(frec_carta_total,frec_carta_fav);
            }
    }

    vector<vector<int>> dp(max_carta+1, vector<int>(max_fav+1,0));

    //Calculo la alegria por carta por separado y las sumo al total
    for (auto i = frec.begin(); i != frec.end(); i++){
        tuple<int,int> par_frecc= i->second;
        int cant_carta= get<0>(par_frecc);
        int cant_fav= get<1>(par_frecc);
        res+=alegria_carta(cant_carta, cant_fav, alegria, dp);
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
