import unittest
import doctest

from io import StringIO
from matrix_solver import Matrix, process_matrices 

class TestMatrix(unittest.TestCase):
    def test_equality(self):
        m1 = Matrix([[1, 2], [3, 4]])
        m2 = Matrix([[3, 4], [1, 2]])
        self.assertEqual(m1, m2)

    def test_inequality(self):
        m1 = Matrix([[1, 2], [3, 4]])
        m3 = Matrix([[1, 1], [2, 2]])
        self.assertNotEqual(m1, m3)

class TestProcessMatrices(unittest.TestCase):
    def test_basic_case(self):
        input_data = StringIO("1 2\n3 4\n\n4 3\n2 1")
        result = process_matrices(input_data.read())
        expected = (
            "Матрица на входе:\n1 2\n3 4\n\nМатрица на выходе:\n4 3\n2 1\n\n"
            "Матрица на входе:\n4 3\n2 1\n\nМатрица на выходе:\n1 2\n3 4"
        )
        self.assertEqual(result, expected)

    def test_invalid_input(self):
        input_data = StringIO("1 a\n2 3")
        result = process_matrices(input_data.read())
        self.assertEqual(result, "Ошибка: неверный формат входных данных. Строки должны содержать только числа, разделенные пробелами.")

    def test_empty_input(self):
        result = process_matrices("")
        self.assertEqual(result, "Нет матриц для обработки.")
        
    def test_task_matrix(self):
        input_data = StringIO("1 1 1 2\n3 1 1 4\n2 1 5 3\n\n1 1 1 2\n3 1 3 4\n2 1 5 3\n\n1 2 1 1\n1 2 1 5\n1 1 5 4")
        result = process_matrices(input_data.read())
        self.assertEqual(result, """Матрица на входе:
1 1 1 2
3 1 1 4
2 1 5 3

Матрица на выходе:
1 2 1 1
1 2 1 5
1 1 5 4

Матрица на входе:
1 2 1 1
1 2 1 5
1 1 5 4

Матрица на выходе:
1 1 1 2
3 1 1 4
2 1 5 3""")

if __name__ == '__main__':
    doctest.testmod(verbose=True)
    unittest.main()