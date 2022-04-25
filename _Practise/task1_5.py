print('Для заданих n та a обчислити суму 1 + 2²a + ... + n²aⁿ⁻¹.')
n, a, s = int(input('n = ')), int(input('a = ')), 0  # рахую тільки для цілих n , a
for n in range(1, n + 1):  # з 1 до n
    s += n ** 2 * a ** (n - 1)  # + n²aⁿ⁻¹
print(f'(i={n}, a={a})\n∑ⁱₙ₌₁n²aⁿ⁻¹ = {s}')
