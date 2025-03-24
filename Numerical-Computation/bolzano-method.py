import numpy as np
import matplotlib.pyplot as plt

# Masukkan fungsi disini (contoh nomer 3 e)
def f(x):
    return (np.exp(x)-np.log(x)-20)

def bolzano(a, b, tol, max_iter):
    if f(a) * f(b) > 0:
        print("Fungsi tidak memiliki akar di interval ini.")
        return None

    iter = 0
    while max_iter > iter:
        c = (a + b) / 2
        if f(c) == 0 or np.abs(b - a)/2 < tol:
            print(f"Perkiraan akar ditemukan pada x = {c} dengan f(x) = {f(c)}")
            break
        print(f"Iterasi {iter + 1}: \na = {a}\nb = {b}\nc = {c}\nf(a) = {f(a)}\nf(b) = {f(b)}\nf(c) = {f(c)}")
        if f(c) * f(a) < 0:
            b = c
        else:
            a = c
        iter += 1

    return c

def graph(a, b, c):
    x = np.linspace(a, b, 400)
    y = f(x)

    plt.plot(x, y, label='f(x)')
    plt.axhline(0, color='black', lw=0.5)
    plt.axvline(c, color='red', linestyle='--', label='Akar')
    plt.title('Grafik Fungsi')
    plt.xlabel('x')
    plt.ylabel('f(x)')
    plt.legend()
    plt.grid()
    plt.show()
    
def main():
    a = 2.5
    b = 3.5
    tol = 1e-12
    max_iter = 200

    akar = bolzano(a, b, tol, max_iter)
    if akar is not None:
        graph(a, b, akar)

if __name__ == "__main__":
    main()