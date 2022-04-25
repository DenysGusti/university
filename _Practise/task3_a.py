# while True: print(bin(eval('0b' + (s := input()).replace(' ', '').replace(\
# (o := '+' if '+' in s else '-' if '-' in s else '*'), o + '0b')))[2:])
def inp():
    while True:
        s = input().replace(' ', '')
        op = '+' if '+' in s else '-' if '-' in s else '*' if '*' in s else None
        if op is None:
            print("Помилка вводу")
            continue
        try:
            n1, n2 = map(list, s.split(op))
            n1, n2 = list(map(int, n1)), list(map(int, n2))
            if any(i > 1 for i in n1 + n2) or not len(n1) or not len(n2):
                print("Помилка вводу")
                continue
            return op, n1, n2
        except ValueError:
            print("Помилка вводу")
            continue


def normalize(n1, n2):
    size = max(len(n1), len(n2))
    n1 += [0] * (size - len(n1))
    n2 += [0] * (size - len(n2))
    return n1, n2


def add(n1, n2):
    overflow = 0
    res = []
    for pair in zip(n1, n2):  # (0-1, 0-1)
        digit = sum(pair, overflow)  # 0-3
        overflow = digit // 2  # 0-1
        res.append(digit % 2)  # 0-1
    if overflow: res.append(1)  # старший розряд
    return res


def subs(n1, n2):
    n2 = add([int(not i) for i in n2], [1] + [0] * (len(n2) - 1))  # ~побітово n2 + 1
    res = add(n1 + [0] * (len(n2) - len(n1)), n2)[:-1]  # n1 + n2 - старший
    return res


def mult(n1, n2):
    n = len(n1)
    add_n = [0] * n
    for i in range(n):
        if n1[i]: add_n = add(*normalize(add_n, [0] * i + n2))
    return add_n


def short(a):
    return a[:len(a) - a[::-1].index(1)] if 1 in a else [0]  # викинути перші нулі


def check(op, n1, n2, res):  # перевірка
    bn1, bn2 = '0b' + ''.join(map(str, n1[::-1])), '0b' + ''.join(map(str, n2[::-1]))
    res = '0b' + ''.join(map(str, res[::-1]))
    return eval(bn1 + op + bn2 + '==' + res)


def inptest():
    for i in range(100):
        for j in range(100):
            for o in ['+', '-', '*']:
                if o != '-' or i >= j:
                    yield o, list(map(int, bin(i)[2:])), list(map(int, bin(j)[2:]))


def calculate(op, n1, n2):
    n1, n2 = normalize(n1[::-1], n2[::-1])
    # print(op, n1, n2)
    res = add(n1, n2) if op == '+' else subs(n1, n2) if op == '-' else mult(n1, n2)
    res = short(res)
    print(*reversed(res), sep='')
    print(check(op, n1, n2, res))
    if not check(op, n1, n2, res): raise ValueError


if __name__ == '__main__':
    if test := 0:
        test_values = tuple(inptest())
        for k in test_values:
            print(k)
            operator, num1, num2 = k
            calculate(operator, num1, num2)
    else:
        while True:
            operator, num1, num2 = inp()
            calculate(operator, num1, num2)
