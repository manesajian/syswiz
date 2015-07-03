import unittest

from collections import deque

from binarytree import BinaryTree
from binarysearchtree import BinarySearchTree
from avltree import AVLTree

def log(msg):
    with open('test.output', 'a') as f:
        f.write(msg + '\n')

def _print_tree(node, is_left, offset, depth, s):
    if node == None: return 0

    width = 6
    left  = _print_tree(node.leftChild, 1, offset, depth + 1, s)
    right = _print_tree(node.rightChild, 0, offset + left + width, depth + 1, s)

    b = '({:3s})'.format(str(node.value)).ljust(20)

    row = list(s[depth])
    for i in range(width):
        row[offset + left + i] = b[i];
    s[depth] = ''.join(row)

    row = list(s[depth - 1])
    if (depth and is_left):
        for i in range(width + right):
            row[offset + left + (width // 2) + i] = '-';
        row[offset + left + (width // 2)] = '.';
    elif (depth and not is_left):
        for i in range(left + width):
            row[offset - (width // 2) + i] = '-';
        row[offset + left + (width // 2)] = '.';
    s[depth - 1] = ''.join(row)

    return left + width + right

def print_tree(bt):
    log('Tree count: {0}, tree height: {1}'.format(len(bt), bt.height()))

    s = [' '*80 for i in range(20)]

    if bt.root:
        _print_tree(bt.root, 0, 0, 0, s)

    for line in s:
        if len(line.strip()) > 0:
            log(line)

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

class TestAVLTree(unittest.TestCase):
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
        print_tree(self.avl)
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
