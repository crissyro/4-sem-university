from collections import defaultdict

class Matrix:
    """
    Класс, представляющий одну матрицу.
    """

    def __init__(self, data: list[list[int]], row_count: int):
        self.__data = data  
        self.__rows = row_count  

    def get_matrix(self) -> list[list[int]]:
        """Возвращает все строки матрицы."""
        return self.__data

    def get_row_sum(self, idx: int) -> int:
        """Возвращает сумму элементов строки по индексу."""
        return sum(self.__data[idx])

    def get_rows(self) -> int:
        """Возвращает количество строк в матрице."""
        return self.__rows

    def __str__(self) -> str:
        return "\n".join(" ".join(map(str, row)) for row in self.__data)


class MatrixCollection:
    """
    Класс для работы с коллекцией матриц.
    """

    def __init__(self, raw_input: list[str]):
        """
        Инициализация коллекции матриц из списка строк.
        """
        self.__matrices = self.__parse_matrices(raw_input)

    def __parse_matrices(self, lines: list[str]) -> list[Matrix]:
        """
        Преобразует входной список строк в список объектов Matrix.
        """
        matrices = []
        current_matrix = []
        row_count = 0

        for line in lines:
            if line.strip() == "":
                if current_matrix:
                    matrices.append(Matrix(current_matrix, row_count))
                    current_matrix = []
                    row_count = 0
            else:
                row = list(map(int, line.strip().split()))
                current_matrix.append(row)
                row_count += 1

        if current_matrix:
            matrices.append(Matrix(current_matrix, row_count))

        return matrices

    def __find_matching_rows(self) -> list[tuple[int, str, int, str]]:
        """
        Находит совпадающие строки по сумме.
        Возвращает кортежи: (номер_матрицы_1, строка_1, номер_матрицы_2, строка_2)
        """
        result = []

        for i, matrix in enumerate(self.__matrices):
            for row_index, row in enumerate(matrix.get_matrix()):
                row_sum = matrix.get_row_sum(row_index)

                for j, other_matrix in enumerate(self.__matrices):
                    if i == j:
                        continue 

                    for other_row in other_matrix.get_matrix():
                        if sum(other_row) == row_sum:
                            result.append((
                                i + 1, ' '.join(map(str, row)),
                                j + 1, ' '.join(map(str, other_row))
                            ))

        return result

    def display_matches(self) -> None:
        """
        Показывает совпадения строк между матрицами, у которых совпадает сумма.
        Формат:
        Матрица N:
            строка → совпадающая строка
        """
        matches = self.__find_matching_rows()
        grouped = defaultdict(list)

        for i, row_str, j, match_str in matches:
            grouped[i].append((row_str, match_str))

        for matrix_id in sorted(grouped):
            print(f"Матрица {matrix_id}:")
            for row_str, match_str in grouped[matrix_id]:
                print(f"    {row_str} → {match_str}")
            print()

