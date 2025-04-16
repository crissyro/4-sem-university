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
        
        self._resources = resources
        
    @property
    def get_creation_time(self) -> datetime.datetime:
        """Возвращает время создания задачи"""
        return self.__creation_time