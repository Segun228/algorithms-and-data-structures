class FenwickCube:
    def __init__(self, size):
        self.n = size
        self.fenwick = [[[0] * (self.n + 2) for _ in range(self.n + 2)] for __ in range(self.n + 2)]
    
    def update(self, x, y, z, delta):
        """Обновление значения в точке (x,y,z) с приращением delta"""
        i = x + 1
        while i <= self.n + 1:
            j = y + 1
            while j <= self.n + 1:
                k = z + 1
                while k <= self.n + 1:
                    self.fenwick[i][j][k] += delta
                    k += k & -k
                j += j & -j
            i += i & -i
    
    def sum(self, x, y, z):
        """Вычисление суммы от (0,0,0) до (x,y,z)"""
        res = 0
        i = x + 1
        while i > 0:
            j = y + 1
            while j > 0:
                k = z + 1
                while k > 0:
                    res += self.fenwick[i][j][k]
                    k -= k & -k
                j -= j & -j
            i -= i & -i
        return res
    
    def get_stars(self, x1, y1, z1, x2, y2, z2):
        """Вычисление суммы в 3D-прямоугольнике (кубоиде)"""
        return  (self.sum(x2, y2, z2) - self.sum(x1-1, y2, z2) - self.sum(x2, y1-1, z2) - self.sum(x2, y2, z1-1) + self.sum(x1-1, y1-1, z2) + self.sum(x1-1, y2, z1-1) + self.sum(x2, y1-1, z1-1) - self.sum(x1-1, y1-1, z1-1))


def main():
    import sys
    input = sys.stdin.read().split()
    ptr = 0
    n = int(input[ptr])
    ptr += 1
    fenwick = FenwickCube(n)
    m = int(input[ptr])
    ptr += 1
    while m != 3:
        if m == 1:
            x, y, z, k = map(int, input[ptr:ptr+4])
            ptr += 4
            fenwick.update(x, y, z, k)
        elif m == 2:
            x1, y1, z1, x2, y2, z2 = map(int, input[ptr:ptr+6])
            ptr += 6
            print(fenwick.get_stars(x1, y1, z1, x2, y2, z2))
        m = int(input[ptr])
        ptr += 1

if __name__ == "__main__":
    main()