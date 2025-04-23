import json
import os
from typing import List
from models import Recipe

class DataManager:
    _instance = None
    FILE_PATH = 'recipes.json'
    
    def __new__(cls):
        if not cls._instance:
            cls._instance = super().__new__(cls)
            cls._instance.load_data()
        return cls._instance
    
    def load_data(self) -> None:
        if not os.path.exists(self.FILE_PATH):
            self.recipes = []
        else:
            with open(self.FILE_PATH, 'r') as f:
                data = json.load(f)
                self.recipes = [Recipe(**item) for item in data]
                
    def save_data(self) -> None:
        with open(self.FILE_PATH, 'w') as f:
            json.dump([recipe.to_dict() for recipe in self.recipes], f, indent=4)
            
    def get_all_recipes(self) -> List[Recipe]:
        return self.recipes
    
    def search_recipes(self, query: str) -> List[Recipe]:
        return [recipe for recipe in self.recipes if 
                query in recipe.title.lower() or
                query in recipe.ingredients.lower() or
                query in recipe.category.lower()]
    
    def add_recipe(self, recipe_data: dict):
        self.recipes.append(Recipe(**recipe_data))
        self.save_data()