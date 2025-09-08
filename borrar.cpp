#include <iostream>
#include <vector>
using namespace std;

int borrar(const string &s, int n, vector<vector<int>> &dp){
    //Si el substring es de largo 1, necesito solo una eliminacion
    for(int i=0; i<n; i++) dp[i][i]=1;
    //Lleno una tabla que posea las eliminaciones necesarias para cada substring con longitud l
    for(int l=2; l<=n; l++){
    int i=0;
        //Lleno dp con las eliminaciones necesarias para eliminar los substring s[i:j] 
        for(int j=l-1; j<n; j++){
            dp[i][j]= dp[i][j-1]+1;

            //Exploro intervalo s[i:j] y veo si puedo juntar caracteres para reducir las eliminaciones
            for(int k=i; k<j; k++){
                if(s[j]==s[k]){
                    if(k+1<=j-1){
                    //Tomo minimo de que si busco juntar los caracteres entre k y j o no y tomo el mejor caso
                    dp[i][j]=min(dp[i][j], dp[i][k]+dp[k+1][j-1]); 
                    }
                    else dp[i][j]=dp[i][k]; //j se elimina junto a k
                }
            }
            i++;
        }
}
    return dp[0][n-1];
}

int main(){
    int n;
    string s;
    cin >> n >> s;
    vector<vector<int>> dp(n, vector<int>(n, 0));
    cout << borrar(s,n, dp);
    return 0;
}
