from fractions import Fraction
from itertools import combinations

# Функция для проверки, является ли вектор нулевым
def is_zero_vector(vector: list) -> bool:
    return vector == [0] * len(vector)

# Функция для копирования матрицы
def clone_matrix(matrix: list) -> list:
    return [row[:] for row in matrix]

# Функция для вывода матрицы
def output_matrix(matrix: list):
    for row in matrix:
        print(*row)
    print()

# Функция для вычисления определителя матрицы
def determinant(matrix: list) -> Fraction:
    n = len(matrix)

    # Базовые случаи для матриц 1x1 и 2x2
    if n == 1:
        return matrix[0][0]
    if n == 2:
        return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0]

    det = 0

    # Рекурсивное вычисление определителя для матриц большего размера
    for j in range(n):
        minor = [row[:j] + row[j + 1:] for row in matrix[1:]]
        det += matrix[0][j] * ((-1) ** (1 + j + 1)) * determinant(minor)

    return det

# Функция для получения столбца матрицы по индексу
def get_column(matrix: list, col_index: int) -> list:
    return [row[col_index] for row in matrix]

# Функция для создания матрицы из выбранных столбцов
def create_matrix_from_cols(matrix: list, col_indices: list) -> list:
    return [get_column(matrix, i) for i in col_indices]

# Функция для вычисления ранга матрицы
def matrix_rank(matrix: list) -> int:
    rows = len(matrix)
    cols = len(matrix[0]) if matrix else 0
    rank = 0

    # Перебор всех возможных подматриц для вычисления ранга
    for order in range(1, min(rows, cols) + 1):
        for i in range(rows - order + 1):
            for j in range(cols - order + 1):
                sub_matrix = [row[j:j + order] for row in matrix[i:i + order]]
                det = determinant(sub_matrix)
                if det != 0:
                    rank += 1
                    break
            if det != 0:
                break

    return rank

# Функция для приведения матрицы к стандартному виду (без последнего столбца)
def cut_matrix_to_standard(matrix: list) -> list:
    return [row[:-1] for row in clone_matrix(matrix)]

# Функция для выполнения метода Гаусса-Жордана
def Gauss_Jordan_eliminations(matrix: list, basic_var_indices: tuple) -> list:
    if matrix_rank(matrix) != matrix_rank(cut_matrix_to_standard(matrix)):
        return -1

    n = len(matrix)
    for i in range(n):
        if is_zero_vector(matrix[i]):
            continue

        col_num = basic_var_indices[i]
        divisor = matrix[i][col_num]

        if divisor == 0:
            exchange_row = find_exchange_row(matrix, i, col_num)
            if exchange_row is None:
                return -1
            matrix[i], matrix[exchange_row] = matrix[exchange_row], matrix[i]
            divisor = matrix[i][col_num]

        matrix[i] = [Fraction(elem, divisor) for elem in matrix[i]]

        for j in range(len(matrix)):
            if is_zero_vector(matrix[j]):
                continue
            if i != j:
                multiplier = matrix[j][col_num]
                matrix[j] = [elem_j - elem_i * multiplier for elem_i, elem_j in zip(matrix[i], matrix[j])]

    return matrix

# Функция для поиска строки для обмена в методе Гаусса-Жордана
def find_exchange_row(matrix: list, start_row: int, col_num: int) -> int:
    for row in range(start_row + 1, len(matrix)):
        if matrix[row][col_num] != 0:
            return row
    return None

# Функция для проверки, могут ли переменные быть базисными
def could_vars_be_basic(matrix: list, var_indices: list) -> bool:
    sub_matrix = create_matrix_from_cols(matrix, var_indices)
    det = determinant(sub_matrix)
    return det != 0

# Функция для получения всех наборов базисных переменных
def get_all_sets_of_basic_vars(matrix: list) -> list:
    sub_matrix = cut_matrix_to_standard(matrix)
    amount_of_basic_vars = matrix_rank(sub_matrix)
    all_vars = len(sub_matrix[0])

    set_of_basic_vars = list(combinations(range(all_vars), amount_of_basic_vars))

    # Фильтрация наборов базисных переменных
    for i in set_of_basic_vars:
        if not could_vars_be_basic(clone_matrix(matrix), i):
            del i
    return set_of_basic_vars

# Функция для форматированного вывода переменных
def print_vars(var_indices: list) -> str:
    return '(' + ', '.join(f'x{i + 1}' for i in var_indices) + ')'

# Функция для создания строки линейного уравнения
def make_linear_equation(coefficients: list) -> str:
    equation = ''
    for idx, coeff in enumerate(coefficients[:-1]):
        if coeff:
            if coeff > 0:
                if coeff == 1:
                    equation += f'+ x{idx + 1} '
                else:
                    equation += f'+ {coeff}x{idx + 1} '
            else:
                if coeff == -1:
                    equation += f'-x{idx + 1} '
                else:
                    equation += f'{coeff}x{idx + 1} '
    equation += f'= {coefficients[-1]}'
    if equation[0] == '+':
        equation = equation[1:]
    return equation

# Функция для вывода системы линейных уравнений
def output_sle(matrix: list):
    output_string = '{'
    for row in matrix:
        if is_zero_vector(row):
            continue
        output_string += make_linear_equation(row) + ',\n'
    output_string = output_string[:-2] + '}'
    print(output_string)
    print()

# Функция для получения всех базисных видов системы линейных уравнений
def get_all_basic_views_of_SLE(matrix: list) -> list:
    sub_matrix = clone_matrix(matrix)
    set_of_basic_vars = get_all_sets_of_basic_vars(sub_matrix)
    list_of_basic_views = []

    for i in set_of_basic_vars:
        result = Gauss_Jordan_eliminations(clone_matrix(matrix), i)
        if result == -1:
            continue
        print(f'{set_of_basic_vars.index(i) + 1}. Базисные неизвестные:', print_vars(i))
        print('Система:')
        list_of_basic_views.append(result)
        output_sle(result)
    return list_of_basic_views

# Функция для преобразования дроби в float
def fract_to_float(x: Fraction) -> float:
    return float(x.numerator) / float(x.denominator)

# Функция для проверки, что все элементы вектора неотрицательные
def is_all_not_negative(vector: list) -> bool:
    return all(fract_to_float(x) >= 0 for x in vector)

# Функция для нахождения опорных решений
def find_reference_solutions(list_of_basic_views: list) -> list:
    list_of_reference_solutions = []

    for matrix in list_of_basic_views:
        solution_vector = get_column(clone_matrix(matrix), -1)
        if not is_all_not_negative(solution_vector):
            continue

        solution_matrix = clone_matrix(matrix)
        for x in range(len(matrix)):
            for y in range(len(matrix[x]) - 1):
                col = get_column(matrix[:], y)
                if not (sum(col) == 1 and col.count(0) == len(col) - 1):
                    solution_matrix[x][y] = 0

        list_of_reference_solutions.append(solution_matrix)
        output_sle(solution_matrix)

    return list_of_reference_solutions

# Функция для вычисления значения целевой функции
def goal(func: list, basic_matrix: list) -> Fraction:
    result = Fraction(0, 1)  # Инициализация дробным нулем
    for i in range(len(basic_matrix)):
        for j in range(len(func)):
            if basic_matrix[i][j] == 1:
                result += func[j] * basic_matrix[i][-1]
    return result

# Функция для нахождения оптимального плана
def find_optimal_plan(list_of_solutions: list, func: list, max_or_min: str) -> tuple:
    min_val = float('inf')
    max_val = -min_val
    res_matrix_min = []
    res_matrix_max = []

    for matrix in list_of_solutions:
        curr_val = goal(func, matrix)
        if curr_val >= max_val:
            res_matrix_max = matrix
            max_val = curr_val
        if curr_val <= min_val:
            res_matrix_min = matrix
            min_val = curr_val

    if max_or_min == 'min':
        return (min_val, res_matrix_min)
    return (max_val, res_matrix_max)

# Основная часть программы
equation_num = int(input("Количество уравнений в системе: "))
a = [[] for _ in range(equation_num)]

for i in range(equation_num):
    print(f'Коэффициенты уравнения {i + 1}', end='\n')
    a[i].extend(list(map(int, input().split())))

print(f'Целевая функция ({len(a[0]) - 1} чисел)')
func = list(map(int, input().split()))
max_or_min = input('Введите "max", если значение функции стремится к максимуму, иначе "min":\n')

print('Введенная система уравнений:')
output_sle(a)

print('Все базисные виды системы:')
all_basic_views = get_all_basic_views_of_SLE(a)

print('Опорные решения системы:')
reference_solutions = find_reference_solutions(all_basic_views)

optimal_solution = find_optimal_plan(reference_solutions, func, max_or_min)
print(f'Оптимальное решение для z = {func}:')
print(fract_to_float(optimal_solution[0]), f'({optimal_solution[0]})')
output_sle(optimal_solution[1])