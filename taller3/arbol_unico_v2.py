import sys
from collections import deque
input=sys.stdin.readline

class DSU:
    def __init__(self,n):
        self.parent=list(range(n))
        self.copia_pre=list(range(n))
        self.rank=[0]*n 
        self.copia_rank=[0]*n 
        #Nodos unidos anteriormente
        self.anterior=None
        
    
    def find(self,v,pre=False):
        if pre:
            if self.copia_pre[v] != v:
                self.copia_pre[v] = self.find(self.copia_pre[v],pre=True) 
            return self.copia_pre[v]        
        else:
            if self.parent[v] != v:
                self.parent[v] = self.find(self.parent[v]) 
            return self.parent[v]
    
    def hay_ciclo(self, v, w,pre=False):
        if pre:
            #Como viene de union ya esta actualizado
            return self.copia_pre[v]==self.copia_pre[w]
        
        raiz_v=self.find(v)
        raiz_w=self.find(w)
        if raiz_v==raiz_w:
            #Hay ciclo porque estan en el mismo set (mismo padre)
            return True 
        return False
    
    def union(self, v,w):
        
            
        raiz_v=self.find(v)
        raiz_w=self.find(w)
        
        if raiz_v==raiz_w:
            return False
        
        if self.anterior is not None:
            x,y=self.anterior
            raiz_x=self.find(x,pre=True)
            raiz_y=self.find(y,pre=True)
                
            if self.copia_rank[raiz_x]<self.copia_rank[raiz_y]:
                self.copia_pre[raiz_x]=raiz_y
                
            elif self.rank[raiz_x]>self.rank[raiz_y]:
                self.copia_pre[raiz_y]=raiz_x
            else:
                self.copia_pre[raiz_y]=raiz_x
                self.copia_rank[raiz_x]+=1
        
        if self.rank[raiz_v]<self.rank[raiz_w]:
            self.parent[raiz_v]=raiz_w
            self.anterior=(v,w)
            
        elif self.rank[raiz_v]>self.rank[raiz_w]:
            self.parent[raiz_w]=raiz_v
            self.anterior=(v,w)
        else:
            self.parent[raiz_w]=raiz_v
            self.rank[raiz_v]+=1
            self.anterior=(v,w)
        return True

def generar_grafo():
    n,m=map(int, input().split())
    ady = []
    for _ in range(m):
        a, b, c = map(int, input().split())
        ady.append((c, a-1,b-1))
    return ady,n


def kruskal():
    ady, n = generar_grafo()
    ady.sort()
    AGM=[]
    dsu=DSU(n)
    res=0
    p_act=0
    while ady:
        p,v,w=ady.popleft()
        #Ya analice los pesos menores y veo que pasa con un peso mayor
        if p>p_act:
            p_act=p
            #Aumento en uno el peso de las aristas que crean bifurcaciones y despues veo que onda
            for elem in range:
                
        if dsu.union(v,w):
            j=0
            while j<len(ady) and ady[j][0]<=p_act:
                x,y,z=ady[j]
                #Si el peso es <= veo que pasa. Si es igual, puede generar bifurcacion. Si es menor, 
                # puede disminuir el peso En ambos casos les aumento el peso y veo que onda
                if not dsu.hay_ciclo(y,z,pre=True) and dsu.hay_ciclo(y,z):
                    aumentados.append(ady[j])
                    res+=1
                j+=1
    return res
        
print(kruskal())