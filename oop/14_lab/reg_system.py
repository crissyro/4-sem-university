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