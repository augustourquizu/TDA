def hacer_grafo():    
    n,m=map(int, input().split())
    demora=[]
    ady=[]
    for _ in range(m):
        a, b, c = map(int, input().split())
        #Me molesta que los vertices empiecen con indice 1. Las tuplas son de la forma (desde,hasta,peso)
        ady.append((a-1,b-1,c))
        ady.append((b-1,a-1,c))
    for _ in range(n):
        #Me molesta que diga la cantidad de momentos de demora
        lista=list(map(lambda x: int(x),input().split()))
        demora.append(set(lista[1:]))
    return demora, ady, n


def ford(demora,ady, n):
    #res es una lista de tiempos minimos para llegar a un planeta desde el punto de partida
    res=[float("inf")]*n
    res[0]=0
    #Es para evaluar si los tiempos dejaron de cambiar para cortar el algortimo Ford
    cambio=True
    while cambio:
        cambio=False
        for m in ady:
            #Me pregunto cuanto tardo en llegar al planeta donde estoy parado
            tiempo_act=res[m[0]] 
            
            #Veo cuanto hay de espera
            while tiempo_act in demora[m[0]]:
                tiempo_act+=1
                
            #Veo si me conviene llegar a otro planeta por un camino distitno
            if m[2]+tiempo_act<res[m[1]]:
                res[m[1]]=m[2]+tiempo_act
                cambio=True
                
    if res[n-1]!=float('inf'): return res[n-1]
    else: return -1
        
demora,ady, n=hacer_grafo()
print(ford(demora,ady,n))
