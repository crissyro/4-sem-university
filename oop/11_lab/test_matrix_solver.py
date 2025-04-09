import unittest
import sys

from io import StringIO
from matrix_solver import MatrixCollection, Matrix

class TestMatrix(unittest.TestCase):

    def test_matrix_creation(self):
        m = Matrix([[1, 2], [3, 4]], 2)
        self.assertEqual(m.get_row_count(), 2)
        self.assertEqual(m.get_rows(), [[1, 2], [3, 4]])

    def test_get_row_sum(self):
        m = Matrix([[1, 2], [3, 4]], 2)
        self.assertEqual(m.get_row_sum(0), 3)
        self.assertEqual(m.get_row_sum(1), 7)

    def test_str_representation(self):
        m = Matrix([[1, 2], [3, 4]], 2)
        self.assertEqual(str(m), "1 2\n3 4")

class TestMatrixCollection(unittest.TestCase):

    def test_parse_matrices(self):
        raw_input = [
            "1 2 3",
            "4 5 6",
            "",
            "7 8 9",
            "10 11 12"
        ]
        collection = MatrixCollection(raw_input)
        self.assertEqual(len(collection._MatrixCollection__matrices), 2)
        self.assertEqual(collection._MatrixCollection__matrices[0].get_row_count(), 2)
        self.assertEqual(collection._MatrixCollection__matrices[1].get_row_count(), 2)

    def test_find_matching_rows(self):
        raw_input = [
            "1 2 3",
            "4 5 6",
            "",
            "7 8 9",
            "4 5 6"
        ]
        collection = MatrixCollection(raw_input)
        matching_rows = collection._MatrixCollection__find_matching_rows()
        self.assertEqual(len(matching_rows), 2)
        self.assertEqual(matching_rows[0], (1, '4 5 6', 2, '4 5 6'))

    def test_display_matches_output(self):
        raw_input = [
            "1 2 3",
            "4 5 6",
            "",
            "7 8 9",
            "4 5 6"
        ]
        collection = MatrixCollection(raw_input)

        captured_output = StringIO()
        sys.stdout = captured_output
        collection.display_matches()
        sys.stdout = sys.__stdout__

        expected_output = "Матрица 1:\n    4 5 6 → 4 5 6\n\nМатрица 2:\n    4 5 6 → 4 5 6\n\n"
        self.assertEqual(captured_output.getvalue(), expected_output)

if __name__ == "__main__":
    unittest.main()
