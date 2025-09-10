import numpy as np

def norma(x,p):
    x = np.array(x)
    i=0
    suma=0

    while(i<len(x)):
        if(p=="inf"):
            suma=max(suma,abs(x[i]))
        else: 
            suma+=abs(x[i])**p
        i+=1
    if(p=="inf"): 
        return suma
    
    return suma**(1/p)

def normaliza(X,p):
    res=[]
    for element in X:
        res.append(element/norma(element, p))
    return res

def normaMatMC(A, q , p , Np) :
    columnas=A.shape[1]
    X=np.random.rand(Np,columnas)
    X=normaliza(X,p)
    res=0
    vector_max=X[0]
    for element in X:
        norma_actual=norma(A@(element.T),q)
        if(res<=norma_actual):
            res=norma_actual
            vector_max=element
    return (res, vector_max)
    



# Primer assert: Compara norma de [1, 1] con sqrt(2)
assert np.allclose(norma(np.array([1, 1]), 2), np.sqrt(2))

# Segundo assert: Compara norma de un vector de 10 unos con sqrt(10)
assert np.allclose(norma(np.array([1] * 10), 2), np.sqrt(10))

# Tercer assert: La norma de un vector aleatorio no debe exceder sqrt(10)
assert norma(np.random.rand(10), 2) <= np.sqrt(10)

# Cuarto assert: La norma de un vector aleatorio siempre debe ser >= 0
assert norma(np.random.rand(10), 2) >= 0

assert [np.allclose(norma(x, 2), 1) for x in normaliza([np.array([1] * k) for k in range(1, 11)], 2)]

assert [not np.allclose(norma(x, 2), 1) for x in normaliza([np.array([1] * k) for k in range(1, 11)], 1)]

assert [np.allclose(norma(x, np.inf), 1) for x in normaliza([np.random.rand(k) for k in range(1, 11)], "inf")]

# Primer set de asserts: utilizando norma L2 y L1 con una matriz identidad
nMC = normaMatMC(A=np.eye(2), q=2, p=1, Np=100000)

# Verifica que la norma de la primera componente de nMC es aproximadamente 1
assert np.allclose(nMC[0], 1, atol=1e-2)

# Verifica que el valor absoluto de la primera componente de nMC[1] es 1, o la segunda componente de nMC[1] es 1
assert np.allclose(np.abs(nMC[1][0]), 1, atol=1e-3) or np.allclose(np.abs(nMC[1][1]), 1, atol=1e-3)

# Verifica que el valor absoluto de la primera componente de nMC[1] es 0, o la segunda componente de nMC[1] es 0
assert np.allclose(np.abs(nMC[1][0]), 0, atol=1e-3) or np.allclose(np.abs(nMC[1][1]), 0, atol=1e-3)

# Segundo set de asserts: utilizando norma infinita (L∞) con la matriz identidad
nMC = normaMatMC(A=np.eye(2), q=2, p=np.inf, Np=100000)

# Verifica que lnorma de la primera componente de nMC es aproximadamente sqrt(2)
print(nMC[0])
print(np.sqrt(2))
assert np.allclose(nMC[0], np.sqrt(2), atol=1e-3)

# Verifica que el valor absoluto de la primera componente de nMC[1] es 1, y la segunda componente de nMC[1] también es 1
assert np.allclose(np.abs(nMC[1][0]), 1, atol=1e-3) and np.allclose(np.abs(nMC[1][1]), 1, atol=1e-3)

# Tercer set de asserts: con una matriz A arbitraria
A = np.array([[1, 2], [3, 4]])

# Calcula la norma infinita con la matriz A y 1 millón de puntos
nMC = normaMatMC(A=A, q=np.inf, p=np.inf, Np=1000000)
