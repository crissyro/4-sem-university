import datetime
from typing import List, Callable, Optional

'''
Разработать систему регистрации «Специальных задач». 

Каждая задача имеет характеристики время создание, требуемое время на выполнение и требуемые ресурсы. 
Контейнер этих задач умеет сортировать эти задачи «методом пузырька».

Теперь требуется добавить возможность сортировать задачи другими видами сортировок, 
сортировкой вставками, и сортировкой выбором. Так же, появляется возможность указания ключа сортировки.

'''

class Task:
    """
    Класс для представления специальной задачи.

    Атрибуты:
        creation_time (datetime.datetime): Время создания задачи
        execution_time (datetime.timedelta): Требуемое время на выполнение
        resources (int): Требуемые ресурсы

    Примеры:
    >>> t1 = Task(datetime.datetime(2023, 1, 1), datetime.timedelta(hours=2), 5)
    >>> t2 = Task(datetime.datetime(2023, 1, 2), datetime.timedelta(hours=1), 3)
    >>> t1 < t2
    True
    >>> t1 > t2
    False
    """
    __slots__ = ['__creation_time', '__execution_time', '__resources']
    
    def __init__(
        self,
        creation_time: Optional[datetime.datetime] = None,
        execution_time: Optional[datetime.timedelta] = None,
        resources: int = 0,
        ):
        
        self.__creation_time = creation_time if creation_time is not None else datetime.datetime.now()
        self.__execution_time = execution_time if execution_time is not None else datetime.timedelta(0)
        
        if not isinstance(resources, int) or resources < 0:
            raise ValueError("Resources must be non-negative integer")
        
        self.__resources = resources
        
    @property
    def get_creation_time(self) -> datetime.datetime:
        """Возвращает время создания задачи"""
        return self.__creation_time
    
    @property
    def execution_time(self) -> datetime.timedelta:
        """Возвращает требуемое время выполнения"""
        return self.__execution_time
    
    @property
    def resources(self) -> int:
        """Возвращает требуемые ресурсы"""
        return self.__resources
    
    @__resources.setter
    def set_resources(self, new_resources: int) -> None:
        if not isinstance(new_resources, int) or new_resources < 0:
            raise ValueError("Resources must be non-negative integer")
        
        self.__resources = new_resources
        
    def __eq__(self, other: object) -> bool:
        if not isinstance(other, Task):
            return NotImplemented
        
        return (self.creation_time == other.creation_time and 
                self.execution_time == other.execution_time and 
                self.resources == other.resources)
        
    def __lt__(self, other: 'Task') -> bool:
        return self.creation_time < other.creation_time

    def __repr__(self) -> str:
        return (f"Task(creation_time={self.creation_time!r}, "
                f"execution_time={self.execution_time!r}, "
                f"resources={self.resources})")

    def __str__(self) -> str:
        return (f"Task [Created: {self.creation_time.strftime('%Y-%m-%d %H:%M')}, "
                f"Duration: {self.execution_time}, "
                f"Resources: {self.resources}]")
        
class TaskContainer:
    """
    Контейнер для управления и сортировки задач.

    Поддерживаемые сортировки:
    - Пузырьковая сортировка
    - Сортировка вставками
    - Сортировка выбором

    Примеры:
    >>> tasks = [
    ...     Task(datetime.datetime(2023, 1, 3), datetime.timedelta(hours=3), 2),
    ...     Task(datetime.datetime(2023, 1, 1), datetime.timedelta(hours=5), 4),
    ...     Task(datetime.datetime(2023, 1, 2), datetime.timedelta(hours=1), 6)
    ... ]
    >>> container = TaskContainer(tasks)
    >>> container.bubble_sort(key=lambda x: x.resources)
    >>> [t.resources for t in container.tasks]
    [2, 4, 6]
    """
    
    __slots__ = ['__tasks']
    
    def __init__(self, tasks: Optional[List[Task]] = None):
        self.__tasks = list(tasks) if tasks else []
        
    @property
    def get_tasks(self) -> List[Task]:
        """Возвращает список задач"""
        return self.__tasks
    
    @__tasks.setter
    def set_tasks(self, new_tasks: Optional[List[Task]] = None) -> None:
        self.__tasks = new_tasks
        
    def add_task(self, task: Task) -> None:
        """Добавляет задачу в контейнер"""
        self.__tasks.append(task)
        
    def __repr__(self) -> str:
        return f"TaskContainer({self._tasks!r})"

    def __str__(self) -> str:
        return "\n".join(str(task) for task in self._tasks)
        
    def bubble_sort(self, key: Callable[[Task], float] = lambda x: x.creation_time) -> None:
        """Сортировка пузырьком с возможностью выбора ключа"""
        n = len(self._tasks)
        for i in range(n):
            for j in range(0, n-i-1):
                if key(self._tasks[j]) > key(self._tasks[j+1]):
                    self.__tasks[j], self.__tasks[j+1] = self.__tasks[j+1], self.__tasks[j]