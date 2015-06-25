import unittest

from binarysearchtree import BinarySearchTree
from avltree import AVLTree

class TestBinarySearchTree(unittest.TestCase):

    def setUp():
        self.bst = BinarySearchTree()

    def tearDown():
        pass

    def test_insert():
        lst = [5, 8, 2, 1, 3, 9, 7, 4, 6, 0]

        for i in lst:
            self.bst.insert(i)

    def test_delete():
        self.bst.delete(5)

    def test_iteration():
        lst = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
        for i in self.bst.root:
            self.assertTrue(i == lst[i])

if __name__ == '__main__':
    unittest.main()
