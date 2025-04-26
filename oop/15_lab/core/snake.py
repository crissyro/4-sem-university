from config.config import GRID_WIDTH, GRID_HEIGHT
from enum import Enum
from typing import List, Tuple

class Direction(Enum):
    UP = (0, -1)
    DOWN = (0, 1)
    LEFT = (-1, 0)
    RIGHT = (1, 0)

class Snake:
    def __init__(self):
        self.reset()
        
    def reset(self):
        self.body: List[Tuple[int, int]] = [(GRID_WIDTH // 2, GRID_HEIGHT // 2)]
        self.direction = Direction.RIGHT
        self.new_direction = None
        self.grow_next_move = False

    def change_direction(self, new_dir: Direction):
        old_x, old_y = self.direction.value
        new_x, new_y = new_dir.value
        if (new_x + old_x, new_y + old_y) != (0, 0):
            self.new_direction = new_dir

    def move(self):
        if self.new_direction:
            self.direction = self.new_direction
            self.new_direction = None

        head_x, head_y = self.body[0]
        dx, dy = self.direction.value
        new_head = (
            (head_x + dx) % GRID_WIDTH,
            (head_y + dy) % GRID_HEIGHT
        )
        
        self.body.insert(0, new_head)
        
        if not self.grow_next_move:
            self.body.pop()
        else:
            self.grow_next_move = False

    def grow(self):
        self.grow_next_move = True

    def check_self_collision(self):
        return self.body[0] in self.body[1:]