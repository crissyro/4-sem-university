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
    
    def load_data(self):
        if not os.path.exists(self.FILE_PATH):
            self.recipes = []
        else:
            with open(self.FILE_PATH, 'r') as f:
                data = json.load(f)
                self.recipes = [Recipe(**item) for item in data]