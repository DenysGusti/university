from math import sqrt


class GaussSolver:
    def __init__(self):
        self.n: int = GaussSolver.initializeN()
        self.a: list[list[float]] = self.initializeMatrix()
        self.b: list[float] = self.initializeVector()
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

    def printSystem(self, msg: str) -> 'GaussSolver':
        print('\n' + msg)
        for i in range(self.n):
            print(f'''{" ".join(map(lambda x: f'{x:5}', self.a[i]))}\t|\t{self.b[i]}''', sep='')
        print()
        return self

    def maxAbsIdxInColumn(self, k: int) -> int:
        max_abs: float = abs(self.a[k][k])
        m: int = k
        for i in range(k + 1, self.n):
            if abs(self.a[i][k]) > max_abs:
                max_abs, m = abs(self.a[i][k]), i
        return m

    def triangulateMatrix(self) -> 'GaussSolver':
        for k in range(self.n - 1):
            if not any(self.a[i][k] for i in range(self.n)):
                break

            if k != (m := self.maxAbsIdxInColumn(k)):
                self.b[k], self.b[m], self.a[k], self.a[m] = self.b[m], self.b[k], self.a[m], self.a[k]
                self.p += 1

            for i in range(k + 1, self.n):
                m_ik: float = -self.a[i][k] / self.a[k][k]
                self.b[i] += m_ik * self.b[k]
                for j in range(k, self.n):
                    self.a[i][j] += m_ik * self.a[k][j]

        return self

    def findSolutions(self) -> 'GaussSolver':
        if idxs := [i for i in range(self.n) if not any(self.a[i])]:
            print("D = 0\nРозв'язків " + ('немає' if any(self.b[i] for i in idxs) else 'безліч'))
            return self

        self.x = [0. for _ in range(self.n)]
        for k in range(self.n - 1, -1, -1):
            s: float = 0.
            for j in range(k + 1, self.n):
                s += self.a[k][j] * self.x[j]
            self.x[k] = (self.b[k] - s) / self.a[k][k]

        self.d = (-1) ** self.p
        for i in range(self.n):
            self.d *= self.a[i][i]
        print(f'D = {self.d}')

        for i in range(self.n):
            print(f'x[{i}] = {self.x[i]:5}')
        return self

    def findNorm(self) -> 'GaussSolver':
        if not self.d:
            return self

        norm: float = 0.
        for i in range(self.n):
            norm += (sum(self.a[i][j] * self.x[j] for j in range(self.n)) - self.b[i]) ** 2
        norm = sqrt(norm)

        print(f'Векторна норма ||Ax-b|| = {norm}')


def main() -> None:
    GaussSolver() \
        .printSystem("Матриця системи:").triangulateMatrix().printSystem("Трикутна матриця:").findSolutions().findNorm()


if __name__ == '__main__':
    main()
