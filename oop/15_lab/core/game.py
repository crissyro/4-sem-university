import pygame
import config.config as cnf
from core.snake import Snake, Direction
from core.food import Food
from core.records import RecordsManager

class Game:
    def __init__(self):
        self.screen = pygame.display.set_mode((cnf.SCREEN_WIDTH, cnf.SCREEN_HEIGHT))
        pygame.display.set_caption("Snake Game")
        self.clock = pygame.time.Clock()
        self.records_manager = RecordsManager()
        self.reset_game()

    def reset_game(self):
        self.snake = Snake()
        self.food = Food()
        self.score = 0
        self.game_over = False
        self.paused = False
        self.difficulty = None

    def show_menu(self):
        menu = True
        selected = 0
        difficulties = list(cnf.Difficulty)

        while menu:
            self.screen.fill(cnf.COLOR_BG)
            
            for i, diff in enumerate(difficulties):
                color = cnf.COLOR_TEXT if i == selected else (100, 100, 100)
                text = cnf.FONT.render(
                    f"{diff.name.capitalize()} (Speed: {diff.value})"
                    f" Record: {self.records_manager.get_record(diff.name.lower())}", 
                    True, color
                )
                self.screen.blit(text, (50, 100 + i * 50))

            pygame.display.flip()

            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    pygame.quit()
                    quit()
                if event.type == pygame.KEYDOWN:
                    if event.key == pygame.K_DOWN:
                        selected = (selected + 1) % len(difficulties)
                    elif event.key == pygame.K_UP:
                        selected = (selected - 1) % len(difficulties)
                    elif event.key == pygame.K_RETURN:
                        self.difficulty = difficulties[selected]
                        return

    def handle_events(self):
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                quit()
            elif event.type == pygame.KEYDOWN:
                if self.game_over:
                    self.reset_game()
                    self.show_menu()
                elif event.key == pygame.K_UP:
                    self.snake.change_direction(Direction.UP)
                elif event.key == pygame.K_DOWN:
                    self.snake.change_direction(Direction.DOWN)
                elif event.key == pygame.K_LEFT:
                    self.snake.change_direction(Direction.LEFT)
                elif event.key == pygame.K_RIGHT:
                    self.snake.change_direction(Direction.RIGHT)
                elif event.key == pygame.K_p:
                    self.paused = not self.paused

    def update(self):
        if self.game_over or self.paused:
            return

        self.snake.move()

        if self.snake.body[0] == self.food.position:
            self.snake.grow()
            self.score += 1
            self.food.spawn(self.snake.body)

        if self.snake.check_self_collision():
            self.game_over = True
            self.records_manager.update_record(
                self.difficulty.name.lower(), 
                self.score
            )

    def draw(self):
        self.screen.fill(cnf.COLOR_BG)

        for i, segment in enumerate(self.snake.body):
            color = cnf.COLOR_SNAKE if i == 0 else (0, 200, 0)
            x = segment[0] * cnf.GRID_SIZE
            y = segment[1] * cnf.GRID_SIZE
            pygame.draw.rect(self.screen, color, (x, y, cnf.GRID_SIZE-1, cnf.GRID_SIZE-1))

        food_x = self.food.position[0] * cnf.GRID_SIZE
        food_y = self.food.position[1] * cnf.GRID_SIZE
        pygame.draw.rect(self.screen, cnf.COLOR_FOOD, (food_x, food_y, cnf.GRID_SIZE-1, cnf.GRID_SIZE-1))

        score_text = cnf.FONT.render(
            f"Score: {self.score} | Record: "
            f"{self.records_manager.get_record(self.difficulty.name.lower())}", 
            True, cnf.COLOR_TEXT
        )
        
        self.screen.blit(score_text, (10, 10))

        if self.paused:
            paused_text = cnf.FONT.render("PAUSED", True, cnf.COLOR_TEXT)
            self.screen.blit(paused_text, (cnf.SCREEN_WIDTH//2 - 50, cnf.SCREEN_HEIGHT//2))

        if self.game_over:
            game_over_text = cnf.FONT.render("Game Over! Press any key", True, cnf.COLOR_TEXT)
            self.screen.blit(game_over_text, (cnf.SCREEN_WIDTH//2 - 120, cnf.SCREEN_HEIGHT//2))

        pygame.display.flip()

    def run(self):
        self.show_menu()
        while True:
            self.handle_events()
            self.update()
            self.draw()
            self.clock.tick(self.difficulty.value if self.difficulty else cnf.FPS)
