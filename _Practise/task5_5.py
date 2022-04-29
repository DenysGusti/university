# Прочитати дату у форматі "yyyy-mm-dd hh:mm:ss" з файлу. Визначити кут у градусах між годинною та хвилинною стрілками
# годинника та вивести відповідне повідомлення. Секундами можна знехтувати.
# Години hh можуть приймати значення від 0 до 23. Врахувати залежність годинної стрілки від хвилинної.

def reading() -> str:  # контекстний менеджер with, для автоматичного закриття файлу (навіть при помилці)
    with open(r"time.txt") as f:  # r - raw string
        return f.read()


def hour_arrow(hh: int, mm: int, ss: int) -> float:  # яку частину від кола пройшла годинна стрілка (0.0 - 1.0)
    # за добу стрілка проходить циферблат 2 рази, тому беремо по модулю від 1: (0.0 - 2.0) -> (0.0 - 1.0)
    return (hh * 3600 + mm * 60 + ss) / 43200 % 1


def minute_arrow(mm: int, ss: int) -> float:  # яку частину від кола пройшла хвилинна стрілка (0.0 - 1.0)
    return (mm * 60 + ss) / 3600


if __name__ == '__main__':
    time = reading().split()[1]  # читаємо тільки годину
    print(time)
    h, m, s = map(int, time.split(':'))  # години, хвилини і секунди
    print(f'{360 * abs(hour_arrow(h, m, s) - minute_arrow(m, s)):.15}°')  # домножуємо на градуси й округляємо до 1e-15
