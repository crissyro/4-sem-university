from kivy.app import App
from kivy.core.window import Window
from ui.recipe_ui import RecipeAppUI

Window.clearcolor = (1, 1, 1, 1)

class RecipeApp(App):
    def build(self):
        return RecipeAppUI()

if __name__ == '__main__':
    RecipeApp().run()
