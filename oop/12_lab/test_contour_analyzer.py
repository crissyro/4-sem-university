import unittest
from contour_analyzer import ContourAnalyzer, Point

class TestContourAnalyzer(unittest.TestCase):
    def setUp(self):
        self.analyzer = ContourAnalyzer()

    def test_single_point(self):
        with open('single_point.txt', 'w') as f:
            f.write('1')
            
        self.analyzer.load_matrix('single_point.txt')
        count, center = self.analyzer.find_max_circle()
        
        self.assertEqual(count, 1)
        self.assertEqual(center, Point(0, 0))

    def test_two_points(self):
        with open('two_points.txt', 'w') as f:
            f.write('1 0\n')
            f.write('0 1\n')
            
        self.analyzer.load_matrix('two_points.txt')
        count, center = self.analyzer.find_max_circle()
        
        self.assertEqual(count, 2)
        
        expected_center = Point(0.5, 0.5)
        
        self.assertEqual(center, expected_center)

    def test_four_points_on_circle(self):
        matrix = [
            ['0', '0', '1', '0', '0'],
            ['0', '0', '0', '0', '0'],
            ['1', '0', '0', '0', '1'],
            ['0', '0', '0', '0', '0'],
            ['0', '0', '1', '0', '0']
        ]
        
        with open('circle.txt', 'w') as f:
            for row in matrix:
                f.write(' '.join(row) + '\n')
                
        self.analyzer.load_matrix('circle.txt')
        
        count, center = self.analyzer.find_max_circle()
        
        self.assertEqual(count, 4)
        self.assertEqual(center, Point(2.0, 2.0))


    def test_collinear_points(self):
        matrix = [['1', '1', '1']]
        with open('collinear.txt', 'w') as f:
            for row in matrix:
                f.write(' '.join(row) + '\n')
                
        self.analyzer.load_matrix('collinear.txt')
        count, center = self.analyzer.find_max_circle()
        
        self.assertEqual(count, 0)
        self.assertIsNone(center)


    def test_empty_file(self):
        with open('empty.txt', 'w') as f:
            f.write('')
            
        self.analyzer.load_matrix('empty.txt')
        count, center = self.analyzer.find_max_circle()
        
        self.assertEqual(count, 0)
        self.assertIsNone(center)


if __name__ == '__main__':
    unittest.main()