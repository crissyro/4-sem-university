import pygame
from enum import Enum

SCREEN_WIDTH = 640
SCREEN_HEIGHT = 480
GRID_SIZE = 20
GRID_WIDTH = SCREEN_WIDTH // GRID_SIZE
GRID_HEIGHT = SCREEN_HEIGHT // GRID_SIZE

COLOR_BG = (0, 0, 0)
COLOR_SNAKE = (0, 255, 0)
COLOR_FOOD = (255, 0, 0)
COLOR_TEXT = (255, 255, 255)
COLOR_HEADER = (100, 100, 100)

class Difficulty(Enum):
    EASY = 8
    MEDIUM = 12
    HARD = 16

pygame.init()
FONT_SIZE = 36
FONT = pygame.font.Font(None, FONT_SIZE)