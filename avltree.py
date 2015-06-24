from binarytree import TreeNode, BinaryTree

class AVLNode(BSTNode):
    def __init__(self, key, value = None):
        BSTNode.__init__(self)

class AVLTree(BinarySearchTree):
    def __init__(self):
        BinarySearchTree.__init__(self)

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
                self._balance(node)
        elif node.key > currentNode.key:
            if currentNode.rightChild:
                self._insert(node, currentNode.rightChild)
            else:
                node.parent = currentNode
                currentNode.rightChild = node
                self._balance(node)
        else:
            currentNode.value = node.value

    def _balance(self, node):
        pass

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
        elif node.leftChild and node.rightChild is None:
            if node.parent is None:
                self.root = node.leftChild
            elif node is node.parent.leftChild:
                node.parent.leftChild = node.leftChild
            else:
                node.parent.rightChild = node.leftChild
            node.leftChild.parent = node.parent
        elif node.rightChild and node.leftChild is None:
            if node.parent is None:
                self.root = node.rightChild
            elif node is node.parent.leftChild:
                node.parent.leftChild = node.rightChild
            else:
                node.parent.rightChild = node.rightChild
            node.rightChild.parent = node.parent
        else:
            successor = node.find_successor()
            self._delete(successor)
            node.key = successor.key
            node.value = successor.value

        self.count -= 1


