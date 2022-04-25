def _10_to_a(c, n):
    if not n: yield 0
    while n:
        yield n % c
        n //= c


def a_to_10(c, n):
    if not n: yield 0
    (arr := list(map(int, str(n)))).reverse()
    for i in range(len(arr)):
        yield c ** i * arr[i]


def addition(c, n1, n2):
    (n1 := list(map(int, str(n1)))).reverse(), (n2 := list(map(int, str(n2)))).reverse()
    size = max(len(n1), len(n2))
    n1 += [0] * (size - len(n1))
    n2 += [0] * (size - len(n2))
    overflow = 0
    for pair in zip(n1, n2):
        digit = sum(pair, overflow)
        overflow = digit // c
        yield digit % c
    if overflow: yield overflow


def testrun():
    for aa in range(3, 10):
        for i in range(101):
            for j in range(101):
                xx = int(''.join(map(str, reversed(list(_10_to_a(aa, i))))))
                yy = int(''.join(map(str, reversed(list(_10_to_a(aa, j))))))
                zz = int(''.join(map(str, reversed(list(addition(aa, xx, yy))))))
                k = sum(a_to_10(aa, zz))
                print(f'{i} + {j} = {k}\n{aa}\n{xx} + {yy} = {zz}')
                print(eval(f'{i} + {j} == {k}'), end='\n' * 2)
                if not eval(f'{i} + {j} == {k}'): raise ValueError


if __name__ == '__main__':
    if test := 0:
        testrun()
    else:
        while True:
            N = int(input('N = '))
            a = ((N - 1) % 7) + 3  # 3-9
            print('Основа СЧ =', a)
            g = int(input(f'1 if 10 -> a({a}) | 2 if a({a}) -> 10 | 3 if x + y in a({a})\n\t'))
            if g == 1:
                number = int(input('n = '))
                print(*reversed(list(_10_to_a(a, number))), sep='')
            elif g == 2:
                number = int(input('n = '))
                print(sum(a_to_10(a, number)))
            elif g == 3:
                x, y = map(int, input().split('+'))
                print(*reversed(list(addition(a, x, y))), sep='')
