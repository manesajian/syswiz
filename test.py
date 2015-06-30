import unittest

from binarysearchtree import BinarySearchTree
from avltree import AVLTree

class TestBinarySearchTree(unittest.TestCase):
    def setUp(self):
        self.bst = None

    def _initialize(self):
        self._cleanup()
        self.bst = BinarySearchTree()
        lst = [5, 8, 2, 1, 3, 9, 7, 4, 6, 0]
        for i in lst:
            self.bst.insert(i)

    def _cleanup(self):
        if self.bst:
            del(self.bst)
            self.bst = None

    def test_insert(self):
        self._initialize()
        self.assertEqual(len(self.bst), 10)

    def test_delete(self):
        self._initialize()
        self.bst.delete(5)
        self.assertEqual(len(self.bst), 9)

    def test_iteration(self):
        self._initialize()
        lst = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
        for i in self.bst.root:
            self.assertTrue(i == lst[i])

    def tearDown(self):
        self._cleanup()

class AVLTree(unittest.TestCase):
    def setUp(self):
        self.avl = None

    def _initialize(self):
        self._cleanup()
        self.avl = AVLTree()
        lst = [5, 8, 2, 1, 3, 9, 7, 4, 6, 0]
        for i in lst:
            self.avl.insert(i)

    def _cleanup(self):
        if self.avl:
            del(self.avl)
            self.avl = None

    def test_insert(self):
        self._initialize()
        self.assertEqual(len(self.avl), 10)

    def test_delete(self):
        self._initialize()
        self.avl.delete(5)
        self.assertEqual(len(self.avl), 9)

    def test_iteration(self):
        self._initialize()
        lst = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
        for i in self.avl.root:
            self.assertTrue(i == lst[i])

    def tearDown(self):
        self._cleanup()

if __name__ == '__main__':
    unittest.main()
