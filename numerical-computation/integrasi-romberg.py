import numpy as np

A = 0.0  # Batas bawah integrasi
B = 2.0  # Batas atas integrasi
ROMBERG_MAX_ITERATION = 4 # Jumlah interval untuk metode Romberg
TRAPEZOIDAL_INTERVAL = 64 # Jumlah interval untuk metode Trapezoidal

# Fungsi yang akan diintegralkan
f = lambda x: 4 * x**3 + 2 * x

def trapezoid(a, b, n=TRAPEZOIDAL_INTERVAL):
    h = (b - a) / n
    integral = 0.5 * (f(a) + f(b))
    for i in range(1, n):
        integral += f(a + i * h)
        print(f"I({a + i * h}):\t\t{integral * h:.10f}")
    print("-" * 40)
    return integral * h

def romberg(a, b, max_iter=ROMBERG_MAX_ITERATION):
    table = np.zeros((max_iter, max_iter))

    h = b - a
    table[0, 0] = 0.5 * h * (f(a) + f(b))

    for i in range(1, max_iter):
        h /= 2.0
        c = 0
        n = 2**i
        
        for j in range(1, n, 2):
            c += f(a + j * h)
        table[i, 0] = h * c + 0.5 * table[i-1, 0]
        print(f"R({i+1},1) [n={n}]:\t{table[i,0]:.10f}")

        for j in range(1, i + 1):
            table[i, j] = ((4**j * table[i, j-1]) - table[i-1, j-1]) / ((4**j) - 1)
            print(f"  -> R({i+1},{j+1}):\t{table[i,j]:.10f}")
        print("-" * 40)

    return table[max_iter-1, max_iter-1]

if __name__ == "__main__":
    print("\n---------- Integrasi Romberg ----------")
    romberg_result = romberg(A, B)
    
    print("\n---------- Metode Trapezoidal ----------")
    trapezoidal_result = trapezoid(A, B)

    print("\n" + "="*40 + "RINGKASAN AKHIR" + "="*40)
    print(f"Hasil Integrasi Romberg ({ROMBERG_MAX_ITERATION} iterasi): {romberg_result:.10f}")
    print(f"Hasil Trapezoidal (n={TRAPEZOIDAL_INTERVAL}): {trapezoidal_result:.10f}")
    print("="*40)