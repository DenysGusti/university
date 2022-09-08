# Прочитати m груп (2 < m < 10) до n штук символів в групі (4 < n < 50). Надрукувати ту з груп, яка містить найбільше
# спільних символів зі всіх груп. Написати підпрограму (функцію або/та процедуру) для обчислення кількісного входження
# символів.

def number_of_letters(s: str) -> None:  # рахуємо букви і їхню кількість в стрічці
    letters = set(s)  # множина унікальних букв
    letters_dict = {letter: s.count(letter) for letter in letters}  # словник буква - кількість
    print("Входження: ", end='')
    print("; ".join(f"{key}: {value}" for key, value in sorted(letters_dict.items())))  # форматований вивід


if __name__ == "__main__":
    m, n = map(int, input("m, n = ").split())
    groups = [input()[:n] for _ in range(m)]  # вводимо m груп (стрічок) максимум по n чарів

    for i, group in enumerate(groups, start=1):
        print(f"Стрічка {i}: {group}")
        number_of_letters(group)  # рахуємо входження букв

    common = set.intersection(*(set(group) for group in groups))  # множина спільних символів
    if not common:
        print("\nНемає спільних символів")
    else:
        print("\nСпільні символи:", *sorted(common))
        # масив к-сті спільних символів для груп
        common_symbols = [sum(group.count(char) for char in common) for group in groups]
        for i, k in enumerate(common_symbols, start=1):
            print(f"Стрічка {i}: {k} спільних символів")

        maxShare = max(common_symbols)  # максимальне входження спільних символів в групах
        print(f"\nНайбільше спільних символів: {maxShare}")
        for i, group in enumerate(groups, start=1):
            if common_symbols[i - 1] == maxShare:  # виводимо декілька стрічок, в яких максимальна к-сть спільних
                print(f"Стрічка {i}: {group}")
