from binarytree import TreeNode, BinaryTree

class BSTNode(TreeNode):
    def __init__(self, key):
        TreeNode.__init__(self)

        self.key = key

class BinarySearchTree(BinaryTree):
    def __init__(self):
        BinaryTree.__init__(self)

    def insert_node(self, node):
        pass

    def find_node(self, node):
        pass

    def delete_node(self, node):
        pass
