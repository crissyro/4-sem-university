import itertools

class Point:
    """Класс для представления точки в двумерном пространстве."""
    def __init__(self, x: float, y: float):
        self.x = x
        self.y = y

    def __eq__(self, other: 'Point') -> bool:
        """Проверка равенства точек с учетом погрешности."""
        epsilon = 1e-6
        return (abs(self.x - other.x) < epsilon and 
                abs(self.y - other.y) < epsilon)

    def __repr__(self) -> str:
        return f"Point({self.x:.2f}, {self.y:.2f})"
    
class Circle:
    """Класс для представления окружности."""
    def __init__(self, center: Point, radius: float):
        self.center = center
        self.radius = radius

    def contains_point(self, point: Point, epsilon: float = 1e-6) -> bool:
        """Проверяет, лежит ли точка на окружности с учетом погрешности."""
        dx = point.x - self.center.x
        dy = point.y - self.center.y
        distance_sq = dx**2 + dy**2
        return abs(distance_sq - self.radius**2) < epsilon

    def __repr__(self) -> str:
        return f"Circle(center={self.center}, radius={self.radius:.2f})"