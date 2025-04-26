import random
from typing import List, Tuple

from config.config import GRID_HEIGHT, GRID_WIDTH

class Food:
    def __init__(self):
        self.position: Tuple[int, int] = (0, 0)
        self.spawn()
        self.animation = 0.0

    def spawn(self, snake_body: List[Tuple[int, int]] = None):
        while True:
            self.position = (
                random.randint(0, GRID_WIDTH - 1),
                random.randint(0, GRID_HEIGHT - 1)
            )
            if snake_body is None or self.position not in snake_body:
                break

    def update(self, dt):
        self.animation = (self.animation + dt * 8) % 1.0