# 1. Написати програму/функцію для перетворення натурального десяткового числа до числа, записаного у системі числення
# за основою a.
# 2. Написати програму/функцію для перетворення числа, записаного у системі числення за основою a, до натурального
# десяткового числа.
# 3. Написати програму, яка додає два числа, записані у системі числення за основою a. Використати перетворення до
# десяткової системи числення, додати числа і результат перетворити у відповідну систему числення.
# Для N (де N - номер в журналі) обрати основу a = ((N - 1) % 7) + 3. (3 - 9)

def _10_to_a(c: int, n: int) -> tuple[int]:  # переведення з 10 в a-у
    if not n:
        yield 0
    while n:
        yield n % c  # повертаємо останню цифру в n за основою c
        n //= c  # відкидаємо останню цифру в n за основою c


def a_to_10(c: int, n: int) -> tuple[int]:  # переведення з a-ої в 10
    if not n:
        yield 0
    (arr := list(map(int, str(n)))).reverse()  # розбиваємо число на цифри й розвертаємо
    for i, el in enumerate(arr):
        yield c ** i * el  # повертаємо arr[i] * a^i


def addition(c: int, n1: int, n2: int) -> tuple[int]:  # додавання в основі a 2 чисел
    (n1 := list(map(int, str(n1)))).reverse()  # розбиваємо число на цифри й розвертаємо
    (n2 := list(map(int, str(n2)))).reverse()
    size = max(len(n1), len(n2))  # урівнюємо числа за довжиною, додаючи нулі
    n1 += [0] * (size - len(n1))
    n2 += [0] * (size - len(n2))
    overflow = 0
    for pair in zip(n1, n2):  # (0 - a-1, 0 - a-1) кортежі однакових розрядів 2 чисел
        digit = sum(pair, overflow)  # (0 - 3a-3)
        overflow = digit // c  # 0 - a-1, якщо сума розрядів вийшла >= с, переносимо переповнення в наступний розряд
        yield digit % c  # 0 - a-1, додаємо останню цифру суми за основою с
    if overflow:  # старший розряд, якщо після додавання лишилося переповнення
        yield overflow


def testrun() -> None:  # тести
    for aa in range(3, 10):
        for i in range(101):
            for j in range(101):
                xx = int(''.join(map(str, reversed(list(_10_to_a(aa, i))))))  # переводимо числа i, j з 10 в a-ту
                yy = int(''.join(map(str, reversed(list(_10_to_a(aa, j))))))
                zz = int(''.join(map(str, reversed(list(addition(aa, xx, yy))))))  # додаємо їх в тій СЧ
                k = sum(a_to_10(aa, zz))
                print(f'{i} + {j} = {k}\n{aa}\n{xx} + {yy} = {zz}')
                print(eval(f'{i} + {j} == {k}'), end='\n' * 2)  # і перевіряємо чи збігається результат
                if not eval(f'{i} + {j} == {k}'):
                    raise ValueError


if __name__ == '__main__':
    if test := False:
        testrun()  # тести
    else:
        while True:
            N = int(input('N = '))
            a = ((N - 1) % 7) + 3  # 3 - 9
            print('Основа СЧ =', a)
            g = int(input(f'1 if 10 -> a({a}) | 2 if a({a}) -> 10 | 3 if x + y in a({a})\n\t'))
            match g:  # python 3.10
                case 1:  # з 10-ої в a
                    number = int(input('n = '))
                    print(*reversed(list(_10_to_a(a, number))), sep='')  # числа представляються як обернений масив цифр
                case 2:  # з a-ої в 10
                    number = int(input('n = '))
                    print(sum(a_to_10(a, number)))
                case 3:  # додавання 2 чисел безпосередньо за основою a
                    x, y = map(int, input().split('+'))
                    print(*reversed(list(addition(a, x, y))), sep='')
