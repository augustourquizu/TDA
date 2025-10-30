import sys
from collections import defaultdict
input=sys.stdin.readline

class DSU:
    def __init__(self,n):
        self.parent=list(range(n))
        self.rank=[0]*n 
        
    
    def find(self,v):
        while self.parent[v] != v:
            self.parent[v] = self.parent[self.parent[v]]
            v=self.parent[v] 
        return v
    
    def se_pueden_unir(self, v, w):
        raiz_v=self.find(v)
        raiz_w=self.find(w)
        
        return raiz_v!=raiz_w
    
    def union(self, v,w):
        
        raiz_v=self.find(v)
        raiz_w=self.find(w)
        
        if raiz_v==raiz_w:
            return False
        
        if self.rank[raiz_v]<self.rank[raiz_w]:
            self.parent[raiz_v]=raiz_w
            
        elif self.rank[raiz_v]>self.rank[raiz_w]:
            self.parent[raiz_w]=raiz_v
        else:
            self.parent[raiz_w]=raiz_v
            self.rank[raiz_v]+=1
        return True

def generar_grafo():
    n,m=map(int, input().split())
    ady = []
    for _ in range(m):
        a, b, c = map(int, input().split())
        ady.append((c, a-1,b-1))
    return ady,n

ady,n = generar_grafo()

def kruskal():
    ady.sort()
    dsu=DSU(n)
    #Agrupo las aristas por pesos y agrupo las aristas por pesos en un mismo AGM arbitrario
    agm_original_pesos={}
    agrupar_pesos=defaultdict(list)
    #Los pesos de las aristas en el AGM
    pesos_agm=set()
    for p,v,w in ady:
        if dsu.union(v,w):
            agm_original_pesos.setdefault(p, []).append((v, w))
            pesos_agm.add(p)
        else:
            if p in pesos_agm:
                agrupar_pesos[p].append((v,w))
    
    return agm_original_pesos, agrupar_pesos

def agregar_pesos():
    agm_original_pesos, agrupar_pesos=kruskal()
    dsu=DSU(n)
    res=0
    #Prueba a anadir cada arista y ver si genera un AGM
    for p, m in agrupar_pesos.items():
        #Evaluo si hubiese podido agregar otras aristas de las que agrege en el AGM original
        for v,w in m:
            if dsu.se_pueden_unir(v,w):
                res+=1
        for v,w in agm_original_pesos[p]:
            dsu.union(v,w) 
    return res
    
        
print(agregar_pesos())