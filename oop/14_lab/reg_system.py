import datetime
from typing import List, Callable, Optional

class Task:
    __slots__ = ['_creation_time', '_execution_time', '_resources']

    def __init__(
        self,
        creation_time: Optional[datetime.datetime] = None,
        execution_time: Optional[datetime.timedelta] = None,
        resources: int = 0
    ):
        self._creation_time = creation_time if creation_time else datetime.datetime.now()
        self._execution_time = execution_time if execution_time else datetime.timedelta(0)
        
        if not isinstance(resources, int) or resources < 0:
            raise ValueError("Resources must be non-negative integer")
        self._resources = resources

    @property
    def creation_time(self) -> datetime.datetime:
        return self._creation_time

    @property
    def execution_time(self) -> datetime.timedelta:
        return self._execution_time

    @property
    def resources(self) -> int:
        return self._resources

    def __eq__(self, other: object) -> bool:
        if not isinstance(other, Task):
            return NotImplemented
        return (self.creation_time == other.creation_time and 
                self.execution_time == other.execution_time and 
                self.resources == other.resources)

    def __repr__(self) -> str:
        return f"Task({self.creation_time!r}, {self.execution_time!r}, {self.resources})"

    def __str__(self) -> str:
        return (f"Task [Created: {self.creation_time.strftime('%Y-%m-%d %H:%M')}, "
                f"Duration: {self.execution_time}, Resources: {self.resources}]")

class TaskContainer:
    __slots__ = ['_tasks']

    def __init__(self, tasks: Optional[List[Task]] = None):
        self._tasks = list(tasks) if tasks else []

    @property
    def tasks(self) -> List[Task]:
        return self._tasks

    def add_task(self, task: Task) -> None:
        if not isinstance(task, Task):
            raise TypeError("Only Task objects can be added")
        self._tasks.append(task)
        
    def __repr__(self) -> str:
        return f"TaskContainer({self._tasks!r})"

    def __str__(self) -> str:
        return "\n".join(str(task) for task in self._tasks)

    def bubble_sort(self, key: Callable[[Task], float] = lambda x: x.creation_time.timestamp()) -> None:
        n = len(self._tasks)
        for i in range(n):
            for j in range(0, n-i-1):
                if key(self._tasks[j]) > key(self._tasks[j+1]):
                    self._tasks[j], self._tasks[j+1] = self._tasks[j+1], self._tasks[j]
                    
    def insertion_sort(self, key: Callable[[Task], float] = lambda x: x.creation_time) -> None:
        for i in range(1, len(self._tasks)):
            current = self._tasks[i]
            j = i-1
            while j >= 0 and key(current) < key(self._tasks[j]):
                self._tasks[j+1] = self._tasks[j]
                j -= 1
            self._tasks[j+1] = current

    def selection_sort(self, key: Callable[[Task], float] = lambda x: x.creation_time) -> None:
        for i in range(len(self._tasks)):
            min_idx = i
            for j in range(i+1, len(self._tasks)):
                if key(self._tasks[j]) < key(self._tasks[min_idx]):
                    min_idx = j
            self._tasks[i], self._tasks[min_idx] = self._tasks[min_idx], self._tasks[i]