import heapq
from collections import defaultdict
import sys
input=sys.stdin.readline
bosque=set()
def generar_grafo():
    n,m=map(int, input().split())
    ady = [[] for _ in range(n)]
    for _ in range(m):
        a, b, c = map(int, input().split())
        ady[a-1].append((b-1, c))
        ady[b-1].append((a-1, c))
    return ady,n

ady, n=generar_grafo()

def bosque_prim(visto, h, arbol=set(), iguales=[]):
    while h:
        p,v,m=heapq.heappop(h)
        if h and h[0][0]==p:
            #Al parecer copiar por slicing que por copy es mas rapido
            bosque_prim(visto[:],h[:],arbol.copy(), iguales+[(p,v,m)])
            
        for x in iguales:
            heapq.heappush(h,x)
        iguales.clear()
        
        if visto[m] and visto[v]:
            continue
        
        if not visto[m]:
            nuevo=m
        else: nuevo=v 
        
        visto[nuevo]=True
        #Expreso las aristas como (n,m) con n<m.
        arbol.add(tuple(sorted((v,m))))
        for w,peso in ady[nuevo]:
            heapq.heappush(h,(peso,w, nuevo))
            
    bosque.add(frozenset(arbol))
  
#Genero la primera vecindad antes de aplicar Prim (queda feo asi pero es mas comodo)
h=[]    
for v,p in ady[0]:
    #peso, origen,destino
    heapq.heappush(h,(p,0,v))
visto=[False]*n
visto[0]=True

bosque_prim(visto, h)

def descarte(bosque):
    res=0
    contador=defaultdict(int)
    bosque = list(bosque)
    #Si elimino un arbol, marco como false en ver para eliminar
    ver_bosque = [True] * len(bosque)
    #Si elimino una arista, marco como false en ver para eliminar
    activos = len(bosque)
    for arbol in bosque: 
        for m in arbol:
            #Cuento las aristas y las agrego al diccionario a la vez
            contador[m]+= 1
             
    while activos>1:
        
        if not contador:
            break 
        
        mayor=0
        arista_mayor=None
        for v, cant in contador.items():
            if cant>0 and activos>cant>mayor:
                mayor=cant
                arista_mayor=v
        
            
        if mayor==1:
            res+=activos-1
            break
        
        activos-=mayor
        
        if arista_mayor is None:
            # No hay más aristas útiles
            break
        
        for i, arbol in enumerate(bosque):
            if ver_bosque[i] and arista_mayor in arbol:
                ver_bosque[i] = False 
                for m in arbol:
                    contador[m] -= 1
        res+=1
        
    return res
print(descarte(bosque))