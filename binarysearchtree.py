from binarytree import TreeNode, BinaryTree

class BSTNode(TreeNode):
    def __init__(self, key, value = None):
        TreeNode.__init__(self)

        self.key = key
        self.value = value
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
        if self.root:
            self._insert(node, self.root)
        else:
            self.root = node
        self.count += 1

    def _insert(self, node, currentNode):
        if node.key < currentNode.key:
            if currentNode.leftChild:
                self._insert(node, currentNode.leftChild)
            else:
                node.parent = current
                current.leftChild = node
        elif node.key > currentNode.key:
            if currentNode.rightChild:
                self._insert(node, currentNode.rightChild)
            else:
                node.parent = current
                current.rightChild = node
        else:
            currentNode.value = node.value

    def find(self, key):
        if self.root:
            found = self._find(key, self.root)
            if found:
                return found.value
        return None

    def _find(self, key, currentNode):
        if currentNode is None:
            return None

        if key < currentNode.key:
            return self._find(key, currentNode.leftNode)
        elif key > currentNode.key:
            return self._find(key, currentNode.rightNode)
        else:
            return currentNode.value

    def delete(self, key):
        pass

