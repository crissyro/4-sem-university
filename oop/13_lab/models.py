from dataclasses import dataclass

@dataclass
class Recipe:
    title: str
    ingredients: str
    instructions: str
    category: str = 'General'
    
    def to_dict(self):
        return {
            'title': self.title,
            'ingredients': self.ingredients,
            'instructions': self.instructions,
            'category': self.category
        }