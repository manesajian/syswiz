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
        if node.balanceFactor > 1 or node.balanceFactor < -1:
            self._rebalance(node)
            return

        if node.parent != None:
            if node == node.parent.leftChild:
                node.parent.balanceFactor += 1
            else:
                node.parent.balanceFactor -= 1

            if node.parent.balanceFactor != 0:
                self._balance(node.parent)

    def _rebalance(self, node):
        if node.balanceFactor < 0:
            if node.rightChild.balanceFactor > 0:
                self._rotateRight(node.rightChild)
                self._rotateLeft(node)
            else:
                self._rotateLeft(node)
        elif node.balanceFactor > 0:
            if node.leftChild.balanceFactor < 0:
                self._rotateLeft(node.leftChild)
                self._rotateRight(node)
            else:
                self._rotateRight(node)

    def _rotateLeft(self, node):
        newRoot = node.rightChild
        node.rightChild = newRoot.leftChild
        if newRoot.leftChild != None:
            newRoot.leftChild.parent = node
        newRoot.parent = node.parent
        if node.parent == None:
            self.root = newRoot
        else:
            if node == node.parent.leftChild:
                node.parent.leftChild = newRoot
            else:
                node.parent.rightChild = newRoot
        newRoot.leftChild = node
        node.parent = newRoot
        node.balanceFactor = node.balanceFactor + \
                             1 - min(newRoot.balanceFactor, 0)
        newRoot.balanceFactor = newRoot.balanceFactor + \
                                1 + max(node.balanceFactor, 0)
 
    def _rotateRight(self, node):
        newRoot = node.leftChild
        node.leftChild = newRoot.rightChild
        if newRoot.rightChild != None:
            newRoot.rightChild.parent = node
        newRoot.parent = node.parent
        if node.parent == None:
            self.root = newRoot
        else:
            if node == node.parent.rightChild:
                node.parent.rightChild = newRoot
            else:
                node.parent.leftChild = newRoot
        newRoot.rightChild = node
        node.parent = newRoot
        node.balanceFactor = node.balanceFactor + \
                             1 + max(newRoot.balanceFactor, 0)
        newRoot.balanceFactor = newRoot.balanceFactor + \
                                1 - min(node.balanceFactor, 0)
 
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


