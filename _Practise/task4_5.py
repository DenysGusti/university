# Прочитати m груп (2 < m < 10) до n штук символів в групі (4 < n < 50). Надрукувати ту з груп, яка містить найбільше
# спільних символів зі всіх груп. Написати підпрограму (функцію або/та процедуру) для обчислення кількісного входження
# символів.

def number_of_letters(s: str) -> None:
    letters = set(s)
    letters_dict = {letter: s.count(letter) for letter in letters}
    print('Входження: ', end='')
    for key in sorted(letters_dict):
        print(f'{key}: {letters_dict[key]}', end='; ')
    print('\n')


# Ввід
m, n = int(input("m = ")), int(input("n = "))
groups = [input()[:n] for _ in range(m)]
#

for i, group in enumerate(groups):
    print(f"Стрічка {i + 1}: {group}")
    number_of_letters(group)

common = set.intersection(*(set(group) for group in groups))  # спільні символи
if not common:
    print("\nНемає спільних символів")
else:
    print("\nСпільні символи:", *sorted(common))

    common_symbols = [sum(group.count(element) for element in common) for group in groups]  # к-сть спільних для групи
    for i, k in enumerate(common_symbols):
        print(f"Стрічка {i + 1}: {k} спільних символів")

    maxShare = max(common_symbols)  # максимальне входження (багаторазове)
    print("\nНайбільше спільних символів:")
    for i in range(m):
        if common_symbols[i] == maxShare:
            print(f'Стрічка {i + 1}: {groups[i]}')
