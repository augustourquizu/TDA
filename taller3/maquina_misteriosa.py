from collections import deque

n, m = map(int, input().split())

def maquina_misteriosa(n,m):
    if n>=m: return n-m
    pasos=0
    #n ya fue "visto" en n>=m
    visto = {n}
    ady={}
    pasos = {n:0}
    q=deque()
    q.append(n)
    #BFS con pequenias modificacion
    while len(q)>0:
        n=q.popleft()
        #Creo el grafo mientras se ejecuta el while
        if n<m: ady[n]={n-1,n*2}
        else: ady[n]={n-1}
        
        for v in ady[n]:
            if not v in visto:
                visto.add(v)
                pasos[v]=pasos[n]+1
                if v==m: return pasos[m]
                q.append(v)

    
print(maquina_misteriosa(n,m))