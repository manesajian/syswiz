from binarytree import TreeNode, BinaryTree

class BSTNode(TreeNode):
    def __init__(self, key):
        TreeNode.__init__(self)

        self.key = key
        self.leftChild = None
        self.rightChild = None

class BinarySearchTree(BinaryTree):
    def __init__(self):
        BinaryTree.__init__(self)

    def __iter__(self):
        if self.root:
            if self.root.leftChild:
                for elem in self.root.leftChild:
                    yield elem
            yield self.root.key
            if self.root.rightChild:
                for elem in self.root.rightChild:
                    yield elem

    def insert(self, node):
        pass

    def _insert(self, key, node, currentNode):
        pass

    def find(self, node):
        pass

    def delete(self, node):
        pass
