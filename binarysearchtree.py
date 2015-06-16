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
        self.__node = self.root
        if self.__node:
            if self.__node.leftChild:
                for elem in self.__node.leftChild:
                    yield elem
            yield self.__node.key
            if self.__node.rightChild()
                for elem in self.__node.rightChild:
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
