import json

class RecordsManager:
    def __init__(self, filename='records.json'):
        self.filename = filename
        self.records = self.load_records()

    def load_records(self):
        try:
            with open(self.filename, 'r') as f:
                return json.load(f)
        except (FileNotFoundError, json.JSONDecodeError):
            return {'easy': 0, 'medium': 0, 'hard': 0}

    def save_records(self):
        with open(self.filename, 'w') as f:
            json.dump(self.records, f)

    def update_record(self, level, score):
        if score > self.records.get(level, 0):
            self.records[level] = score
            self.save_records()

    def get_record(self, level):
        return self.records.get(level, 0)