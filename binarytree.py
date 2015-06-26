class TreeNode():
    def __init__(self):
        self.parent = None
        self.leftChild = None
        self.rightChild = None

class BinaryTree():
    def __init__(self):
        self.root = None
        self.count = 0

    def __len__(self):
        return self.count

    def height(node):
        if node == None:
            return 0
        return max(height(node.leftChild), height(node.rightChild)) + 1

    def depth_first_traversal():
        pass

    def breadth_first_traversal():
        pass

