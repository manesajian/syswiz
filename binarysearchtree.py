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

    def __next__(self):
        returnObj = self.__next

        if returnObj is None:
                raise StopIteration

        if returnObj.leftChild:
            self.__next = returnObj.leftChild
        elif returnObj.rightChild:
            self.__next = returnObj.rightChild
        else:
            self.__next = None

        return returnObj

    def insert_node(self, node):
        pass

    def find_node(self, node):
        pass

    def delete_node(self, node):
        pass
