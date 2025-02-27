from fractions import Fraction
from prettytable import PrettyTable

# Инициализация таблицы для симплекс-метода
symplex = PrettyTable()

# Количество ограничений и переменных
count_restriction = 3  # Количество ограничений
count_variables = 6     # Количество переменных

# Матрица коэффициентов ограничений
matrix = [
    [1, -3, 0, -4, 0, -2, 8],
    [0, 6, 0, 5, 1, 2, 28],
    [0, 3, 1, -5, 0, -4, 10]
]

# Целевая функция
target_function = [0, 7, 0, 10, 0, 3]  # Целевая функция

# Заголовки таблицы симплекс-метода
symplex.field_names = ['Базисные переменные', 'x1', 'x2', 'x3', 'x4', 'x5', 'x6', 'Свободные члены']

# Функция для нахождения дельт
def find_delts(symplex_t, basis):
    finds_delts = []  # Массив для дельт
    # Находим дельты
    for i in range(count_variables + 1):
        number = 0
        for j in range(len(basis)):
            number += target_function[basis[j]] * matrix[j][i]
        finds_delts.append(number)
    finds_delts.insert(0, 'z')  # Вставляем "z" в начало
    # Создаем новую таблицу и заполняем ее обновленными данными
    new_symplex = PrettyTable()
    new_symplex.field_names = symplex_t.field_names  # копируем все строки, кроме последней
    for row in symplex_t._rows[:-1]:
        new_symplex.add_row(row)
    new_symplex.add_row(finds_delts)  # Добавляем дельты (всего 8 элементов)
    return new_symplex

# Функция для проверки базиса
def check_basis(symplex_t):
    basis = []
    for i in range(count_restriction + 1):
        row = ['0'] * (count_variables + 2)  # Создаем строку с нужным количеством элементов
        if i != count_restriction:
            flag = True
            for index, element in enumerate(matrix[i]):
                if flag and element == 1:
                    flag_ = True
                    for j in range(count_restriction):
                        if matrix[j][index] != 0 and j != i:
                            flag_ = False
                    if flag_:
                        row[0] = f'x{index + 1}'  # Вставляем базисную переменную в начало строки
                        basis.append(index)
                    else:
                        flag = False
                row[index + 1] = element  # Копируем значения в соответствующие ячейки таблицы
        symplex_t.add_row(row)
    return symplex_t, basis

# Функция для нахождения индекса минимальной дельты
def find_min_delta(symplex_t):
    min_index = -1
    min_delta = float('inf')
    delta = symplex_t.rows[-1][1:-1]
    for index, element in enumerate(delta):
        if element < min_delta:
            min_index = index
            min_delta = element
    return min_index, min_delta

# Функция для вычисления симплекс-отношений (Q)
def calculate_Q(symplex_t, min_index):
    q_values = []
    for row in symplex_t.rows[:-1]:
        q_value = Fraction(row[-1]) / Fraction(row[min_index])
        q_values.append(q_value)
    return q_values

# Функция для нахождения строки с минимальным симплекс-отношением
def find_min_Q(q_values):
    min_Q = float('inf')
    min_index = -1
    for index, q_value in enumerate(q_values):
        if q_value < min_Q:
            min_Q = q_value
            min_index = index
    return min_index, min_Q

# Функция для деления элементов для нахождения базиса
def divide(symplex_t, min_index, min_index_string):
    row = [symplex_t.rows[min_index_string][0]]  # Сохраняем базисную переменную (первый элемент)
    permissive_element_in_row = symplex_t.rows[min_index_string][min_index]  # Элемент, на который будем делить

    # Проверка, что элемент для деления является числом
    if not isinstance(permissive_element_in_row, (int, float)):
        print(f"Ошибка: элемент для деления {permissive_element_in_row} не является числом.")
        return symplex_t  # Возвращаем таблицу без изменений, чтобы избежать дальнейших ошибок

    for element in symplex_t.rows[min_index_string][1:]:
        # Проверка, что элемент является числом перед делением
        if isinstance(element, (int, float)):
            row.append(Fraction(element / permissive_element_in_row))  # Делим только если это число
        else:
            row.append(element)  # Если это не число (например, строка 'x1'), добавляем как есть

    # Создаем новый симплекс
    new_symplex = PrettyTable()
    new_symplex.field_names = symplex_t.field_names
    for index, element in enumerate(symplex_t._rows):
        row_ = list(element)
        if index == min_index_string:
            row_ = row  # Заменяем строку на новую, обновленную
        new_symplex.add_row(row_)

    return new_symplex


# Пример выполнения функции
symplex, basis = check_basis(symplex)
print("Таблица после начальной проверки базиса:")
print(symplex)

# Находим дельты
symplex = find_delts(symplex, basis)
print("Таблица после нахождения дельт:")
print(symplex)

# Шаг 1: Нахождение минимальной дельты
min_index, min_delta = find_min_delta(symplex)
print(f"Разрешающий столбец: {min_index + 1}, Δ{min_index + 1}: {min_delta}")

# Шаг 2: Вычисляем симплекс-отношения Q
q_values = calculate_Q(symplex, min_index)
print(f"Q: {q_values}")

# Шаг 3: Находим строку с минимальным Q
min_row_index, min_Q = find_min_Q(q_values)
print(f"Qmin = {min_Q}, строка {min_row_index + 1}")

# Шаг 4: Делим строку на разрешающий элемент
symplex = divide(symplex, min_index, min_row_index)
print("Таблица после деления строки на разрешающий элемент:")
print(symplex)