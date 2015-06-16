class LinkedListNode():
    def __init__(self):
        self.prev = None
        self.next = None

# doubly-linked optionally-circular list implementation
class LinkedList():
    def __init__(self, circular = False):
        self.head = None
        self.tail = None
        self.__count = 0

        # llist can iterate circularly
        self.circular = circular

    def __len__(self):
        return self.__count

    def __iter__(self):
        self.__next = self.head
        return self

    def __next__(self):
        returnObj = self.__next

        if returnObj is None:
            if self.circular:
                self.__next = self.head
                returnObj = self.__next
            else:
                raise StopIteration

        self.__next = returnObj.next

        return returnObj

    def __lookup(self, idx):
        # convert negative index to positive
        if idx < 0:
            idx += self.__count

        if idx < 0 or idx >= self.__count:
            raise IndexError('idx ({0}/{1}) out of range'.format(idx,
                                                                 len(self)))

        if self.__count == 0:
            return None

        # start from whichever end of list is closest to idx
        midIdx = (self.__count - 1) // 2
        if idx < midIdx:
            item = self.head
            for i in range(0, idx):
                item = item.next
        else:
            item = self.tail
            for i in range(0, (self.__count - 1) - idx):
                item = item.prev

        return item

    def __slice(self, slice_):
        newLst = LinkedList()

        start = slice_.start
        stop = slice_.stop
        step = slice_.step

        if step == None:
            step = 1

        if start == None:
            if step < 0:
                start = -1
            else:
                start = 0
        elif start < 0:
            start = len(self) + start

        if abs(start) > len(self):
            raise IndexError('list index out of range')

        if stop == None:
            stop = len(self)
        elif stop < 0:
            stop = len(self) - stop

        if abs(stop) > len(self):
            raise IndexError('list index out of range')

        node = self.__getitem__(start)
        for i in range(*slice_.indices(len(self))):
            newLst.push_tail(copy(node))
            steps = step
            while steps != 0:
                if steps < 0:
                    node = node.prev
                    if node is None:
                        node = self.tail
                    steps += 1
                else:
                    node = node.next
                    if node is None:
                        node = self.head
                    steps -= 1

        return newLst

    def __getitem__(self, val):
        if isinstance(val, slice):
            return self.__slice(val)

        return self.__lookup(val)

    def is_empty(self):
        return self.__count == 0

    def push(self, idx, node):
        if idx == 0:
            # set new head, order of operations matters
            node.prev = None
            node.next = self.head

            # if list not empty, point current head to new head
            if self.head is not None:
                self.head.prev = node
            else:
                self.tail = node

            self.head = node
        elif idx >= self.__count:
            # set new tail, order of operations matters
            node.next = None
            node.prev = self.tail

            # if list not empty, point current tail to new tail
            if self.tail is not None:
                self.tail.next = node
            else:
                self.head = node

            self.tail = node
        else:
            curNode = self.__lookup(idx)

            # handle empty list case
            if curNode is None:
                self.head = node
                self.tail = node
                node.prev = None
                node.next = None
            else:
                # splice new node in
                node.next = curNode
                node.prev = curNode.prev
                curNode.prev.next = node
                curNode.prev = node

        self.__count += 1

    def push_head(self, node):
        self.push(0, node)

    def push_middle(self, idx, node):
        self.push(idx, node)

    def push_tail(self, node):
        self.push(self.__count, node)

    def pop(self, idx):
        if self.__count < 1:
            return None
        
        if idx <= 0:
            # get list head
            item = self.head

            # point list head to next element
            self.head = self.head.next

            # if list not empty, tell head it has no prev         
            if self.head is not None:
                self.head.prev = None

            # one less element in the list
            self.__count -= 1

            # if down to 1 element, set tail to head
            if self.__count == 1:
                self.tail = self.head
                
            return item
        elif idx >= self.__count - 1:
            # get list tail
            item = self.tail

            # point list tail to previous element
            self.tail = self.tail.prev

            # if list not empty, tell tail it has no next
            if self.tail is not None:
                self.tail.next = None

            # one less element in the list
            self.__count -= 1

            # if down to 1 element, set head to tail
            if self.__count == 1:
                self.head = self.tail

            return item
        else:
            curNode = self.__lookup(idx)

            # because curNode is not head or tail, these dereferences are safe
            curNode.prev.next = curNode.next
            curNode.next.prev = curNode.prev

            # one less element in the list
            self.__count -= 1

            return curNode
          
    def pop_head(self):
        return self.pop(0)

    def pop_middle(self, idx):
        return self.pop(idx)

    def pop_tail(self):
        return self.pop(self.__count - 1)

    def pop_node(self, node):
        if node is None:
            return None

        if node.prev is not None:
            node.prev.next = node.next
        else:
            self.head = node.next

        if node.next is not None:
            node.next.prev = node.prev
        else:
            self.tail = node.prev

        self.__count -= 1

        return node

    def insert_before(self, oldNode, newNode):
        if self.__count < 1:
            raise SuperQEx('Calling insert_before() on empty list.')

        # handle case inserting new head
        if self.head == oldNode:
            newNode.prev = None
            newNode.next = oldNode
            oldNode.prev = newNode
            self.head = newNode
        else:
            newNode.prev = oldNode.prev
            newNode.next = oldNode
            oldNode.prev.next = newNode
            oldNode.prev = newNode

        self.__count += 1

    def insert_after(self, oldNode, newNode):
        if self.__count < 1:
            raise SuperQEx('Calling insert_before() on empty list.')

        # handle case inserting new tail
        if self.tail == oldNode:
            newNode.next = None
            newNode.prev = oldNode
            oldNode.next = newNode
            self.tail = newNode
        else:
            newNode.prev = oldNode
            newNode.next = oldNode.next
            oldNode.next.prev = newNode
            oldNode.next = newNode

        self.__count += 1

    def move_up(self, node):
        # can't move list node up if it is already head
        if node.prev is None:
            return

        # these are aliases to the 4 starting elements involved
        above_node_prev = node.prev.prev
        above_node = node.prev
        current_node = node
        current_node_next = node.next

        # do the pointer swaps
        if above_node_prev is not None:
            above_node_prev.next = current_node
        current_node.prev = above_node_prev
        current_node.next = above_node
        above_node.prev = current_node
        above_node.next = current_node_next
        above_node.next.prev = above_node

        # if node is at top of list, set head to node
        if current_node.prev is None:
            self.head = current_node

    def move_down(self, node):
        # can't move list node up if it is already head
        if node.prev is None:
            return

        # these are aliases to the 4 starting elements involved
        above_node_prev = node.prev.prev
        above_node = node.prev
        current_node = node
        current_node_next = node.next

        # do the pointer swaps
        if above_node_prev is not None:
            above_node_prev.next = current_node
        current_node.prev = above_node_prev
        current_node.next = above_node
        above_node.prev = current_node
        above_node.next = current_node_next
        above_node.next.prev = above_node

        # if node is at top of list, set head to node
        if current_node.prev is None:
            self.head = current_node
