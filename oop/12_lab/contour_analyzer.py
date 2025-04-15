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