# Для заданих n та a обчислити суму s = 1 + 2²a + ... + n²aⁿ⁻¹ = ∑(i=1, n) i²aⁱ⁻¹.
if __name__ == "__main__":
    n, a = map(int, input("n, a = ").split())  # ввід n, a

    s = sum(i ** 2 * a ** (i - 1) for i in range(1, n + 1))  # до s в циклі додаємо i²aⁱ⁻¹ від 1 до n

    print(f"\n{n = }, {a = }\n{s = }")
