from ctypes import *

#load the shared object file
adder = CDLL('./adder.so')
add_float = adder.add_float
add_float.restype = c_float
print "Sum 3.2 + 2.1 = ", str(add_float())
