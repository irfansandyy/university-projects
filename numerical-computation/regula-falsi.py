import numpy as np
import matplotlib.pyplot as plt

A = 2.5 # Batas Kiri
B = 3.5 # Batas Kanan
MAX_LINE = 4 # Jumlah Garis yang akan di cetak di plot
MAX_ITERATION = 200 # Maksimal Iterasi
MAX_TOLERANCE = 1e-12 # Maksimal Toleransi
GRAPH_TOLERANCE = (B-A)/4 # Jarak Fungsi yang di cetak dari batas awal dan akhir
FUNCTION_LINSPACE = round(((B-A) + GRAPH_TOLERANCE*2)*200)

# Masukkan fungsi disini (contoh nomer 3 e)
f = lambda x: np.exp(x) - np.log(x) - 20

def regula_falsi(a, b):
    x = np.linspace(a-GRAPH_TOLERANCE, b+GRAPH_TOLERANCE, FUNCTION_LINSPACE)
    y = f(x)

    plt.plot(x, y, label='f(x)')
    plt.axhline(0, color='black', lw=0.5)
    plt.title('Grafik Fungsi')
    plt.xlabel('x')
    plt.ylabel('f(x)')
    plt.grid()
    
    x1 = a
    x2 = b
    y1 = f(a)
    y2 = f(b)
    
    if y1 * y2 > 0:
        print("Fungsi tidak memiliki akar di interval ini.")
        return None
    
    plt.plot([x1, x2], [y1, y2])
    iter = 1
    while MAX_ITERATION > iter:
        xn = x1 - y1 * (x2 - x1) / (y2 - y1)
        if iter < MAX_LINE: plt.plot([xn], [0], 'o', label=f'{xn}')
        yn = f(xn)
        
        if abs(y1) < MAX_TOLERANCE:
            print(f"Perkiraan akar ditemukan pada x = {x1}")
            break
        
        print(f"Iterasi {iter}: \nx1 = {x1}\nx2 = {x2}\nf(x1) = {y1}\nf(x2) = {y2}\n")
        
        if y1 * yn < 0:
            x2 = xn
            y2 = yn
            if iter < MAX_LINE: plt.plot([x1, x2], [y1, y2])
        else:
            x1 = xn
            y1 = yn
            if iter < MAX_LINE: plt.plot([x1, x2], [y1, y2])

        if iter < MAX_LINE: plt.legend()
        iter += 1
    plt.axvline(x1, color='red', linestyle='--', label='Akar')
    plt.show()
    return x1
    
if __name__ == "__main__":
    regula_falsi(A, B)