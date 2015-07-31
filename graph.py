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


# for neighbor in graph[vertex]

class GraphNode():
    def __init__(self, key, value = None, neighbors = None):
        self.key = key
        self.value = value
        self.neighbors = neighbors

class Graph():
    def __init__(self):
        self.nodes = {}
        self.count = 0

    def __len__(self):
        return self.count

    def __iter__(self):
        return self.nodes.items()

    def __getitem__(self, key):
        return self.nodes[key]

    def __setitem__(self, node, neighbors):
        if node.key in self.nodes:
            del(node)

        self.nodes[node.key] = node

        for neighbor in node

        return

    def __delitem__(self, key):
        if key not in self.nodes:
            raise KeyError('{0} not found.'.format(key))
            for neighbor in self.nodes[node.key]:



