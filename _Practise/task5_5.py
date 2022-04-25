# Прочитати дату у форматі "yyyy-mm-dd hh:mm:ss" з файлу. Визначити кут у градусах між годинною та хвилинною стрілками
# годинника та вивести відповідне повідомлення. Секундами можна знехтувати.
# Години hh можуть приймати значення від 0 до 23. Врахувати залежність годинної стрілки від хвилинної.
def reading() -> str:
    f = open('files/time.txt', 'r')
    t = f.read()
    f.close()
    return t


def reading2() -> str:
    with open('files/time.txt') as f:
        return f.read()


def hourArrow() -> float:
    return (h * 3600 + m * 60 + s) / 43200 % 1


def minuteArrow() -> float:
    return (m * 60 + s) / 3600


if __name__ == '__main__':
    time = reading2().split()[1]
    print(time)
    h, m, s = map(int, time.split(':'))
    print(f'{360 * abs(hourArrow() - minuteArrow()):.14}°')
