#include <iostream>
#include <algorithm>
#include <vector>
#include <tuple>
#include <unordered_map>
using namespace std;



long long alfebaticamente(const vector<string>& lista, const vector<long long> &coste){
    long long dp[2];
    int n=lista.size();
    int i=n-1;
    //La posicion uno toma el menor coste de la posicion actual si al string lo dejo como estaba
    dp[0]=0;
    //Menor coste
    dp[1]=coste[i];
    string ultimoRev(lista[i].rbegin(),lista[i].rend());

    //Utilizo enfoque bottom-up para reducir las cuentas repetidas
    for(int i=n-2; i>=0;i--){
        string actual=lista[i];
        string actualRev(actual.rbegin(), actual.rend());

        string siguiente=lista[i+1];
        string siguienteRev(siguiente.rbegin(), siguiente.rend());
        //Guardo lo que despues va a ser los valores de la tabla
        long long dpActual[2]={-1,-1};

        //Actualizo el coste actual
        if(actual<=siguiente || actual<=siguienteRev){
            if (actual<=siguiente && dp[0] != -1 && actual <=siguienteRev && dp[1] != -1)
                // Me quedo con el mas chico
                dpActual[0] =min(dp[0],dp[1]);

            //Si actual<=siguiente, dp[0] se mantiene igual (dp[0] puede ser -1)
            else if (actual <=siguienteRev && dp[1] != -1) dpActual[0]=dp[1];
        }

        if(actualRev<=siguiente || actualRev<=siguienteRev){
            if (actualRev<=siguiente && dp[0] != -1 && actualRev <=siguienteRev && dp[1] != -1)
                // Me quedo con el mas chico y sumo el coste
                dpActual[1] =min(dp[0],dp[1])+coste[i];

            else if (actualRev<=siguiente && dp[0] != -1) dpActual[1]=dp[0] +coste[i];
            else if (actualRev <=siguienteRev && dp[1] != -1) dpActual[1]=dp[1]+coste[i];
        }

        //Actualizo el coste
        dp[0]=dpActual[0];
        dp[1]=dpActual[1];
        }
        if(dp[0]!=-1 && dp[1]!=-1) return min(dp[0],dp[1]);
        //Si un valor de dp es -1, me quedo con el otro que va a ser mayor o igual a -1
        return max(dp[0],dp[1]);
    }

int main(){
    int n;
    cin >> n;

    int i=0;
    vector<long long> coste(n);
    while(i<n){
        long long costo;
        cin >> costo;
        coste[i]=costo;
        i++;
    }
    i=0;
    vector<string> lista(n);
    while(i<n){
        string palabra;
        cin >> palabra;
        lista[i]=palabra;
        i++;
    }
    cout << alfebaticamente(lista, coste);
    return 0;
}