import sys
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

def agrupar_pesos():
    i=0
    grupos={}
    while i<len(ady):
        p, v, w =ady[i]
        while i<len(ady) and ady[i][0]==p:
            v,w=ady[i][1],ady[i][2]
            grupos.setdefault(p,[]).append((v,w))
            i+=1
    return grupos

def kruskal():
    ady.sort()
    dsu=DSU(n)
    grupos=agrupar_pesos()
    res=0
    for aristas in grupos.values():
        candidatos=[]
        for v,w in aristas:
            raiz_v=dsu.find(v)
            raiz_w=dsu.find(w)
            if raiz_v!=raiz_w:
                candidatos.append((v,w))
        agregados=0
        for v, w in candidatos:
            if dsu.union(v,w):
                #Armo un AGM arbitrario
                agregados+=1
        #Solo tengo que aumentar una vez el peso de una arista para descartarla
        #Elimino aristas hasta que mi AGM arbitrario sea unico
        res+=len(candidatos)-agregados
    return res

print(kruskal())