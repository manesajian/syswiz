from binarytree import BinaryTreeNode, BinaryTree

class BSTNode(BinaryTreeNode):
    def __init__(self, key, value = None):
        BinaryTreeNode.__init__(self)

        self.key = key
        self.value = value

        if self.value == None:
            self.value = self.key

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

    def find_max(self):
        current = self
        while current.rightChild:
            current = current.rightChild
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
            return currentNode

        return None

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
            if node is node.parent.leftChild:
                node.parent.leftChild = None
            else:
                node.parent.rightChild = None
            self.count -= 1
        elif node.leftChild and node.rightChild is None:
            if node.parent is None:
                self.root = node.leftChild
            elif node is node.parent.leftChild:
                node.parent.leftChild = node.leftChild
            else:
                node.parent.rightChild = node.leftChild
            node.leftChild.parent = node.parent
            self.count -= 1
        elif node.rightChild and node.leftChild is None:
            if node.parent is None:
                self.root = node.rightChild
            elif node is node.parent.leftChild:
                node.parent.leftChild = node.rightChild
            else:
                node.parent.rightChild = node.rightChild
            node.rightChild.parent = node.parent
            self.count -= 1
        else:
            successor = node.find_successor()
            self._delete(successor)
            node.key = successor.key
            node.value = successor.value
