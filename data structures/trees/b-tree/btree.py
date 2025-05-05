class Node:
    def __init__(self, leaf=False):
        self.keys = []
        self.children = []
        self.leaf = leaf

class BTree():
    def __init__(self, t):
        self.root = Node(True)
        self.t = t

    def search(self, key, node=None):
        node = self.root if node==None else node
        i=0
        while i<len(node.keys) and key>node.keys[i]:
            i+=1
        if i < len(node.keys) and key == node.keys[i]:
            return (node, i)
        elif node.leaf:
            return None
        else:
            return self.search(key, node.children[i])
        
    def split_child(self, x, i):
        t = self.t
        #y - забитый до отказа сын х
        y = x.children[i]
        #создаем новый узел и привязываем его к родителю
        z = Node(y.leaf)
        x.children.insert(i+1, z)
        #вставляем средний элемент из делимого в его родителя
        x.keys.insert(i, y.keys[t-1])
        #разделим оставшиеся в У значения на у и z
        z.keys = y.keys[t: (2 * t) - 1]
        y.keys = y.keys[0, t-1]
        #если y - не лист, то распределяем его детей между у и z
        if not y.leaf:
            z.children = y.children[t: 2*t]
            y.children = y.children[0: t-1]

    def insert(self, k):
        t = self.t
        root = self.root
        if len(root.keys) == (2*t) - 1:
            new_root = Node()
            self.root = new_root
            new_root.children.insert(0, root)
            self.split_child(new_root, 0)
            self.insert_non_full(new_root, k)
        else:
            self.insert_non_full(root, k)

    def insert_non_full(self, x, k):
        t = self.t
        i = len(x.keys) - 1
        if x.leaf:
            while i>=0 and k< x.keys[i]:
                x.keys[i+1] = x.keys[i]
                i-=1
            x.keys[i+1] = k
        else:
            while i>=0 and k < x.keys[i]:
                i-=1
            i+=1
            if len(x.children[i].keys) == (2 * t) - 1:
                self.split_child(x, i)
                if k > x.keys[i]:
                    i += 1
            self.insert_non_full(x.children[i], k)
    def delete(self, x, k):
        t = self.t
        i = 0

        while i < len(x.keys) and k > x.keys[i]:
            i += 1
        if x.leaf:
            if i < len(x.keys) and x.keys[i] == k:
                x.keys.pop(i)
            return

        if i < len(x.keys) and x.keys[i] == k:
            return self.delete_internal_node(x, k, i)
        elif len(x.children[i].keys) >= t:
            self.delete(x.children[i], k)
        else:
            if i != 0 and i + 2 < len(x.children):
                if len(x.children[i - 1].keys) >= t:
                    self.delete_sibling(x, i, i - 1)
                elif len(x.children[i + 1].keys) >= t:
                    self.delete_sibling(x, i, i + 1)
                else:
                    self.delete_merge(x, i, i + 1)
            elif i == 0:
                if len(x.children[i + 1].keys) >= t:
                    self.delete_sibling(x, i, i + 1)
                else:
                    self.delete_merge(x, i, i + 1)
            elif i + 1 == len(x.children):
                if len(x.children[i - 1].keys) >= t:
                    self.delete_sibling(x, i, i - 1)
                else:
                    self.delete_merge(x, i, i - 1)
            self.delete(x.children[i], k)

    def delete_internal_node(self, x, k, i):
        t = self.t
        if x.leaf:
            if x.keys[i] == k:
                x.keys.pop(i)
            return

        if len(x.children[i].keys) >= t:
            x.keys[i] = self.delete_predecessor(x.children[i])
            return
        elif len(x.children[i + 1].keys) >= t:
            x.keys[i] = self.delete_successor(x.children[i + 1])
            return
        else:
            self.delete_merge(x, i, i + 1)
            self.delete_internal_node(x.children[i], k, self.t - 1)

    def delete_predecessor(self, x):
        if x.leaf:
            return x.keys.pop()
        n = len(x.keys) - 1
        if len(x.children[n].keys) >= self.t:
            self.delete_sibling(x, n + 1, n)
        else:
            self.delete_merge(x, n, n + 1)
        self.delete_predecessor(x.children[n])

    def delete_successor(self, x):
        if x.leaf:
            return x.keys.pop(0)
        if len(x.children[1].keys) >= self.t:
            self.delete_sibling(x, 0, 1)
        else:
            self.delete_merge(x, 0, 1)
        self.delete_successor(x.children[0])

    def delete_merge(self, x, i, j):
        cnode = x.children[i]

        if j > i:
            rsnode = x.children[j]
            cnode.keys.append(x.keys[i])
            for k in range(len(rsnode.keys)):
                cnode.keys.append(rsnode.keys[k])
                if len(rsnode.children) > 0:
                    cnode.children.append(rsnode.children[k])
            if len(rsnode.children) > 0:
                cnode.children.append(rsnode.children.pop())
            new = cnode
            x.keys.pop(i)
            x.children.pop(j)
        else:
            lsnode = x.children[j]
            lsnode.keys.append(x.keys[j])
            for i in range(len(cnode.keys)):
                lsnode.keys.append(cnode.keys[i])
                if len(lsnode.children) > 0:
                    lsnode.children.append(cnode.children[i])
            if len(lsnode.children) > 0:
                lsnode.children.append(cnode.children.pop())
            new = lsnode
            x.keys.pop(j)
            x.children.pop(i)

        if x == self.root and len(x.keys) == 0:
            self.root = new

    def delete_sibling(self, x, i, j):
        cnode = x.children[i]
        if i < j:
            rsnode = x.children[j]
            cnode.keys.append(x.keys[i])
            x.keys[i] = rsnode.keys[0]
            if len(rsnode.children) > 0:
                cnode.children.append(rsnode.children[0])
                rsnode.children.pop(0)
            rsnode.keys.pop(0)
        else:
            lsnode = x.children[j]
            cnode.keys.insert(0, x.keys[i - 1])
            x.keys[i - 1] = lsnode.keys.pop()
            if len(lsnode.children) > 0:
                cnode.children.insert(0, lsnode.children.pop())

    def print_tree(self, x, level=0):
        print(f'Level {level}', end=": ")

        for i in x.keys:
            print(i, end=" ")

        print()
        level += 1

        if len(x.children) > 0:
            for i in x.children:
                self.print_tree(i, level)
