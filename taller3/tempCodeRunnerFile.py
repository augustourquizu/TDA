def generar_grafo():
    n,m=map(int, input().split())
    ady = []
    for _ in range(m):
        a, b, c = map(int, input().split())
        ady.append((c, a-1,b-1))
    return ady,n

ady, n=generar_grafo()