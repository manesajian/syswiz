class TreeNode():
    def __init__(self):
        self.parent = None
        self.leftChild = None
        self.rightChild = None
        self.value = None

class BinaryTree():
    def __init__(self):
        self.root = None
        self.count = 0

    def __len__(self):
        return self.count

    def height(self, node = None):
        if node == None:
            return self._height(self.root)
        return self._height(node)

    def _height(self, node):
        if node == None:
            return 0
        return max(self._height(node.leftChild),
                   self._height(node.rightChild)) + 1

    def depth_first_traversal(self):
        pass

    def breadth_first_traversal(self):
        pass

