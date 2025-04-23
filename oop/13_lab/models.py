class Recipe:
    def __init__(self, title, ingredients, instructions, notes):
        self.title = title
        self.ingredients = ingredients
        self.instructions = instructions
        self.notes = notes

class RecipeBook:
    def __init__(self):
        self.recipes = []

    def add(self, recipe):
        self.recipes.append(recipe)

    def update(self, index, title, ingredients, instructions, notes):
        if 0 <= index < len(self.recipes):
            recipe = self.recipes[index]
            recipe.title = title
            recipe.ingredients = ingredients
            recipe.instructions = instructions
            recipe.notes = notes

    def delete(self, index):
        if 0 <= index < len(self.recipes):
            del self.recipes[index]

    def all(self):
        return self.recipes