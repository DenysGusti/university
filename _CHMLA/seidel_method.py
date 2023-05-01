from math import sqrt


class SeidelMethod:
    def __init__(self):
        if _ := True:
            self.A = [[2., 1., 0.],
                      [1., 2., 1.],
                      [0., 1., 2.]]
            # self.A = [[16., 3.],
            #           [7., -11.]]
            self.b = [3., 4., 3.]
            # self.b = [11., 13.]
            self.n = len(self.A)
        else:
            self.n = SeidelMethod.initializeN()
            self.A = self.initializeMatrix()
            self.b = self.initializeVector()

        self.x: list[float] | None = None

    @staticmethod
    def initializeN():
        return int(input('Введіть розмір матриці, n = '))

    def initializeMatrix(self) -> list[list[float]]:
        print(f'Введіть квадратну матрицю [{self.n} * {self.n}]:')
        return list(list(map(float, input().split())) for _ in range(self.n))

    def initializeVector(self) -> list[float]:
        print(f'Введіть вектор значень розміром {self.n}:')
        return list(map(float, input().split()))

    def printSystem(self) -> 'SeidelMethod':
        print("\nМатриця системи:")
        for i in range(self.n):
            print(f'''{" ".join(map(lambda x: f'{x:5.1f}', self.A[i]))}\t|\t{self.b[i]}''')
        print()
        return self

    def checkDiagonalDominance(self) -> bool:
        return all(abs(self.A[i][i]) >=
                   sum(abs(self.A[i][j]) if i != j else 0.
                       for j in range(self.n))
                   for i in range(self.n))

    def findSolutions(self, *, eps: float) -> 'SeidelMethod':
        if not self.checkDiagonalDominance():
            print("Матриця не має діагональної переваги")
            return self

        x_old = [0. for _ in range(self.n)]
        x_new = [float("inf") for _ in range(self.n)]

        iter_counter = 0
        while self.findEps(x_old, x_new) > eps:
            for i in range(self.n):
                sum_l_new: float = sum(self.A[i][j] * x_new[j] for j in range(i))
                sum_r_old: float = sum(self.A[i][j] * x_old[j] for j in range(i + 1, self.n))
                x_new[i] = (self.b[i] - sum_l_new - sum_r_old) / self.A[i][i]
            x_old, x_new = x_new, x_old
            iter_counter += 1

        self.x = x_old
        for i, x in enumerate(self.x):
            print(f"x[{i}] = {x}")

        print(f"{eps = }\nКількість ітерацій: {iter_counter}")
        print(f"Векторна норма ||Ax-b|| = {self.findNorm()}")

    def findEps(self, prev_vector: list[float], cur_vector: list[float]) -> float:
        return sqrt(sum(
            (prev_vector[i] - cur_vector[i]) ** 2
            for i in range(self.n)))

    def findNorm(self) -> float:
        return sqrt(sum(
            (sum(self.A[i][j] * self.x[j] for j in range(self.n)) - self.b[i]) ** 2
            for i in range(self.n)))


def main() -> None:
    SeidelMethod().printSystem().findSolutions(eps=1e-6)


if __name__ == '__main__':
    main()
