import heapq
import sys
input=sys.stdin.readline

def hacer_grafo():    
    n,m=map(int, input().split())
    demora=[]
    ady = [[] for _ in range(n)]
    for _ in range(m):
        a, b, c = map(int, input().split())
        ady[a-1].append((b-1, c))
        ady[b-1].append((a-1, c))
        
    for _ in range(n):
        #Me molesta que diga la cantidad de momentos de demora
        tiempos=list(map(int, input().split()[1:]))
        #No me pasa el tiempo asi que aprovecho que tengo memoria de sobra
        demora_dict={}
        
        if tiempos:
            demora_dict[tiempos[-1]] = 1
            for i in range(len(tiempos) - 2, -1, -1):
                if tiempos[i+1] == tiempos[i] + 1:
                    demora_dict[tiempos[i]] = demora_dict[tiempos[i+1]] + 1
                else:
                    demora_dict[tiempos[i]] = 1
            
        demora.append(demora_dict)
    return demora, ady, n


def dijkstra(demora,ady, n):
    #res es una lista de tiempos minimos para llegar a un planeta desde el punto de partida
    res=[float("inf")]*n
    res[0]=0#heap de la forma (peso_camino, nodo)
    h=[(0,0)]
    
    while h:
        tiempo, nodo=heapq.heappop(h)
        #En el heap pueden aparecer distintos caminos a un nodo y me aseguro de tomar el mas corto
        if tiempo==res[nodo]:
            #m es la arista que es una tupla de la forma (hasta, peso)
            for m in ady[nodo]:
                v,p=m
                #Tomo el tiempo con la demora
                if tiempo in demora[nodo]:
                    tiempo_demora=demora[nodo][tiempo]+tiempo
                else: tiempo_demora=tiempo 
                     
                if tiempo_demora+p<res[v]:
                    res[v]=tiempo_demora+p
                    heapq.heappush(h,(tiempo_demora+p,v))
                
    if res[n-1]!=float('inf'): return res[n-1]
    else: return -1
    
        
demora,ady, n=hacer_grafo()
print(dijkstra(demora,ady,n))