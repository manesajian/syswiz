# generates paths in graph from start to target
def depth_first_search_paths(self, graph, start, target):
    stack = [(start, [start])]
    while stack:
        (vertex, path) = stack.pop()
        for next in graph[vertex] - set(path):
            if next == target:
                yield path + [next]
            else:
                stack.append((next, path + [next]))

# generates paths in graph from start to target
def breadth_first_search_paths(self, graph, start, target):
    queue = [(start, [start])]
    while queue:
        (vertex, path) = queue.pop(0)
        for next in graph[vertex] - set(path):
            if next == target:
                yield path + [next]
            else:
                queue.append((next, path + [next]))

class GraphNode():
    def __init__(self):
        self.value = None

class Graph():
    def __init__(self):
        self.count = 0

    def __len__(self):
        return self.count
