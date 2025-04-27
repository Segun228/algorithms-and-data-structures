from math import log2

def hemming_encode (s : str) -> str:
    help_bits_quantity = 0
    i = 0
    counter = 0
    code_list = [None]
    for le in s:
        code_list.append(int(le))

    while(i + help_bits_quantity <= len(s) + 2**(int(log2(len(s))))):
        if (i == 2**help_bits_quantity):
            code_list.insert(i, 0)
            help_bits_quantity+=1
        i+=1

    total_length = help_bits_quantity + len(s)
    print(help_bits_quantity)
    for j in range(0, help_bits_quantity):
        counter = 0
        for k in range(2**j, total_length, 2**j):
            if(k>total_length):
                break
            for r in range(0, 2**j):
                if k+r>total_length:
                    break
                if(code_list[k+r]==1 and not((i & (i - 1)) == 0)):
                    counter+=1
        if(counter%2):
            code_list[2**j] = 1
        else:
            code_list[2**j] = 0
    code_list.pop(0)
    for i in range(0, len(code_list)):
        code_list[i] = str(code_list[i])
    return "".join(code_list)


def hemming_decode (s : str) -> str:
    code_list = []
    answer = ""
    for le in s:
        code_list.append(le)
    mistakes = []
    i = 0
    counter = 0
    control_bits = 0
    while(i < len(s)):
        if((i & (i - 1)) == 0):
            control_bits+=1
    for i in range(control_bits):
        counter = 0
        control_bit_position = 2**i 
        value = 0
        for j in range(1, len(s)+control_bits+1):
            if (j & control_bit_position) != 0:
                if code_list[j - 1] == '1':
                    counter+=1
        if(counter%2 != code_list[control_bit_position]):
            mistakes.append(control_bit_position)
    code_list[sum(mistakes)] ^= 1
    for j in range(1, len(s)+control_bits+1):
        if not((j & (j - 1)) == 0):
            answer+=code_list[j]
    print(answer)
    return answer


s = input()
print(hemming_encode(s))
print(hemming_decode(input()))
