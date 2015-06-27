import unittest

from binarysearchtree import BinarySearchTree
from avltree import AVLTree

class TestBinarySearchTree(unittest.TestCase):
    def setUp(self):
        self.bst = BinarySearchTree()

    def test_insert(self):
        lst = [5, 8, 2, 1, 3, 9, 7, 4, 6, 0]
        for i in lst:
            self.bst.insert(i)
        self.assertEqual(len(self.bst), 10)

    def test_delete(self):
        self.bst.delete(5)
        self.assertEqual(len(self.bst), 9)

    def test_iteration(self):
        lst = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
        for i in self.bst.root:
            self.assertTrue(i == lst[i])

    def tearDown(self):
        pass

if __name__ == '__main__':
    unittest.main()
