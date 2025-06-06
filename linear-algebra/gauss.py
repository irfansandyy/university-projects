import numpy as np

iteration = 0

def inputMatrix() -> np.ndarray:
    try:
        n = int(input("Masukkan Jumlah Baris: "))
        m = int(input("Masukkan Jumlah Kolom: "))
    
        if n <= 0 or m <= 0:
            raise ValueError("Jumlah Baris dan Kolom harus lebih besar dari 0")
    
        matrix = list(map(int, input("Masukkan koefisien-koefisien variabel: ").split()))
    
        if len(matrix) != n * m:
            raise ValueError("Jumlah Koefisien Tidak Sesuai")
        return np.array(matrix, dtype=np.float64).reshape(n, m)
    except ValueError as e:
        print(f'Input Error: {e}')
        exit(0)

def rowSwap(matrix: np.ndarray, rowStart: int, rowEnd: int) -> None:
    global iteration
    iteration += 1
    print(f'Iteration: {iteration}\nSwapping Row {rowStart+1} and {rowEnd+1}')
    matrix[[rowStart, rowEnd]] = matrix[[rowEnd, rowStart]]
    print(matrix)

def rowDivide(matrix: np.ndarray, row: int, pivotLocation: int) -> None:
    global iteration
    iteration += 1
    print(f'Iteration: {iteration}\nDividing Row {row+1} by {matrix[row, pivotLocation]}')
    matrix[row] = matrix[row] / matrix[row, pivotLocation]
    np.around(matrix, 2, matrix)
    matrix = np.where(matrix == -0, 0, matrix)
    print(matrix)
    
def rowSum(matrix: np.ndarray, row: int, curRow: int, curCol: int) -> None:
    global iteration
    iteration += 1
    print(f'Iteration: {iteration}\nSubtracting Row {row+1} by {matrix[curRow, :] * matrix[row, curCol]}')
    matrix[row, :] = matrix[row, :] - (matrix[curRow, :] * matrix[row, curCol])
    np.around(matrix, 2, matrix)
    matrix = np.where(matrix == -0, 0, matrix)
    print(matrix)
    
def gauss(matrix: np.ndarray) -> None:
    mrow, mcol = matrix.shape
    zeroVectorSwap = 0
    doSum = False
    curRow = 0
    curCol = 0
    
    print('Input Matrix')
    print(matrix)
    
    while curCol < mcol and curRow < mrow:
        if not doSum and not np.any(matrix[curRow:, curCol]):
            curCol += 1
        elif not doSum:
            for i in range(curRow, mrow):
                if matrix[i, curCol] != 0:
                    if i != curRow: rowSwap(matrix, curRow, i)
                    if matrix[curRow, curCol] != 1: rowDivide(matrix, curRow, curCol) 
                    doSum = True
                    break
        else:
            for i in range(curRow+1, mrow):
                if matrix[i, curCol] != 0:
                    rowSum(matrix, i, curRow, curCol)
                    if not np.any(matrix[i, :]) and not i >= mrow - 1 - zeroVectorSwap:
                        for j in range(mrow-1, -1, -1):
                            if np.any(matrix[j, :]):
                                rowSwap(matrix, i, j)
                                zeroVectorSwap += 1
                                rowSum(matrix, i, curRow, curCol)
                                break
                    elif not np.any(matrix[i, :]) and i == mrow - 1 - zeroVectorSwap:
                        zeroVectorSwap += 1
            doSum = False
            curCol += 1
            curRow += 1
                
if __name__ == '__main__':
    matrix = inputMatrix()
    gauss(matrix)