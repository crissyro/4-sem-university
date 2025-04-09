class Matrix:
    """
    Класс для представления матрицы и работы с суммами строк.

    Атрибуты:
        data (list of list of int): Данные матрицы, где каждый вложенный список представляет строку.

    Примеры:
        >>> m1 = Matrix([[1, 2], [3, 4]])
        >>> m2 = Matrix([[3, 4], [1, 2]])
        >>> m1 == m2
        True
        >>> m3 = Matrix([[1, 1], [2, 2]])
        >>> m1 == m3
        False
    """

    def __init__(self, data):
        self.__data = data

    def row_sums(self):
        """Возвращает список сумм строк матрицы."""
        return [sum(row) for row in self.__data]

    def __eq__(self, other):
        """Проверяет равенство матриц по суммам строк (порядок строк не учитывается)."""
        return sorted(self.row_sums()) == sorted(other.row_sums())

    def __str__(self):
        """Возвращает строковое представление матрицы."""
        return '\n'.join([' '.join(map(str, row)) for row in self.__data])


def process_matrices(input_data):
    """
    Обрабатывает входные данные с матрицами, разделенными пустыми строками, 
    и возвращает пары совпадающих матриц.

    Аргументы:
        input_data (str): Входные данные в виде строки.

    Возвращает:
        str: Результат обработки или сообщение об ошибке.

    Примеры:
        >>> input_data = '1 2\\n3 4\\n\\n4 3\\n2 1'
        >>> print(process_matrices(input_data))
        Матрица на входе:
        1 2
        3 4
        <BLANKLINE>
        Матрица на выходе:
        4 3
        2 1
        <BLANKLINE>
        Матрица на входе:
        4 3
        2 1
        <BLANKLINE>
        Матрица на выходе:
        1 2
        3 4

        >>> input_data = '1 a\\n2 3'
        >>> print(process_matrices(input_data))
        Ошибка: неверный формат входных данных. Строки должны содержать только числа, разделенные пробелами.
    """
    matrices = []
    current_matrix_data = []

    for line in input_data.splitlines():
        line = line.strip()
        if line:
            try:
                row = list(map(int, line.split()))
                current_matrix_data.append(row)
            except ValueError:
                return "Ошибка: неверный формат входных данных. Строки должны содержать только числа, разделенные пробелами."
        else:
            if current_matrix_data:
                matrices.append(Matrix(current_matrix_data))
                current_matrix_data = []
    
    if current_matrix_data:
        matrices.append(Matrix(current_matrix_data))

    if not matrices:
        return "Нет матриц для обработки."

    output = []
    for i, matrix in enumerate(matrices):
        matching_matrices = []
        for j, other in enumerate(matrices):
            if i != j and matrix == other:
                matching_matrices.append(other)
        
        if matching_matrices:
            output.append(f"Матрица на входе:\n{matrix}\n\nМатрица на выходе:\n{matching_matrices[0]}")

    return '\n\n'.join(output) if output else "Нет совпадающих матриц."


# from io import StringIO
# input_data = StringIO("1 1 1 2\n3 1 1 4\n2 1 5 3\n\n1 1 1 2\n3 1 3 4\n2 1 5 3\n\n1 2 1 1\n1 2 1 5\n1 1 5 4")
# result = process_matrices(input_data.read())
# print(result)