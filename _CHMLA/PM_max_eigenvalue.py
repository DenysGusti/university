from statistics import mean


class PMMaxEigenvalue:
    def __init__(self):
        if _ := True:
            self.A = [[1., 2., 3.],
                      [2., 5., 2.],
                      [3., 2., 1.]]
            self.n = len(self.A)
        else:
            self.n = PMMaxEigenvalue.initializeN()
            self.A = self.initializeMatrix()
        self.L: float | None = None
        self.y: list[float] | None = None

    @staticmethod
    def initializeN():
        return int(input('Введіть розмір матриці, n = '))

    def initializeMatrix(self) -> list[list[float]]:
        print(f'Введіть квадратну матрицю [{self.n} * {self.n}]:')
        return list(list(map(float, input().split())) for _ in range(self.n))

    def printMatrix(self) -> 'PMMaxEigenvalue':
        print("\nA:")
        for row in self.A:
            print(f'''{" ".join(map(lambda x: f'{x:5.1f}', row))}''')
        print()
        return self

    def Amul(self, x: list[float]) -> list[float]:
        result = [0. for _ in range(self.n)]
        for i in range(self.n):
            result[i] = sum(self.A[i][j] * x[j] for j in range(self.n))
        return result

    @staticmethod
    def norm(y: list[float]) -> float:
        # return sqrt(sum(y_i ** 2 for y_i in y))
        return max(abs(y_i) for y_i in y)

    def findMaxEigenvalue(self, *, delta: float, eps: float) -> 'PMMaxEigenvalue':
        yk_1 = [1. for _ in range(self.n)]
        norm_y = PMMaxEigenvalue.norm(yk_1)
        xk_1 = [y_i / norm_y for y_i in yk_1]
        lk_1 = [0. for _ in range(self.n)]
        k = 1

        print(f"{delta = }, {eps = }")
        print(f"y(0) = {yk_1}\n")

        while True:
            yk = self.Amul(xk_1)
            norm_yk = PMMaxEigenvalue.norm(yk)
            xk = [y_i / norm_yk for y_i in yk]

            lk = [yk[i] / xk_1[i] for i in range(self.n)]
            valid_indexes = [i for i in range(self.n) if abs(xk_1[i]) > delta]

            delta_l = [lk[i] - lk_1[i] for i in range(len(valid_indexes))]
            print(f"y({k}) = {yk}\nx({k}) = {xk}\nL[{k}] = {mean(lk[i] for i in valid_indexes)}\n")
            if PMMaxEigenvalue.norm(delta_l) < eps:
                self.L = mean(lk[i] for i in valid_indexes)
                self.y = xk
                break

            k += 1
            xk_1, lk_1 = xk, lk

        return self

    def printResults(self) -> None:
        print(f"Max abs eigenvalue = {self.L}\nEigenvector = {self.y}")


def main() -> None:
    PMMaxEigenvalue().printMatrix().findMaxEigenvalue(delta=1e-7, eps=1e-7).printResults()


if __name__ == '__main__':
    main()
