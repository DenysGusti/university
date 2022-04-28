# Написати інтерактивну програму для здійснення арифметичних операцій над натуральними числами у двійковій
# системі числення.
# 1. додавання двох чисел,
# 2. віднімання двох чисел (вважати перше число більшим за друге)
# 3. множення двох чисел,
# Операції реалізувати без переходу до десяткової системи числення.
# Вхідні дані: числа у двійковому представленні.
# Вихідні дані: числа у двійковому представленні.
# Перевірити коректність отриманих результатів, використовуючи вбудовані функції/дії в python.

def inp() -> tuple[str, list[int], list[int]]:  # функція вводу, вертає оператор і 2 числа у вигляді списків
    while True:
        s = input("\nВведіть приклад: ").replace(' ', '')  # забираємо пробіли
        op = '+' if '+' in s else '-' if '-' in s else '*' if '*' in s else None  # знаходимо оператор в стрічці
        if op is None:
            print("Помилка вводу")
            continue
        try:
            n1, n2 = map(list, s.split(op))  # ділимо стрічку оператором і робимо з чисел списки
            n1, n2 = list(map(int, n1)), list(map(int, n2))  # робимо списки цілих чисел
            if any(i > 1 for i in n1 + n2) or not len(n1) or not len(n2):
                print("Помилка вводу")
                continue
            return op, n1, n2
        except ValueError:
            print("Помилка вводу")
            continue


def normalize(n1: list[int], n2: list[int]) -> tuple[list[int], list[int]]:  # робить числа рівної довжини, додаючи нулі
    size = max(len(n1), len(n2))
    n1 += [0] * (size - len(n1))
    n2 += [0] * (size - len(n2))
    return n1, n2


def add(n1: list[int], n2: list[int]) -> list[int]:  # додавання
    overflow = 0
    res = []
    for pair in zip(n1, n2):  # (0-1, 0-1) кортежі одинакових розрядів 2 чисел
        digit = sum(pair, overflow)  # 0-3
        overflow = digit // 2  # 0-1, якщо сума розрядів вийшла >= 2, переносимо переповнення в наступний розряд
        res.append(digit % 2)  # 0-1, додаємо останню цифру суми за основою 2
    if overflow:
        res.append(1)  # старший розряд, якщо після додавання лишилося переповнення
    return res


def subs(n1: list[int], n2: list[int]) -> list[int]:  # віднімання
    n2 = add([int(not i) for i in n2], [1] + [0] * (len(n2) - 1))  # побітове ~ для n2 + 1
    res = add(n1 + [0] * (len(n2) - len(n1)), n2)[:-1]  # n1 + n2 - старший розряд
    return res


def mult(n1: list[int], n2: list[int]) -> list[int]:  # множення
    n = len(n1)
    add_n = [0] * n
    for i in range(n):  # представляємо множення як додавання в циклі в тих розрядах числа n1, де є 1
        if n1[i]:
            add_n = add(*normalize(add_n, [0] * i + n2))  # до результату додаємо n1 * 2^i (n2 << i)
    return add_n


def short(a: list[int]) -> list[int]:  # забирає зайві нулі в числа:  [0,1,0] -> [0,1], числа представлені задом наперед
    return a[:len(a) - a[::-1].index(1)] if 1 in a else [0]


def check(op: str, n1: list[int], n2: list[int], res: list[int]) -> bool:  # перевірка
    bn1, bn2 = '0b' + ''.join(map(str, n1[::-1])), '0b' + ''.join(map(str, n2[::-1]))
    res = '0b' + ''.join(map(str, res[::-1]))  # представляємо числа у стандартному двійковому вигляді 0b+біти
    return eval(bn1 + op + bn2 + '==' + res)  # обраховуємо стрічку як код


def inptest() -> tuple[str, list[int], list[int]]:  # функція з тестами, вертає оператор і 2 числа у вигляді списків
    for i in range(100):
        for j in range(100):
            for o in ['+', '-', '*']:
                if o != '-' or i >= j:
                    yield o, list(map(int, bin(i)[2:])), list(map(int, bin(j)[2:]))


def calculate(op: str, n1: list[int], n2: list[int]) -> None:  # обчислює
    n1, n2 = normalize(n1[::-1], n2[::-1])  # надалі числа у розвернутому вигляді, урівнюємо за довжиною
    res = add(n1, n2) if op == '+' else subs(n1, n2) if op == '-' else mult(n1, n2)
    res = short(res)  # викидаємо зайві нулі в результаті
    print(*reversed(res), sep='')  # друкуємо розархівований обернений масив бітів числа в нормальному вигляді
    print(check(op, n1, n2, res))  # перевірка
    if not check(op, n1, n2, res):
        raise ValueError


if __name__ == "__main__":
    if test := False:
        test_values = tuple(inptest())
        for k in test_values:
            print(k)
            operator, num1, num2 = k
            calculate(operator, num1, num2)
    else:
        while True:
            operator, num1, num2 = inp()
            calculate(operator, num1, num2)
