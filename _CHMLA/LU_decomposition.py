from math import sqrt


class LUDecomposition:
    def __init__(self):
        self.n: int = LUDecomposition.initializeN()
        self.A: list[list[float]] = self.initializeMatrix()
        self.b: list[float] = self.initializeVector()
        self.L: list[list[float]] = [[float(i == j) for i in range(self.n)] for j in range(self.n)]
        self.U: list[list[float]] = [[0. for _ in range(self.n)] for _ in range(self.n)]
        self.x: list[float] | None = None
        self.p: int = 0
        self.d: float = 0

    @staticmethod
    def initializeN():
        return int(input('Введіть розмір матриці, n = '))

    def initializeMatrix(self) -> list[list[float]]:
        print(f'Введіть квадратну матрицю [{self.n} * {self.n}]:')
        return list(list(map(float, input().split())) for _ in range(self.n))

    def initializeVector(self) -> list[float]:
        print(f'Введіть вектор значень розміром {self.n}:')
        return list(map(float, input().split()))

    def printSystem(self) -> 'LUDecomposition':
        print("\nМатриця системи:")
        for i in range(self.n):
            print(f'''{" ".join(map(lambda x: f'{x:5}', self.A[i]))}\t|\t{self.b[i]}''')
        print()
        return self

    def printLUMatrices(self) -> 'LUDecomposition':
        if not all(self.U[i][i] for i in range(self.n)):
            return self

        print(f"L:")
        for i in range(self.n):
            print(f'''{" ".join(map(lambda x: f'{x:5}', self.L[i]))}''')

        print(f"\nU:")
        for i in range(self.n):
            print(f'''{" ".join(map(lambda x: f'{x:5}', self.U[i]))}''')
        print()
        return self

    def findLUMatrices(self) -> 'LUDecomposition':
        for i in range(self.n):
            for j in range(i):
                self.L[i][j] = (self.A[i][j] - sum(self.L[i][k] * self.U[k][j] for k in range(j))) / self.U[j][j]
            for j in range(i, self.n):
                self.U[i][j] = self.A[i][j] - sum(self.L[i][k] * self.U[k][j] for k in range(i))
            if self.U[i][i] == 0:
                print("Один з головних мінорів матриці A = 0, розклад цим способом неможливий")
                return self
        return self

    def findSolutions(self) -> 'LUDecomposition':
        if not all(self.U[i][i] for i in range(self.n)):
            return self

        y = [0. for _ in range(self.n)]
        for i in range(self.n):
            y[i] = self.b[i] - sum(self.L[i][k] * y[k] for k in range(i))
        self.x = [0. for _ in range(self.n)]
        for i in range(self.n - 1, -1, -1):
            self.x[i] = (y[i] - sum(self.U[i][k] * self.x[k] for k in range(i + 1, self.n))) / self.U[i][i]

        self.d = 1.
        for i in range(self.n):
            self.d *= self.U[i][i]
        print(f'D = {self.d}')

        for i in range(self.n):
            print(f'x[{i}] = {self.x[i]:5}')
        return self

    def findNorm(self) -> 'LUDecomposition':
        if not self.d:
            return self

        norm: float = 0.
        for i in range(self.n):
            norm += (sum(self.A[i][j] * self.x[j] for j in range(self.n)) - self.b[i]) ** 2
        norm = sqrt(norm)
        print(f'Векторна норма ||Ax-b|| = {norm}')


def main() -> None:
    LUDecomposition().printSystem().findLUMatrices().printLUMatrices().findSolutions().findNorm()


if __name__ == '__main__':
    main()
