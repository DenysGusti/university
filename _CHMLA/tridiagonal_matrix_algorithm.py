from math import sqrt


class TriDiagonalMatrixAlgorithm:
    def __init__(self, *, test: bool | None):
        if test is None:
            self.n = self.initializeN()  # n + 1
            self.A = [1. for _ in range(self.n - 2)] + [0.]
            self.B = [0.] + [1. for _ in range(self.n - 2)]
            h = 1 / (self.n - 1)
            self.C = [1.] + [(-2 - (1 + i * h) * h ** 2) for i in range(1, self.n - 1)] + [1.]
            self.D: list[list[float]] = self.recreateD()
            self.F = [1.] + [
                (h ** 2 * (4 - (1 + i * h) * (2 * i ** 2 * h ** 2 + 1))) for i in range(1, self.n - 1)
            ] + [3.]

        elif test:
            self.D: list[list[float]] = [
                [2., -1., 0., 0., 0.],
                [1., -5., 2., 0., 0.],
                [0., 1., -5., 2., 0.],
                [0., 0., 1., -5., 2.],
                [0., 0., 0., -1., 5.]
            ]
            self.F: list[float] = [2., 3., -3., -4., -1.]
            self.n = len(self.D)

        else:
            self.n = self.initializeN()
            self.D: list[list[float]] = self.initializeMatrix()
            self.F = self.initializeVector()

        if test is not None:
            self.A: list[float] = self.getA()
            self.B: list[float] = self.getB()
            self.C: list[float] = self.getC()

        self.printSystem()

        if test is None:
            self.correct = True
        else:
            self.correct: bool = self.isCorrect()

        self.y: list[float] = self.leftAlgorithm()

        if test is None:
            self.findNormOriginal()
        else:
            self.findNorm()

    @staticmethod
    def initializeN():
        return int(input('Введіть розмір матриці - 1, n = ')) + 1

    def initializeMatrix(self) -> list[list[float]]:
        print(f'Введіть квадратну матрицю [{self.n} * {self.n}]:')
        return list(list(map(float, input().split())) for _ in range(self.n))

    def initializeVector(self) -> list[float]:
        print(f'Введіть вектор значень розміром {self.n}:')
        return list(map(float, input().split()))

    def getA(self) -> list[float]:
        return [self.D[i + 1][i] for i in range(self.n - 1)]

    def getB(self) -> list[float]:
        return [self.D[i][i + 1] for i in range(self.n - 1)]

    def getC(self) -> list[float]:
        return [self.D[i][i] for i in range(self.n)]

    def printSystem(self) -> 'TriDiagonalMatrixAlgorithm':
        print("D = ")
        for row in self.D:
            print('\t', '\t'.join(map(lambda x: f'{x:>4}', row)))
        print("\nF = ", '\t'.join(map(lambda x: f'{x:>4}', self.F)))
        print("A = ", '\t'.join(map(lambda x: f'{x:>4}', self.A)))
        print("B = ", '\t'.join(map(lambda x: f'{x:>4}', self.B)))
        print("C = ", '\t'.join(map(lambda x: f'{x:>4}', self.C)))
        return self

    def isCorrect(self) -> bool:
        if not all(self.C):
            print("|C[i]|>0, i=0,...,n is not correct")
            return False

        if not all(self.A):
            print("|A[i]|>0, i=1,...,n is not correct")
            return False

        if not all(self.B):
            print("|B[i]|>0, i=0,...n-1 is not correct")
            return False

        if abs(self.C[0]) < abs(self.B[0]):
            print("|C[0]|>=|B[0]| is not correct")
            return False

        if abs(self.C[-1]) < abs(self.A[-1]):
            print("|C[n]|>=|A[n]| is not correct")
            return False

        if any((abs(self.C[i]) < abs(self.A[i - 1]) + abs(self.B[i])) for i in range(1, self.n - 1)):
            print("|C[i]|>=|A[i]|+|B[i]|, i=1,...,n-1 is not correct")
            return False

        print("\nCorrect")
        return True

    def leftAlgorithm(self) -> list[float]:
        if not self.correct:
            return []

        xi = [0. for _ in range(self.n)]
        eta = [0. for _ in range(self.n)]
        y = [0. for _ in range(self.n)]

        xi[-1] = -self.A[-1] / self.C[-1]
        eta[-1] = self.F[-1] / self.C[-1]

        for i in range(self.n - 2, 0, -1):
            xi[i] = -self.A[i - 1] / (self.C[i] + self.B[i] * xi[i + 1])
            eta[i] = (self.F[i] - self.B[i] * eta[i + 1]) / (self.C[i] + self.B[i] * xi[i + 1])

        y[0] = (self.F[0] - self.B[0] * eta[1]) / (self.C[0] + self.B[0] * xi[1])

        for i in range(1, self.n):
            y[i] = xi[i] * y[i - 1] + eta[i]

        print()
        for i in range(self.n - 1, 0, -1):
            print(f" xi[{i}] = {xi[i]}\neta[{i}] = {eta[i]}")
        print()
        for i in range(self.n):
            print(f"  y[{i}] = {y[i]}")
        print()

        return y

    def findNorm(self) -> 'TriDiagonalMatrixAlgorithm':
        if not self.correct:
            return self

        norm: float = 0.
        for i in range(self.n):
            norm += (sum(self.D[i][j] * self.y[j] for j in range(self.n)) - self.F[i]) ** 2
        norm = sqrt(norm)
        print(f"Норма ||Dy-F|| = {norm}")

        return self

    def findNormOriginal(self) -> 'TriDiagonalMatrixAlgorithm':
        h = 1 / (self.n - 1)
        y_original = [(2 * i ** 2 * h ** 2 + 1) for i in range(self.n)]
        for i in range(self.n):
            print(f"  y*[{i}] = {y_original[i]}")
        print()

        norm: float = 0.
        for i in range(self.n):
            norm += (self.y[i] - y_original[i]) ** 2
        norm = sqrt(norm)
        print(f"Норма ||∆y|| = {norm}")

        return self

    def recreateD(self) -> list[list[float]]:
        d = [[self.C[i] if i == j else 0. for i in range(self.n)] for j in range(self.n)]
        for i in range(self.n - 1):
            d[i + 1][i] = self.A[i]
            d[i][i + 1] = self.B[i]
        return d


def main() -> None:
    TriDiagonalMatrixAlgorithm(test=None)


if __name__ == '__main__':
    main()
