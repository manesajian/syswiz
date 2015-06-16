from binarysearchtree import BinarySearchTree

bst = BinarySearchTree()

lst = [5, 8, 2, 1, 3, 9, 7, 4, 6, 0]

for i in lst:
    bst.insert(i)

for i in bst.root:
    print(i)

bst.delete(5)

for i in bst.root:
    print(i)

