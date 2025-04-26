import pytest
import datetime
from reg_system import Task, TaskContainer

class TestTaskSystem:
    @pytest.fixture
    def sample_tasks(self):
        return [
            Task(datetime.datetime(2025, 1, 3)),
            Task(execution_time=datetime.timedelta(hours=2)),
            Task(resources=5),
            Task(datetime.datetime(2025, 1, 1)),
            Task(datetime.datetime(2025, 1, 2))
        ]

    def test_task_creation(self):
        t = Task()
        assert t.resources == 0
        assert isinstance(t.creation_time, datetime.datetime)

        ct = datetime.datetime(2025, 1, 1)
        et = datetime.timedelta(hours=1)
        t = Task(ct, et, 5)
        assert t.creation_time == ct
        assert t.execution_time == et

    def test_resource_validation(self):
        with pytest.raises(ValueError):
            Task(resources=-1)
        with pytest.raises(ValueError):
            Task(resources="invalid")

    def test_task_equality(self):
        t1 = Task(datetime.datetime(2025, 1, 1))
        t2 = Task(datetime.datetime(2025, 1, 1))
        assert t1 == t2

    def test_container_initialization(self):
        container = TaskContainer()
        assert len(container.tasks) == 0

        tasks = [Task(), Task()]
        container = TaskContainer(tasks)
        assert len(container.tasks) == 2

    def test_add_task_validation(self):
        container = TaskContainer()
        container.add_task(Task())
        
        with pytest.raises(TypeError):
            container.add_task("invalid")
        
        with pytest.raises(TypeError):
            container.add_task(123)

    def test_sorting_operations_1(self, sample_tasks):
        container = TaskContainer(sample_tasks.copy())
        container.bubble_sort(key=lambda x: x.creation_time.timestamp())
        assert [t.creation_time.day for t in container.tasks] == [1, 2, 3, 26, 26]
        
    def test_sorting_operations_2(self, sample_tasks):
        container = TaskContainer(sample_tasks.copy())
        container.insertion_sort(key=lambda x: x.creation_time.timestamp())
        assert [t.creation_time.day for t in container.tasks] == [1, 2, 3, 26, 26]
        
    def test_sorting_operations_3(self, sample_tasks):
        container = TaskContainer(sample_tasks.copy())
        container.selection_sort(key=lambda x: x.creation_time.timestamp())
        assert [t.creation_time.day for t in container.tasks] == [1, 2, 3, 26, 26]
        
    def test_sorting_operations_4(self, sample_tasks):
        container = TaskContainer(sample_tasks.copy())
        container.bubble_sort(key=lambda x: x.resources)
        assert [t.creation_time.day for t in container.tasks] == [3, 26, 1, 2, 26]
        
    def test_sorting_operations_5(self, sample_tasks):
        container = TaskContainer(sample_tasks.copy())
        container.insertion_sort(key=lambda x: x.resources)
        assert [t.creation_time.day for t in container.tasks] == [3, 26, 1, 2, 26]
        
    def test_sorting_operations_6(self, sample_tasks):
        container = TaskContainer(sample_tasks.copy())
        container.selection_sort(key=lambda x: x.resources)
        assert [t.creation_time.day for t in container.tasks] == [3, 26, 1, 2, 26]

    def test_empty_container(self):
        container = TaskContainer()
        container.bubble_sort()
        assert len(container.tasks) == 0
        assert container.tasks == []

if __name__ == '__main__':
    pytest.main([__file__, '-v'])