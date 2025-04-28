from math import log2, ceil
def check_pow_2(n):
    if(n > 0 and (n & (n - 1))==0):
        return True
    return False

def hemming_encode(s: str) -> str:
    data_bits = [int(bit) for bit in s]
    n = len(data_bits)
    check_bits_quantity = 0
    while(2**check_bits_quantity < n + check_bits_quantity + 1):
        check_bits_quantity += 1
    encoded = []
    data_index = 0
    for i in range(1, n + check_bits_quantity + 1):
        if check_pow_2(i):
            encoded.append(0)
        else:
            encoded.append(data_bits[data_index])
            data_index += 1
    for i in range(check_bits_quantity):
        current = 2**i
        if(current > len(encoded)):
            continue
        buf = 0
        for j in range(current-1, len(encoded), 2*current):
            for k in range(j, min(j+current, len(encoded))):
                buf ^= encoded[k]
        encoded[current - 1] = buf
    return ''.join(map(str, encoded))

def hemming_decode(s: str) -> str:
    encoded = [int(bit) for bit in s]
    n = len(encoded)
    check_bits_quantity = 0
    while(2**check_bits_quantity <= n):
        check_bits_quantity += 1
    
    error_pos = 0
    for i in range(check_bits_quantity):
        current = 2**i
        if(current > n):
            continue
        buf = 0
        for j in range(current - 1, n, 2 * current):
            for k in range(j, min(j + current, n)):
                buf ^= encoded[k]
        if(buf != 0):
            error_pos += current
    if(0 < error_pos and error_pos <= n):
        encoded[error_pos - 1] ^= 1
    decoded = []
    for i in range(1, n + 1):
        if(not check_pow_2(i)):
            decoded.append(str(encoded[i - 1]))
    return ''.join(decoded)

z = "0101010"
buf = hemming_encode(z)
print(buf)
print(hemming_decode(buf))