from binarytree import TreeNode, BinaryTree

class BSTNode(TreeNode):
    def __init__(self, key, value = None):
        TreeNode.__init__(self)

        self.key = key
        self.value = value
        self.leftChild = None
        self.rightChild = None

    def __iter__(self):
        if self.leftChild:
            for elem in self.leftChild:
                yield elem
        yield self.key
        if self.rightChild:
            for elem in self.rightChild:
                yield elem

    def find_successor(self):
        successor = None
        if self.rightChild:
            successor = self.rightChild.find_min()
        else:
            if self.parent:
                if self is self.parent.leftChild:
                    successor = self.parent
                else:
                    self.parent.rightChild = None
                    successor = self.parent.findSuccessor()
                    self.parent.rightChild = self
        return successor

    def find_min(self):
        current = self
        while current.leftChild:
            current = current.leftChild
        return current

class BinarySearchTree(BinaryTree):
    def __init__(self):
        BinaryTree.__init__(self)

    def insert(self, key, value = None):
        node = BSTNode(key, value)
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
                node.parent = currentNode
                currentNode.leftChild = node
        elif node.key > currentNode.key:
            if currentNode.rightChild:
                self._insert(node, currentNode.rightChild)
            else:
                node.parent = currentNode
                currentNode.rightChild = node
        else:
            currentNode.value = node.value

    def find(self, key):
        found = self._find(key, self.root)
        if found:
            return found.value

    def _find(self, key, currentNode):
        if currentNode is None:
            return None

        if key < currentNode.key:
            return self._find(key, currentNode.leftNode)
        elif key > currentNode.key:
            return self._find(key, currentNode.rightNode)
        else:
            return currentNode.value

    def __delitem__(self, key):
        self.delete(key)

    def delete(self, key):
        if self.count == 1:
            if self.root.key == key:
                self.root = None
                self.count -= 1
                return
        elif self.count > 1:
            node = self._find(key, self.root)
            if node:
                self._delete(node)
                return
        raise KeyError('{0} not found.'.format(key))

    def _delete(self, node):
        # handle 'neither', 'left', 'right', and 'both' children cases
        if node.leftChild is None and node.rightChild is None:
            if currentNode is node.parent.leftChild:
                currentNode.parent.leftChild = None
            else:
                currentNode.parent.rightChild = None
        elif node.leftChild and node.rightChild is None:
            if node.parent is None:
                self.root = node.leftChild
            elif currentNode is node.parent.leftChild:
                currentNode.parent.leftChild = node.leftChild
            else:
                currentNode.parent.rightChild = node.leftChild
            node.leftChild.parent = currentNode.parent
        elif node.rightChild and node.leftChild is None:
            if node.parent is None:
                self.root = node.rightChild
            elif currentNode is node.parent.leftChild:
                currentNode.parent.leftChild = node.rightChild
            else:
                currentNode.parent.rightChild = node.rightChild
            node.rightChild.parent = currentNode.parent
        else:
            successor = node.find_successor()
            self._delete(successor)
            currentNode.key = successor.key
            currentNode.value = successor.value

        self.count -= 1


